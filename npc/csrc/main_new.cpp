#include "Vysyx_25020059_top.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include <verilated_dpi.h>

// 命令行交互相关头文件
#include <readline/readline.h>
#include <readline/history.h>
#include <map>

// 全局指针声明（替代参数传递）
static VerilatedContext* ctx = nullptr;    // 仿真上下文全局指针
static VerilatedVcdC* tfp = nullptr;       // 波形文件全局指针


// 仿真控制全局变量
static bool sim_done = false;              // 仿真结束标志
static int trap_code = -1;                 // 陷阱代码
static uint64_t sim_cycle = 0;             // 仿真周期计数

// 仿真内存配置
#define MEM_BASE       0x80000000U
#define MEM_SIZE       (8 * 1024 * 1024)    // 8MB
static Vysyx_25020059_top dut;             // DUT实例
static uint8_t* memory = nullptr;           // 仿真内存

// 函数声明
void single_cycle();                        // 单周期执行（无参数）
void reset(int n);                          // 复位函数（无参数）
void cmd_si(int steps);                     // 单步执行
void cmd_continue();                        // 继续运行
void cmd_info_reg();                        // 查看寄存器
void cmd_help();                            // 帮助命令
void sdb_mainloop();                        // 命令行主循环

// 虚拟地址转内存偏移
static inline uint32_t guest_to_host(uint32_t addr) {
    return addr - MEM_BASE;
}

// 从仿真内存读取指令
uint32_t pmem_read(uint32_t* /*unused*/, uint32_t vaddr) {
    uint32_t off = guest_to_host(vaddr);
    return *(uint32_t*)(memory + off);
}

// 加载程序镜像到内存
void load_image(const char* filename) {
    FILE* fp = fopen(filename, "rb");
    if (!fp) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    size_t sz = fread(memory, 1, MEM_SIZE, fp);
    fclose(fp);
    printf("Loaded binary '%s' (%zu bytes) at 0x%08X\n", filename, sz, MEM_BASE);
}

// 单周期执行（使用全局指针，无需参数）
void single_cycle() {
    dut.clk = 0;
    dut.eval();
    tfp->dump(ctx->time());  // 使用全局tfp和ctx
    ctx->timeInc(1);
    dut.clk = 1;
    dut.eval();
    dut.inst = pmem_read(nullptr, dut.curr_pc);  // 提取指令
    tfp->dump(ctx->time());
    ctx->timeInc(1);

    sim_cycle++;
}

// 复位n个周期（使用全局指针）
void reset(int n) {
    dut.rst = 1;
    while (n-- > 0) single_cycle();  // 直接调用单周期函数，无需传参
    dut.rst = 0;
}

// DPI回调：处理ebreak陷阱
extern "C" void npc_trap(int code) {
    if (!sim_done) {
        sim_done = true;
        trap_code = code;
    }
}

// 命令映射表
std::map<std::string, void(*)(const char*)> cmd_table = {
    {"si",    [](const char* args) { cmd_si(args ? atoi(args) : 1); }},
    {"c",     [](const char* args) { cmd_continue(); }},
    {"info r",[](const char* args) { cmd_info_reg(); }},
    {"help",  [](const char* args) { cmd_help(); }},
    {"q",     [](const char* args) { sim_done = true; }},
};

// 单步执行n个周期
void cmd_si(int steps = 1) {
    if (steps <= 0) {
        printf("Invalid steps: %d\n", steps);
        return;
    }
    for (int i = 0; i < steps && !sim_done; i++) {
        single_cycle();  // 无参数调用
        printf("PC=0x%08X, inst=0x%08X\n",dut.curr_pc, dut.inst);
    }
}


// 继续运行直到陷阱
void cmd_continue() {
    printf("Continuing...\n");
    while (!sim_done) {
        single_cycle();  // 无参数调用
        printf("PC=0x%08X, inst=0x%08X\n",dut.curr_pc, dut.inst);
    }
}

// 查看寄存器状态
void cmd_info_reg() {
    printf("Registers:\n");
    for (int i = 0; i < 32; i++) {
        printf("x%02d: 0x%08X  ", i, (uint32_t)dut.reg_f[i]);
        if ((i + 1) % 4 == 0) printf("\n");
    }
    printf("\n");
}

// 帮助命令
void cmd_help() {
    printf("Supported commands:\n");
    printf("  si [n]   - Step n cycles (default 1)\n");
    printf("  c        - Continue until trap\n");
    printf("  info r   - Show registers\n");
    printf("  help     - Show this help\n");
    printf("  q        - Quit simulation\n");
}

// 命令行交互主循环
void sdb_mainloop() {
    printf("NPC debugger started. Type 'help' for commands.\n");
    while (!sim_done) {
        char* line = readline("(npc) ");
        if (!line) break;
        if (line[0] != '\0') add_history(line);

        char* cmd = strtok(line, " ");
        char* args = strtok(nullptr, "");

        if (cmd) {
            auto it = cmd_table.find(cmd);
            if (it != cmd_table.end()) {
                it->second(args);
            } else {
                printf("Unknown command: %s\n", cmd);
            }
        }
        free(line);
    }
}

// 主函数
int main(int argc, char**argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <program.bin>\n", argv[0]);
        return -1;
    }

    // 初始化内存
    memory = (uint8_t*)malloc(MEM_SIZE);
    if (!memory) { perror("malloc"); return -1; }
    memset(memory, 0, MEM_SIZE);
    load_image(argv[1]);

    // 初始化全局指针（关键：为全局ctx和tfp分配内存）
    ctx = new VerilatedContext;
    tfp = new VerilatedVcdC;

    // 波形配置
    Verilated::traceEverOn(true); // Correctly called inside main before tracing
    dut.trace(tfp, 5);
    tfp->open("Vysyx_25020059.vcd");

    // 复位CPU
    reset(2);

    // 启动命令行交互
    sdb_mainloop();

    // 仿真结束清理
    printf("\n");
    if (trap_code == 0) {
        printf("\033[32m[NPC] HIT GOOD TRAP: program exited successfully.\033[0m\n");
    } else {
        printf("\033[31m[NPC] HIT BAD TRAP: program failed (code=%d).\033[0m\n", trap_code);
    }

    tfp->close();
    delete tfp;   // 释放全局指针
    delete ctx;   // 释放全局指针
    free(memory);
    return 0;
}
