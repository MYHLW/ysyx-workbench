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
#include <cpu/cpu.h>
#include <difftest-def.h>
#include <memory/paddr.h>

__EXPORT void difftest_memcpy(paddr_t addr, void *buf, size_t n, bool direction) {
  if (direction == DIFFTEST_TO_REF) {
    memcpy(guest_to_host(addr), buf, n);
  } else {
    memcpy(buf, guest_to_host(addr), n);
  }
}

__EXPORT void difftest_regcpy(uint32_t *pc_out_or_in, uint32_t *gpr_buf, bool direction) {
    if (direction == DIFFTEST_TO_REF) {
        /* 从 NPC -> REF：把传入的 gpr/pc 写入 nemu cpu */
        for (int i = 0; i < 16; i++) cpu.gpr[i] = gpr_buf[i];
        cpu.pc = (uint32_t)(*pc_out_or_in);
        cpu.gpr[0] = 0; /* 确保 x0 = 0 */
    } else {
        /* 从 REF -> NPC：把 nemu cpu 的内容写回调用者提供的缓冲 */
        *pc_out_or_in = (uint32_t)cpu.pc;
        for (int i = 0; i < 16; i++) gpr_buf[i] = cpu.gpr[i];
    }
}

__EXPORT void difftest_exec(uint64_t n) {
  cpu_exec(n);
}

__EXPORT void difftest_raise_intr(word_t NO) {
  assert(0);
}

__EXPORT void difftest_init(int port) {
  void init_mem();
  init_mem();
  /* Perform ISA dependent initialization. */
  init_isa();
  // cpu.gpr[0]=0;
  // cpu.pc=RESET_VECTOR;
}
