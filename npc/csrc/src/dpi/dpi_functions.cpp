#include <cstdint>
#include <cstdio>
#include <cstring>
#include <sys/time.h>
#include "memory.h"
#include "difftest/difftest_check.h"
#include "trace/itrace.h"

// 定义内存访问错误码
#define MEM_ACCESS_FAULT 0xdeadbeef
volatile bool need_difftest_skip_ref = false;

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

    // 处理 MMIO 读取
    if (vaddr == RTC_PORT) {
        need_difftest_skip_ref = true;  // 设置跳过标志
        value = (uint32_t)get_time();
    }
    else if (vaddr == RTC_PORT + 4) {
        need_difftest_skip_ref = true;
        value = (uint32_t)(get_time() >> 32);
    }
    // 处理普通内存读取
    else if (vaddr >= MEM_BASE && vaddr < MEM_BASE + MEM_SIZE) {
        uint32_t off = vaddr - MEM_BASE;
        memcpy(&value, memory + off, sizeof(value));
    }
    else if (vaddr == SERIAL_PORT) {
        need_difftest_skip_ref = true;
        value = 0;  // 串口读取，返回0表示可以写入
    }
    else if (vaddr == VGACTL_PORT) {
        need_difftest_skip_ref = true;
        // 返回VGA控制寄存器的值（屏幕大小）
        return (300 << 16) | 400;
    }
    else if (vaddr == VGACTL_PORT + 4) {
        need_difftest_skip_ref = true;
        // 返回同步状态，始终为1表示就绪
        return 1;
    }
    else if (vaddr >= FB_ADDR && vaddr < FB_ADDR + 400 * 300 * 4) {
        need_difftest_skip_ref = true;
        // 从帧缓冲区读取像素数据
        uint32_t fb_offset = vaddr - FB_ADDR;
        uint32_t val;
        memcpy(&val, memory + MEM_SIZE - (400 * 300 * 4) + fb_offset, sizeof(val));
        return val;
    }
    else {
        printf("pmem_read: address out of bounds: 0x%08X\n", vaddr);
        npc_trap(MEM_ACCESS_FAULT);
       // return 0;
    }

    return value;
}

extern "C" void pmem_write(uint32_t addr, uint32_t data, uint8_t wmask) {
    // 处理 MMIO 写入
    if (addr == SERIAL_PORT) {
        need_difftest_skip_ref = true;
        putchar(data & 0xff);
        fflush(stdout);
    }
    // 处理VGA控制器写入
    else if (addr == VGACTL_PORT) {
        need_difftest_skip_ref = true;
        static uint32_t vgactl = 0;
        vgactl = data;
    }
    else if (addr == VGACTL_PORT + 4) {
        need_difftest_skip_ref = true;
        // VGA同步信号
    }
    // 处理帧缓冲区写入
    else if (addr >= FB_ADDR && addr < FB_ADDR + 400 * 300 * 4) {
        need_difftest_skip_ref = true;
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