#include <am.h>
#include <klib.h>
#include <klib-macros.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)
static unsigned long int next = 1;

int rand(void) {
  // RAND_MAX assumed to be 32767
  next = next * 1103515245 + 12345;
  return (unsigned int)(next/65536) % 32768;
}

void srand(unsigned int seed) {
  next = seed;
}

int abs(int x) {
  return (x < 0 ? -x : x);
}

int atoi(const char* nptr) {
  int x = 0;
  while (*nptr == ' ') { nptr ++; }
  while (*nptr >= '0' && *nptr <= '9') {
    x = x * 10 + *nptr - '0';
    nptr ++;
  }
  return x;
}

// ============ malloc/free 实现部分 ============

extern char _heap_start; 
extern char _heap_end;  

static char *heap_end = &_heap_start;  // 当前指向“未分配区域的起始地址”

void *malloc(size_t size) {
  // 简单对齐：8 字节对齐
  size = (size + 7) & ~7;

  char *old = heap_end;
  char *new_end = old + size;

#ifdef _heap_end
  if (new_end > &_heap_end) {
    panic("Out of heap memory: tried to malloc %d bytes", size);
  }
#endif

  heap_end = new_end;
  return old;
}

void free(void *ptr) {
  // 不释放内存
}

#endif
