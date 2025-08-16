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
  return cpu.mtvec;
  
}

word_t isa_query_intr() {
  return INTR_EMPTY;
}
