// csrc/cli.cpp
#include "cli.h"
#include "registers.h"
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
#include "trace/trace.h"

// 引用 main_new.cpp 中的全局变量
extern VerilatedContext* ctx;
extern VerilatedVcdC* tfp;
extern Vysyx_25020059_top dut;
extern bool sim_done;
extern int trap_code;
extern uint64_t sim_cycle;
// 原错误声明（指针类型，与main_new中数组不匹配）
// extern uint8_t* memory;             // 仿真内存

// 修正后（数组类型，匹配main_new中的static uint8_t memory[MEM_SIZE]）
extern uint8_t memory[];             // 仿真内存（数组形式外部引用）        // 仿真内存

// single_cycle 在 main_new.cpp 中实现
extern void single_cycle();
void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);
void difftest_step(vaddr_t pc, vaddr_t npc);


// “si” 命令：单步 n 周期
void cmd_si(const char* args) {
    int steps = args ? std::atoi(args) : 1;
    if (steps <= 0) {
        std::printf("Invalid steps: %d\n", steps);
        return;
    }

    static bool disasm_inited = false;
    if (!disasm_inited) {
        init_disasm();
        disasm_inited = true;
    }

    for (int i = 0; i < steps && !sim_done; i++) {
        single_cycle();

        uint32_t pc = (uint32_t)dut.curr_pc;
        uint32_t inst = (uint32_t)dut.inst;

        // 将 inst 拷成字节数组传给 capstone（明确字节序）
        uint8_t code[4];
        std::memcpy(code, &inst, sizeof(inst)); 

        char asm_buf[128] = {0};
        disassemble(asm_buf, sizeof(asm_buf), (uint64_t)pc, code, 4);

        std::printf("0x%08X: %08x  %s\n", pc, inst, asm_buf);
    }
}

// “c” 命令：继续运行直到陷阱
void cmd_continue(const char* /*args*/) {
    std::printf("Continuing...\n");
    while (!sim_done) {
        single_cycle();
        //std::printf("PC=0x%08X, inst=0x%08X\n", dut.curr_pc, dut.inst);
    }
}

// “info” 命令：打印寄存器
void cmd_info(const char* /*args*/) {
    static const char* reg_names[32] = {
        "$0",  "ra",  "sp",  "gp",  "tp",  "t0",  "t1",  "t2",
        "s0",  "s1",  "a0",  "a1",  "a2",  "a3",  "a4",  "a5",
        "a6",  "a7",  "s2",  "s3",  "s4",  "s5",  "s6",  "s7",
        "s8",  "s9",  "s10", "s11", "t3",  "t4",  "t5",  "t6"
    };

    std::printf("Register Information:\n");
    std::printf("pc     0x%08X\n", (uint32_t)dut.curr_pc);
    for (int i = 0; i < 16; i++) {
        std::printf("%-5s  0x%08X\n", reg_names[i], (uint32_t)dut.reg_f[i]);
    }
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
