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
#include <stdio.h>
#include <stdbool.h>

bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) {
  bool same = true;

  printf("\n[DIFFTEST] PC = 0x%08x\n", pc);
  printf("-------------------------------------------------------------------\n");
  printf("| %-3s |      DUT (NEMU)     |      REF (Other)    | Status  |\n", "Reg");
  printf("-------------------------------------------------------------------\n");

  for (int i = 0; i < 32; i++) {
    bool diff = (cpu.gpr[i] != ref_r->gpr[i]);
    if (diff) same = false;

    printf("| %-3s | 0x%08x         | 0x%08x         | %s%-7s\033[0m |\n",
           reg_name(i),                // 只传 idx
           cpu.gpr[i],                  // word_t == unsigned int
           ref_r->gpr[i],
           diff ? "\033[1;31m" : "\033[1;32m",
           diff ? "DIFF" : "OK");
  }

  // 检查 PC
  bool pc_diff = (cpu.pc != ref_r->pc);
  if (pc_diff) same = false;

  printf("-------------------------------------------------------------------\n");
  printf("| %-3s | 0x%08x         | 0x%08x         | %s%-7s\033[0m |\n",
         "pc",
         cpu.pc,
         ref_r->pc,
         pc_diff ? "\033[1;31m" : "\033[1;32m",
         pc_diff ? "DIFF" : "OK");
  printf("-------------------------------------------------------------------\n\n");

  return same;
}

void isa_difftest_attach() {
}
