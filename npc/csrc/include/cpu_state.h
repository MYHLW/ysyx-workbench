#ifndef __CPU_STATE_H__
#define __CPU_STATE_H__

#include <stdint.h>

typedef struct {
  uint32_t gpr[32];
  uint32_t pc;
} CPU_state;

extern CPU_state cpu; // 当前 CPU 状态
#endif