/*main_new.cpp 只负责初始化（内存、波形、复位）和清理，核心仿真控制交给 sdb_mainloop。*/
//=================================================================================
// main_new.cpp
#include "verilated_vcd_c.h"
#include "Vysyx_25020059_top.h"
#include "verilated.h"
#include "sdb.h"  // 引入 sdb 模块
#include <cstdio>
#include <cstdlib>
#include <cstring>

// 声明外部全局变量（在 sdb.cpp 中定义）
extern Vysyx_25020059_top dut;
extern VerilatedVcdC* tfp;
extern VerilatedContext* ctx;
extern bool sim_done;
extern int trap_code;

#define MEM_BASE 0x80000000U
#define MEM_SIZE (8 * 1024 * 1024)
static uint8_t* memory;

// 加载程序镜像（复用之前的逻辑）
void load_image(const char* filename) {
    FILE* fp = fopen(filename, "rb");
    if (!fp) { perror("fopen"); exit(1); }
    size_t sz = fread(memory, 1, MEM_SIZE, fp);
    fclose(fp);
    printf("Loaded '%s' (%zu bytes) at 0x%08X\n", filename, sz, MEM_BASE);
}

// 复位函数
static void reset(int n) {
    dut.rst = 1;
    while (n-- > 0) {
        dut.clk = 0; dut.eval();
        dut.clk = 1; dut.eval();
        ctx->timeInc(2);  // 复位阶段的时间推进
    }
    dut.rst = 0;
}

// DPI 回调（陷阱处理）
extern "C" void npc_trap(int code) {
    if (!sim_done) {
        sim_done = true;
        trap_code = code;
    }
}

int main(int argc, char**argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <image.bin>\n", argv[0]);
        return 1;
    }

    // 初始化内存
    memory = (uint8_t*)malloc(MEM_SIZE);
    memset(memory, 0, MEM_SIZE);
    load_image(argv[1]);

    // 初始化仿真上下文和波形
    ctx = new VerilatedContext;
    tfp = new VerilatedVcdC;
    dut.trace(tfp, 5);
    tfp->open("Vysyx_25020059.vcd");
    Verilated::traceEverOn(true);

    // 复位 CPU
    reset(2);  // 复位 2 个周期

    // 启动 sdb 命令行主循环（核心控制交给 sdb 模块）
    sdb_mainloop();

    // 仿真结束：打印结果并清理
    printf("\n");
    if (trap_code == 0) {
        printf("\033[32m[NPC] Success (code=%d)\033[0m\n", trap_code);
    } else {
        printf("\033[31m[NPC] Failed (code=%d)\033[0m\n", trap_code);
    }

    tfp->close();
    delete tfp;
    delete ctx;
    free(memory);
    return 0;
}