#ifndef __CPU_OPERATIONS_H__
#define __CPU_OPERATIONS_H__

#include "../dpi/dpi_functions.h"
#include <cstdint>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include "Vysyx_25020059_top.h"
#include "cpu_state.h"


extern Vysyx_25020059_top dut;
extern VerilatedContext* ctx;
extern VerilatedVcdC* tfp;
extern bool sim_done;
extern int trap_code;
extern uint64_t sim_cycle;

extern const uint32_t MEM_BASE;
extern const uint32_t MEM_SIZE;
extern uint8_t memory[];

extern CPU_state cpu;
extern void get_regs();

#define MAX_CYCLE 1000000000
void init_cycle();  // 初始化周期
void single_cycle();
void reset(int n);

#endif