#ifndef __DIFFTEST_CHECK_H__
#define __DIFFTEST_CHECK_H__

#include "difftest/difftest-def.h"
#include "cpu_state.h"

bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc);
void isa_difftest_print_diff(CPU_state *ref_r, vaddr_t pc);

#endif