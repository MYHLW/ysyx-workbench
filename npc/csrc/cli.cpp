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
#include <cstdint>

// 引用 main_new.cpp 中的全局变量
extern VerilatedContext* ctx;
extern VerilatedVcdC* tfp;
extern Vysyx_25020059_top dut;
extern bool sim_done;
extern int trap_code;
extern uint64_t sim_cycle;
extern uint8_t* memory;             // 仿真内存

// single_cycle 在 main_new.cpp 中实现
extern void single_cycle();

#define MEM_BASE 0x80000000U

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
     std::printf("  x addr(0x80000000) [n] - Scan memory: dump n words from addr (default n=1)\n");
     std::printf("  help     - Show this help\n");
     std::printf("  q        - Quit simulation\n");
 }

// “x” 命令：扫描内存，按 32 位字读取
void cmd_scan(const char* args) {
    if (!args) {
        std::printf("Usage: x <addr> [length]\n");
        return;
    }
    // 解析地址和长度
    char* token = std::strtok((char*)args, " ");
    uint32_t addr = std::strtoul(token, nullptr, 0);
    token = std::strtok(nullptr, " ");
    int len = token ? std::atoi(token) : 1;

    for (int i = 0; i < len; i++) {
        uint32_t a = addr + i * 4;
        uint32_t off = a - MEM_BASE;
        uint32_t data = *(uint32_t*)(memory + off);
        std::printf("0x%08X: 0x%08X\n", a, data);
    }
}

// 命令查找表
static std::map<std::string, void(*)(const char*)> cmd_table = {
    {"si",    cmd_si},
    {"c",     cmd_continue},
    {"info",  cmd_info},
    {"x",     cmd_scan},
    {"help",  cmd_help},
    {"q",     [](const char*) { sim_done = true; }}
};

// ===================DPI 端口===========================
extern "C" void npc_trap(int code) {
    if (!sim_done) {
        sim_done = true;
        trap_code = code;
    }
}

extern "C" uint32_t pmem_read(uint32_t vaddr) {
    uint32_t off = vaddr - MEM_BASE;
    return *(uint32_t*)(memory + off);
}
//=======================================================
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
