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
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stddef.h>

__EXPORT void difftest_memcpy(paddr_t addr, void *buf, size_t n, bool direction) {
  if (direction == DIFFTEST_TO_REF) {
    memcpy(guest_to_host(addr), buf, n);
  } else {
    memcpy(buf, guest_to_host(addr), n);
  }
}

__EXPORT void difftest_regcpy(void *dut, bool direction) {
  fprintf(stderr, "[NEMU DEBUG] difftest_regcpy called: dut=%p dir=%d DIFFTEST_REG_SIZE=%d sizeof(cpu)=%zu &cpu=%p\n",
          dut, (int)direction, (int)DIFFTEST_REG_SIZE, sizeof(cpu), (void*)&cpu);
  fflush(stderr);

  if (dut == NULL) {
    fprintf(stderr, "[NEMU DEBUG] dut == NULL !\n");
    fflush(stderr);
    return;
  }

  /* 为安全起见，先把用户缓冲区拷到本地堆栈/堆缓冲区并打印前几个 word（只读） */
  uint8_t *tmp = malloc(DIFFTEST_REG_SIZE);
  if (!tmp) {
    fprintf(stderr, "[NEMU DEBUG] malloc failed\n");
    fflush(stderr);
    return;
  }
  /* 注意：如果 'dut' 指向的内存不可读，下面 memcpy 会在这里崩溃 —— 这有助定位问题 */
  memcpy(tmp, dut, DIFFTEST_REG_SIZE);

  /* 打印前 4 words 以便比对 */
  uint32_t *words = (uint32_t *)tmp;
  fprintf(stderr, "[NEMU DEBUG] received words: %08x %08x %08x %08x\n",
          words[0], words[1], words[2], words[3]);
  fflush(stderr);

  if (direction == DIFFTEST_TO_REF) {
    /* 真正拷贝到 cpu（现在将来自 tmp 的数据复制到 cpu） */
    memcpy(&cpu, tmp, DIFFTEST_REG_SIZE);
  } else {
    memcpy(tmp, &cpu, DIFFTEST_REG_SIZE);
    memcpy(dut, tmp, DIFFTEST_REG_SIZE);
  }

  free(tmp);
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
}
