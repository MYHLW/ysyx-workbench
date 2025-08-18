#ifndef __DIFFTEST_CHECK_H__
#define __DIFFTEST_CHECK_H__

#include "difftest/difftest-def.h"
#include "cpu_state.h"

bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc);
void isa_difftest_print_diff(CPU_state *ref_r, vaddr_t pc);
void difftest_skip_ref();
void difftest_skip_dut(int nr_ref, int nr_dut);
void isa_difftest_attach();

extern volatile bool need_difftest_skip_ref;

#endif