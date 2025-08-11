#include "registers.h"
#include "cpu_state.h"
#include "cli.h"
#include "Vysyx_25020059_top.h"

#define REG_NUM 16
extern VerilatedContext* ctx;
extern VerilatedVcdC* tfp;
extern Vysyx_25020059_top dut;
const char *regs[] = {
    "$0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
    "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5"
} ;


void get_regs() {
    for (int i = 0; i < REG_NUM; i++) {
        cpu.gpr[i] = dut.reg_f[i];
    }
    cpu.pc = dut.curr_pc;
}