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

#ifndef PRV_M
#define PRV_M 3
#endif

word_t isa_raise_intr(word_t NO, vaddr_t epc) {
  /* 1) 保存 mepc / mcause */
  cpu.mepc = epc;
  cpu.mcause = NO; /* NO 应当是完整 mcause 编码（含 interrupt 位） */
  #ifdef CONFIG_ETRACE
    printf("\n[etrace] Trap! mcause = 0x%x, mepc = 0x%x\n", cpu.mcause, cpu.mepc);
  #endif
  // 更新 mstatus
  word_t mstatus = cpu.mstatus;
  // 1. 保存中断使能位
  uint32_t mie = (mstatus >> 3) & 0x1;
  mstatus = (mstatus & ~(1 << 7)) | (mie << 7);  // MPIE <- MIE
  mstatus &= ~(1 << 3);  // MIE <- 0
  // 2. 保存当前特权级
  uint32_t prev_mode = (cpu.mstatus >> 10) & 0x3; // 你的模式字段
  mstatus = (mstatus & ~(3 << 11)) | (prev_mode << 11); // MPP <- mode
  cpu.mstatus = mstatus;
  return cpu.mtvec;
  
}

word_t isa_query_intr() {
  return INTR_EMPTY;
}
