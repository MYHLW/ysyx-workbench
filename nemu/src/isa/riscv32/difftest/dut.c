/***************************************************************************************
* Copyright (c) 2014-2024 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include <isa.h>
#include <cpu/difftest.h>
#include "../local-include/reg.h"

#define ANSI_RED     "\033[31m"
#define ANSI_RESET   "\033[0m"

static const char *reg_names[] = {
  "x0", "ra", "sp", "gp", "tp", "t0", "t1", "t2",
  "s0", "s1", "a0", "a1", "a2", "a3", "a4", "a5",
  "a6", "a7", "s2", "s3", "s4", "s5", "s6", "s7",
  "s8", "s9", "s10", "s11", "t3", "t4", "t5", "t6"
};

bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) {
  int reg_num = ARRLEN(cpu.gpr);
  bool same = true;

  printf("\n==== Register Compare at PC = 0x%08lx ====\n", (unsigned long)pc);
  printf("%-4s %-12s %-12s %s\n", "Reg", "REF", "DUT", "Diff");
  printf("---------------------------------------------\n");

  for (int i = 0; i < reg_num; i++) {
    bool diff = (ref_r->gpr[i] != cpu.gpr[i]);
    if (diff) {
      same = false;
      printf("%-4s " ANSI_RED "0x%08x" ANSI_RESET "  " ANSI_RED "0x%08x" ANSI_RESET "  " ANSI_RED "<--" ANSI_RESET "\n",
             reg_names[i], ref_r->gpr[i], cpu.gpr[i]);
    } else {
      printf("%-4s 0x%08x  0x%08x\n", reg_names[i], ref_r->gpr[i], cpu.gpr[i]);
    }
  }

  // 最后比较 PC
  bool diff_pc = (ref_r->pc != cpu.pc);
  if (diff_pc) {
    same = false;
    printf("%-4s " ANSI_RED "0x%08x" ANSI_RESET "  " ANSI_RED "0x%08x" ANSI_RESET "  " ANSI_RED "<--" ANSI_RESET "\n",
           "pc", ref_r->pc, cpu.pc);
  } else {
    printf("%-4s 0x%08x  0x%08x\n", "pc", ref_r->pc, cpu.pc);
  }

  return same;
}

void isa_difftest_attach() {
}