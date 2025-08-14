#include <cstdint>
#include <cstdio>
#include <cstring>
#include <sys/time.h>
#include "memory.h"
#include "trace/itrace.h"

// 引用 main_new.cpp 中的全局变量
extern bool sim_done;
extern int trap_code;
extern uint64_t sim_cycle;
extern uint8_t memory[];
extern const uint32_t MEM_BASE;
extern const uint32_t MEM_SIZE;

// ===================DPI 端口===========================
extern "C" void npc_trap(int code) {
    if (!sim_done) {
        sim_done = true;
        trap_code = code;
        // 在trap时打印指令环形缓冲区
        display_inst();
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

// 定义设备地址
#define SERIAL_PORT 0xa00003f8  // 串口地址，与NEMU保持一致
#define RTC_PORT    0xa0000048  // 时钟地址，与NEMU保持一致
#define VGACTL_PORT 0xa0000100  // VGA控制器地址，与NEMU保持一致
#define FB_ADDR     0xa1000000  // 帧缓冲区地址，与NEMU保持一致
#define KBD_ADDR    0xa0000060  // 键盘地址，与NEMU保持一致

// 获取当前时间（毫秒）
uint64_t get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}

extern "C" uint32_t pmem_read(uint32_t vaddr, int i) {  
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
        // Framebuffer access, not implemented yet
        // For now, return 0
        return 0;
    }
    else {
        //printf("Invalid pmem_read address: 0x%08X\n", vaddr);
        //npc_trap(MEM_ACCESS_FAULT); // 触发内存访问错误
        return 0; // 或者返回一个错误值
    }
    return value;
}

extern "C" void pmem_write(uint32_t vaddr, uint32_t data, int i) {
    // 处理MMIO写入
    if (vaddr == SERIAL_PORT) {
        // 串口写入，直接打印字符
        putchar(data);
    }
    // 处理普通内存写入
    else if (vaddr >= MEM_BASE && vaddr < MEM_BASE + MEM_SIZE) {
        //printf("code:%d pmem_write: addr=0x%08X, data=0x%08X\n", i, vaddr, data);
        uint32_t off = vaddr - MEM_BASE;
        memcpy(memory + off, &data, sizeof(data));
    }
    else if (vaddr >= FB_ADDR && vaddr < FB_ADDR + 400 * 300 * 4) {
        // Framebuffer access, not implemented yet
    }
    else {
        //printf("Invalid pmem_write address: 0x%08X\n", vaddr);
        //npc_trap(MEM_ACCESS_FAULT); // 触发内存访问错误
    }
}