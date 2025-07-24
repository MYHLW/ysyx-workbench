#include "Vysyx_25020059_top.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include <verilated_dpi.h>

// 仿真内存基址和大小定义
#define MEM_BASE       0x80000000U
#define MEM_SIZE       (8 * 1024 * 1024) // 8MB

static Vysyx_25020059_top dut;
static uint8_t *memory;

// 将虚拟地址转换为内存数组偏移
static inline uint32_t guest_to_host(uint32_t addr) {
    return addr - MEM_BASE;
}

// 从仿真内存读取一条指令
uint32_t pmem_read(uint32_t * /*unused*/, uint32_t vaddr) {
    uint32_t off = guest_to_host(vaddr);
    return *(uint32_t *)(memory + off);
}

// 从文件加载二进制镜像到仿真内存
void load_image(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    // 读入数据
    size_t sz = fread(memory, 1, MEM_SIZE, fp);
    fclose(fp);
    printf("Loaded binary '%s' (%zu bytes) at 0x%08X\n", filename, sz, MEM_BASE);
}

// 一个时钟周期
void single_cycle() {
    dut.clk = 0; dut.eval();
    dut.clk = 1; dut.eval();
}

// 复位 n 个周期
static void reset(int n) {
    dut.rst = 0; 
    while (n-- > 0) single_cycle();
    dut.rst = 1; 
}

// ============ DPI‑C: ebreak 触发退出 ==============
extern "C" void npc_trap(int code) {
    printf("[DPI] ebreak, PC = 0x%08X, code = %d\n", (uint32_t)dut.curr_pc, code);
    exit(0);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <program.bin>\n", argv[0]);
        return -1;
    }
    // 分配仿真内存
    memory = (uint8_t *)malloc(MEM_SIZE);
    if (!memory) {
        perror("malloc");
        return -1;
    }
    memset(memory, 0, MEM_SIZE);

    // 加载用户程序
    load_image(argv[1]);

    // Verilator 波形追踪设置
    Verilated::traceEverOn(true);
    VerilatedContext *ctx = new VerilatedContext;
    VerilatedVcdC *tfp = new VerilatedVcdC;
    dut.trace(tfp, 5);
    tfp->open("Vysyx_25020059.vcd");

    // 初始化时钟与复位
    dut.clk = 1;
    dut.rst = 0; // 复位信号
    reset(2);


    // 仿真主循环，直到 ebreak 调用 npc_trap 退出进程
    while (true) {
        // 提取并分发指令
        dut.inst = pmem_read(nullptr, dut.curr_pc);
        // 单周期推进
        single_cycle();
        // 波形记录
        tfp->dump(ctx->time());
        ctx->timeInc(1);
        // 同步打印 PC 和指令
        printf("PC=0x%08X inst=0x%08X\n", (uint32_t)dut.curr_pc, dut.inst);
    }

    // 清理（理论上不可达）
    tfp->close();
    delete tfp;
    delete ctx;
    free(memory);
    return 0;
}
