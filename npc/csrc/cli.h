// csrc/cli.h
#pragma once

#include <cstdint>

// --- 对 main_new.cpp 中的全局变量、函数做 extern 声明 ---
class VerilatedContext;
class VerilatedVcdC;
class Vysyx_25020059_top;

extern VerilatedContext* ctx;
extern VerilatedVcdC* tfp;
extern Vysyx_25020059_top dut;
extern bool sim_done;
extern int trap_code;
extern uint64_t sim_cycle;

// single_cycle 在 main_new.cpp 中定义
extern void single_cycle();
//extern uint32_t pmem_read();
//extern inline uint32_t guest_to_host(uint32_t addr);

// 调试命令接口
void cmd_si(const char* args);
void cmd_continue(const char* args);
void cmd_info(const char* args);
void cmd_help(const char* args);
void sdb_mainloop();

// 来自 DPI 的陷阱回调
extern "C" void npc_trap(int code);
//extern "C" uint32_t pmem_read(uint32_t vaddr);
//=======================================================
