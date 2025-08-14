#ifndef __DPI_FUNCTIONS_H__
#define __DPI_FUNCTIONS_H__

#include <cstdint>

#ifdef __cplusplus
extern "C" {
#endif
#define MEM_FAULT_CODE   0xdeadbeef  // 定义内存故障码
#define MEM_ACCESS_FAULT 1           // 定义内存访问错误trap码
extern void npc_trap(int code);
extern uint32_t pmem_read(uint32_t vaddr, int i);
extern void pmem_write(uint32_t vaddr, uint32_t data, int i);

#ifdef __cplusplus
}
#endif

#endif