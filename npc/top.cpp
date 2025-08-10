#include "common.h"
#include "debug.h"
#include "cpu_exec.h"
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <sys/time.h>
#include <string>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include <verilated_dpi.h>

//初始化
//处理参数 把img_file传出去
//启动sdb

bool              sim_done  = false;
int               trap_code = -1;
uint64_t          sim_cycle = 0;
const uint32_t MEM_BASE = 0x80000000U;
const uint32_t MEM_SIZE = 128 * 1024 * 1024;  // 128MB
uint8_t memory[MEM_SIZE];  // 全局内存数组（供loader和cli访问）
#define MEM_FAULT_CODE   0xdeadbeef  // 定义内存故障码
#define MEM_ACCESS_FAULT 1           // 定义内存访问错误trap码
#define MAX_CYCLE 10000000  // 最大允许周期数，超过则触发trap

// 定义设备地址
#define SERIAL_PORT 0xa00003f8  // 串口地址，与NEMU保持一致
#define RTC_PORT    0xa0000048  // 时钟地址，与NEMU保持一致
#define VGACTL_PORT 0xa0000100  // VGA控制器地址，与NEMU保持一致
#define FB_ADDR     0xa1000000  // 帧缓冲区地址，与NEMU保持一致
#define KBD_ADDR    0xa0000060  // 键盘地址，与NEMU保持一致


void init_ftrace(char *elf_file);
void init_iritrace(int num_entries);


void exit_ftrace();
void iritrace_destroy(void);

int main(int argc, char *argv[]) {
    //参数处理（暂时放在这）

    if(argc < 1){
        Assert(0, "NO img_file input");
    }
    if(argc < 2){
        Assert(0, "NO elf_file input");
    }

    //init
        //ft
    char *elf_file = argv[2];
    init_ftrace(elf_file);
        //ir
    init_iritrace(16);
        //
    char *img_file = argv[1];
    init_mainloop(img_file);
        //diff 见cpu_exec


    //启动sdb
    init_sdb();
    sdb_mainloop();


    //结束
    exit_ftrace();
    iritrace_destroy();
    
    exit_mainloop();
}
//================================DPI-C=======================================================
extern "C" void npc_trap(int code) {
    if (!sim_done) {
        sim_done = true;
        trap_code = code;
        // 在trap时打印指令环形缓冲区
        //display_inst();
    }
    printf("NPC_TRAP: code=%d\n", code);
    printf("%ld cycles executed.\n", sim_cycle);
    std::printf("\n");
    if (trap_code == 0) {
        std::printf("\033[32m[NPC] HIT GOOD TRAP: program exited successfully.\033[0m\n");
    } else {
        std::printf("\033[31m[NPC] HIT BAD TRAP: program failed (code=%d).\033[0m\n", trap_code);
    }
}

// 获取当前时间（毫秒）
uint64_t get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

extern "C" uint32_t pmem_r(uint32_t vaddr, int i) {  
    uint32_t value = 0;
    
    // 处理MMIO读取
    if (vaddr == RTC_PORT) {
        value = (uint32_t)get_time();
    }
    else if (vaddr == RTC_PORT + 4) {
        value = (uint32_t)(get_time() >> 32);
    }
    // 处理普通内存读取
    else if (vaddr >= MEM_BASE && vaddr < MEM_BASE + MEM_SIZE) {
        //printf("code:%d pmem_read: addr=0x%08X\n", i, vaddr);
        uint32_t off = vaddr - MEM_BASE;
        memcpy(&value, memory + off, sizeof(value));
    }
    else if (vaddr == SERIAL_PORT) {
        value = 0;  // 串口读取，返回0表示可以写入
    }
    else if (vaddr == VGACTL_PORT) {
        // 返回VGA控制寄存器的值（屏幕大小）
        return (300 << 16) | 400;
    }
    else if (vaddr == VGACTL_PORT + 4) {
        // 返回同步状态，始终为1表示就绪
        return 1;
    }
    else if (vaddr >= FB_ADDR && vaddr < FB_ADDR + 400 * 300 * 4) {
        // 从帧缓冲区读取像素数据
        uint32_t fb_offset = vaddr - FB_ADDR;
        uint32_t value;
        memcpy(&value, memory + MEM_SIZE - (400 * 300 * 4) + fb_offset, sizeof(value));
        return value;
    }
    else {
        printf("pmem_read: address out of bounds: 0x%08X\n", vaddr);
        npc_trap(MEM_ACCESS_FAULT);
        return MEM_FAULT_CODE;
    }
    
    // // 添加内存读取追踪
    // trace_memory(false, vaddr, value, 4);
    return value;
}

extern "C" void pmem_w(uint32_t addr, uint32_t data, uint8_t wmask) {
    //printf("pmem_write: addr=0x%08X, off_data=0x%08X, wmask=0x%02X\n", addr, data, wmask);
    
    // 处理MMIO写入
    if (addr == SERIAL_PORT) {
        putchar(data & 0xff);
        fflush(stdout);
    }
    // 处理VGA控制器写入
    else if (addr == VGACTL_PORT) {
        static uint32_t vgactl = 0;
        vgactl = data;
    }
    else if (addr == VGACTL_PORT + 4) {
        // VGA同步信号
    }
    // 处理帧缓冲区写入
    else if (addr >= FB_ADDR && addr < FB_ADDR + 400 * 300 * 4) {
        uint32_t fb_offset = addr - FB_ADDR;
        uint8_t *fb_ptr = (uint8_t *)&data;
        for (int i = 0; i < 4; i++) {
            if (wmask & (1 << i)) {
                memory[MEM_SIZE - (400 * 300 * 4) + fb_offset + i] = fb_ptr[i];
            }
        }
    }
    // 处理普通内存写入
    else if (addr >= MEM_BASE && addr < MEM_BASE + MEM_SIZE) {
        uint32_t off_byte = addr - MEM_BASE;
        uint32_t off_word = off_byte & ~0x3u;
        uint8_t *p = memory + off_word;
        for (int i = 0; i < 4; i++) {
            if (wmask & (1u << i)) {
                p[i] = uint8_t((data >> (i * 8)) & 0xFF);
            }
        }
    }
    else {
        printf("pmem_write: address out of bounds: 0x%08X\n", addr);
        npc_trap(MEM_ACCESS_FAULT);
    }
}