// csrc/cli.cpp
#include "cli.h"
#include "Vysyx_25020059_top.h"
#include <verilated.h>
#include <verilated_vcd_c.h>
#include <verilated_dpi.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <map>
#include <cstring>
#include <cstdlib>
#include <cstdio>

// 引用 main_new.cpp 中的全局变量
extern VerilatedContext* ctx;
extern VerilatedVcdC* tfp;
extern Vysyx_25020059_top dut;
extern bool sim_done;
extern int trap_code;
extern uint64_t sim_cycle;

// single_cycle 在 main_new.cpp 中实现
extern void single_cycle();

// “si” 命令：单步 n 周期
void cmd_si(const char* args) {
    int steps = args ? std::atoi(args) : 1;
    if (steps <= 0) {
        std::printf("Invalid steps: %d\n", steps);
        return;
    }
    for (int i = 0; i < steps && !sim_done; i++) {
        single_cycle();
        std::printf("PC=0x%08X, inst=0x%08X\n", dut.curr_pc, dut.inst);
    }
}

// “c” 命令：继续运行直到陷阱
void cmd_continue(const char* /*args*/) {
    std::printf("Continuing...\n");
    while (!sim_done) {
        single_cycle();
        std::printf("PC=0x%08X, inst=0x%08X\n", dut.curr_pc, dut.inst);
    }
}

// “info” 命令：打印寄存器
void cmd_info(const char* /*args*/) {
    std::printf("Registers:\n");
    for (int i = 0; i < 32; i++) {
        std::printf("x%02d: 0x%08X  ", i, (uint32_t)dut.reg_f[i]);
        if ((i + 1) % 4 == 0) std::printf("\n");
    }
    std::printf("\n");
}

// “help” 命令
void cmd_help(const char* /*args*/) {
    std::printf("Supported commands:\n");
    std::printf("  si [n]   - Step n cycles (default 1)\n");
    std::printf("  c        - Continue until trap\n");
    std::printf("  info     - Show registers\n");
    std::printf("  help     - Show this help\n");
    std::printf("  q        - Quit simulation\n");
}

// 命令查找表
static std::map<std::string, void(*)(const char*)> cmd_table = {
    {"si",    cmd_si},
    {"c",     cmd_continue},
    {"info",  cmd_info},
    {"help",  cmd_help},
    {"q",     [](const char*) { sim_done = true; }}
};

// DPI 端口：trap 回调
extern "C" void npc_trap(int code) {
    if (!sim_done) {
        sim_done = true;
        trap_code = code;
    }
}

// 主循环
void sdb_mainloop() {
    std::printf("NPC debugger started. Type 'help' for commands.\n");
    while (!sim_done) {
        char* line = readline("(npc) ");
        if (!line) break;
        if (line[0]) add_history(line);

        char* cmd = std::strtok(line, " ");
        char* args = std::strtok(nullptr, "");
        if (cmd) {
            auto it = cmd_table.find(cmd);
            if (it != cmd_table.end()) {
                it->second(args);
            } else {
                std::printf("Unknown command: %s\n", cmd);
            }
        }
        std::free(line);
    }
}
