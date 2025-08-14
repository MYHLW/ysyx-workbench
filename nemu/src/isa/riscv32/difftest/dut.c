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

/* 比较寄存器并返回是否完全相同（不做任何打印） */
bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) {
  /* 比较通用寄存器 */
  for (int i = 0; i < 32; i++) {
    if (cpu.gpr[i] != ref_r->gpr[i]) return false;
  }

  /* 比较 PC */
  if (cpu.pc != ref_r->pc) return false;

  /* 比较常用 CSR（若你的 CPU_state 包含这些字段） */
  if (cpu.mstatus != ref_r->mstatus) return false;
  if (cpu.mcause  != ref_r->mcause)  return false;
  if (cpu.mepc    != ref_r->mepc)    return false;
  if (cpu.mtvec   != ref_r->mtvec)   return false;

  return true;
}

void isa_difftest_attach() {
}

/* 打印差异表格（在比较失败时调用） */
void isa_difftest_print_diff(CPU_state *ref_r, vaddr_t pc) {
  printf("\n[DIFFTEST] PC = 0x%08x\n", (unsigned)pc);
  printf("-------------------------------------------------------------------\n");
  printf("| %-3s |      DUT (NEMU)     |      REF (Other)    | Status  |\n", "Reg");
  printf("-------------------------------------------------------------------\n");

  for (int i = 0; i < 32; i++) {
    bool diff = (cpu.gpr[i] != ref_r->gpr[i]);

    printf("| %-3s | 0x%08x         | 0x%08x         | %s%-7s\033[0m |\n",
           reg_name(i),
           (unsigned)cpu.gpr[i],
           (unsigned)ref_r->gpr[i],
           diff ? "\033[1;31m" : "\033[1;32m",
           diff ? "DIFF" : "OK");
  }

  /* PC 行 */
  bool pc_diff = (cpu.pc != ref_r->pc);
  printf("-------------------------------------------------------------------\n");
  printf("| %-3s | 0x%08x         | 0x%08x         | %s%-7s\033[0m |\n",
         "pc",
         (unsigned)cpu.pc,
         (unsigned)ref_r->pc,
         pc_diff ? "\033[1;31m" : "\033[1;32m",
         pc_diff ? "DIFF" : "OK");

  /* CSR 行：mstatus, mcause, mepc, mtvec */
  bool mstatus_diff = (cpu.mstatus != ref_r->mstatus);
  printf("| %-3s | 0x%08x         | 0x%08x         | %s%-7s\033[0m |\n",
         "mst",
         (unsigned)cpu.mstatus,
         (unsigned)ref_r->mstatus,
         mstatus_diff ? "\033[1;31m" : "\033[1;32m",
         mstatus_diff ? "DIFF" : "OK");

  bool mcause_diff = (cpu.mcause != ref_r->mcause);
  printf("| %-3s | 0x%08x         | 0x%08x         | %s%-7s\033[0m |\n",
         "mca",
         (unsigned)cpu.mcause,
         (unsigned)ref_r->mcause,
         mcause_diff ? "\033[1;31m" : "\033[1;32m",
         mcause_diff ? "DIFF" : "OK");

  bool mepc_diff = (cpu.mepc != ref_r->mepc);
  printf("| %-3s | 0x%08x         | 0x%08x         | %s%-7s\033[0m |\n",
         "mep",
         (unsigned)cpu.mepc,
         (unsigned)ref_r->mepc,
         mepc_diff ? "\033[1;31m" : "\033[1;32m",
         mepc_diff ? "DIFF" : "OK");

  bool mtvec_diff = (cpu.mtvec != ref_r->mtvec);
  printf("| %-3s | 0x%08x         | 0x%08x         | %s%-7s\033[0m |\n",
         "mtv",
         (unsigned)cpu.mtvec,
         (unsigned)ref_r->mtvec,
         mtvec_diff ? "\033[1;31m" : "\033[1;32m",
         mtvec_diff ? "DIFF" : "OK");

  printf("-------------------------------------------------------------------\n\n");
}
