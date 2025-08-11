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

#ifndef __MEMORY_HOST_H__
#define __MEMORY_HOST_H__

#include <common.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static inline word_t host_read(void *addr, int len) {
  switch (len) {
    case 1: return *(uint8_t  *)addr;
    case 2: return *(uint16_t *)addr;
    case 4: //return *(uint32_t *)addr;printf("DEBUG: host_read called haddr=%p len=%d\n", haddr, len);
  fflush(stdout);

  if (addr == NULL) {
    fprintf(stderr, "ERROR: host_read haddr is NULL\n");
    fflush(stderr);
    abort();
  }

  // safety: use local buffer to avoid unaligned/unsafe direct deref
  uint8_t tmp[8] = {0};
  if (len < 0 || len > (int)sizeof(tmp)) {
    fprintf(stderr, "ERROR: host_read unexpected len=%d\n", len);
    fflush(stderr);
    abort();
  }
  // try to memcpy from host memory
  memcpy(tmp, addr, len);

  printf("DEBUG: host_read bytes:");
  for (int i = 0; i < len; i++) printf(" %02x", tmp[i]);
  printf("\n");
  fflush(stdout);

  word_t val = 0;
  for (int i = 0; i < len; i++) val |= (word_t)tmp[i] << (8 * i);
  printf("DEBUG: host_read returning 0x%016lx\n", (unsigned long)val);
  fflush(stdout);
  return val;
    IFDEF(CONFIG_ISA64, case 8: return *(uint64_t *)addr);
    default: MUXDEF(CONFIG_RT_CHECK, assert(0), return 0);
  }
}

static inline void host_write(void *addr, int len, word_t data) {
  switch (len) {
    case 1: *(uint8_t  *)addr = data; return;
    case 2: *(uint16_t *)addr = data; return;
    case 4: *(uint32_t *)addr = data; return;
    IFDEF(CONFIG_ISA64, case 8: *(uint64_t *)addr = data; return);
    IFDEF(CONFIG_RT_CHECK, default: assert(0));
  }
}

#endif
