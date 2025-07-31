#include <am.h>
#include <klib-macros.h>

extern char _heap_start;
int main(const char *args);

extern char _pmem_start;
#define PMEM_SIZE (128 * 1024 * 1024)
#define PMEM_END  ((uintptr_t)&_pmem_start + PMEM_SIZE)

Area heap = RANGE(&_heap_start, PMEM_END);
#define MAINARGS_MAX_LEN 128
static const char mainargs[MAINARGS_MAX_LEN] = TOSTRING(MAINARGS_PLACEHOLDER); // defined in CFLAGS

void putch(char ch) {
  putchar(ch);
}

void halt(int code) {
  // 将 code 放到 a0
  asm volatile("mv a0, %0" :: "r"(code));
  // 触发 ebreak，NPC 会捕获并退出
  asm volatile("ebreak");
  while(1);
}


void _trm_init() {
  int ret = main(mainargs);
  halt(ret);
}
