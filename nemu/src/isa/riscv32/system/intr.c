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

#ifndef MSTATUS_MIE
#define MSTATUS_MIE       (1UL << 3)
#endif
#ifndef MSTATUS_MPIE
#define MSTATUS_MPIE      (1UL << 7)
#endif
#ifndef MSTATUS_MPP_MASK
#define MSTATUS_MPP_MASK  (3UL << 11)
#endif

#ifndef PRV_U
#define PRV_U 0
#define PRV_S 1
#define PRV_M 3
#endif
extern int current_priv; // 当前特权级，初始为 Machine 模式

word_t isa_raise_intr(word_t NO, vaddr_t epc) {
  /* 1) 保存 mepc / mcause */
  cpu.mepc = epc;
  cpu.mcause = NO;

#ifdef CONFIG_ETRACE
  printf("\n[etrace] Trap! mcause = 0x%x, mepc = 0x%x\n", cpu.mcause, cpu.mepc);
#endif

  /* 2) MPIE <- MIE ; MIE <- 0 */
  if (cpu.mstatus & MSTATUS_MIE) cpu.mstatus |= MSTATUS_MPIE;
  else                           cpu.mstatus &= ~MSTATUS_MPIE;
  cpu.mstatus &= ~MSTATUS_MIE;

  /* 3) 保存当前特权级到 MPP 并切到 Machine （使用全局 current_priv）*/
  cpu.mstatus = (cpu.mstatus & ~MSTATUS_MPP_MASK) | ((word_t)(current_priv & 0x3) << 11);
  current_priv = PRV_M; /* 切换到 Machine 模式 */

  /* 4) 根据 mtvec.mode 计算 trap 入口 (direct/vectored) */
  word_t mtvec = cpu.mtvec;
  word_t mode = mtvec & 0x3;        /* low 2 bits are mode */
  word_t base = mtvec & ~((word_t)0x3);
  word_t trap_pc;
  if (mode == 1) { /* VECTORED: base + 4 * cause_index (cause low bits) */
    int xlen = sizeof(word_t) * 8;
    word_t cause_index = cpu.mcause & (~((word_t)1 << (xlen-1)));
    trap_pc = base + 4 * cause_index;
  } else { /* DIRECT or reserved -> base */
    trap_pc = base;
  }

  return trap_pc;
}

word_t isa_query_intr() {
  return INTR_EMPTY;
}
