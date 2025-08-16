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
#define PRV_U 0   // User mode
#define PRV_S 1   // Supervisor mode
#define PRV_M 3   // Machine mode
#endif


word_t isa_raise_intr(word_t NO, vaddr_t epc) {
  cpu.mepc   = epc;
  cpu.mcause = NO; // 完整 mcause 编码

  // 2) MPIE <- MIE ; MIE <- 0
  if (cpu.mstatus & MSTATUS_MIE)
      cpu.mstatus |= MSTATUS_MPIE;  // trap 前允许中断
  else
      cpu.mstatus &= ~MSTATUS_MPIE;
  cpu.mstatus &= ~MSTATUS_MIE;

  // 3) 保存当前特权级到 MPP（PA不管priv，但要写入位）
  cpu.mstatus = (cpu.mstatus & ~MSTATUS_MPP_MASK) | (PRV_U << 11); // 假设 trap 从 U 模式
  // 如果是 S 模式 trap 就写 PRV_S，如果是 M 模式 trap 就写 PRV_M

  return cpu.mtvec; // trap 入口
}

word_t isa_query_intr() {
  return INTR_EMPTY;
}
