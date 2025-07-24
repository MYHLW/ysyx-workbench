#include <am.h>
#include <klib-macros.h>

extern char _heap_start;
int main(const char *args);

extern char _pmem_start;
#define PMEM_SIZE (128 * 1024 * 1024)
#define PMEM_END  ((uintptr_t)&_pmem_start + PMEM_SIZE)

Area heap = RANGE(&_heap_start, PMEM_END);
static const char mainargs[MAINARGS_MAX_LEN] = MAINARGS_PLACEHOLDER; // defined in CFLAGS

void putch(char ch) {
}

// void halt(int code) {
//   asm volatile("ebreak");
//   while (1);
// }

// 改为直接发出 ebreak，用 a0 寄存器携带退出 code
void halt(int code) {
  // 将 code 放到 a0
  asm volatile("mv a0, %0" :: "r"(code));
  // 触发环境断点，RTL 捕捉后会调用 npc_trap(code)
  asm volatile("ebreak");
  // 如果 trap 失效，防止继续向下执行
  while (1);
}

void _trm_init() {
  int ret = main(mainargs);
  halt(ret);
}
