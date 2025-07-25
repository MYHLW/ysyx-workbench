// sdb.cpp
#include "sdb.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <map>
#include <cstdio>

// 定义全局变量（与 sdb.h 中的 extern 声明对应）
bool sim_done = false;
int trap_code = -1;
Vysyx_25020059_top dut;
VerilatedVcdC* tfp;
VerilatedContext* ctx;

uint64_t sim_cycle = 0;  // 局部全局变量（仅 sdb.cpp 使用）

// 单步执行一个时钟周期（复用之前的 single_cycle 逻辑）
static void single_cycle() {
    // 低电平阶段
    dut.clk = 0;
    dut.eval();  // 更新组合逻辑
    tfp->dump(ctx->time());
    ctx->timeInc(1);

    // 高电平阶段
    dut.clk = 1;
    dut.eval();  // 更新组合逻辑（含时序逻辑准备）
    tfp->dump(ctx->time());
    ctx->timeInc(1);

    sim_cycle++;
}

// 单步执行 steps 个周期
void cmd_si(int steps) {
    if (steps <= 0) steps = 1;
    for (int i = 0; i < steps && !sim_done; i++) {
        // 执行前打印当前状态
        printf("Cycle %llu: PC=0x%08X, inst=0x%08X\n",
               sim_cycle, (uint32_t)dut.curr_pc, dut.inst);
        single_cycle();
    }
}

// 继续运行直到陷阱
void cmd_continue() {
    printf("Continuing...\n");
    while (!sim_done) {
        printf("Cycle %llu: PC=0x%08X, inst=0x%08X\n",
               sim_cycle, (uint32_t)dut.curr_pc, dut.inst);
        single_cycle();
    }
}

// 查看寄存器（示例）
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
    printf("Commands:\n");
    printf("  si [n]   - Step n cycles (default 1)\n");
    printf("  c        - Continue until trap\n");
    printf("  info r   - Show registers\n");
    printf("  help     - Show this help\n");
    printf("  q        - Quit simulation\n");
}

// 命令映射表
static std::map<std::string, void(*)(const char*)> cmd_table = {
    {"si",    [](const char* args) { cmd_si(args ? atoi(args) : 1); }},
    {"c",     [](const char* args) { cmd_continue(); }},
    {"info r",[](const char* args) { cmd_info_reg(); }},
    {"help",  [](const char* args) { cmd_help(); }},
    {"q",     [](const char* args) { sim_done = true; }},
};

// 命令行主循环
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