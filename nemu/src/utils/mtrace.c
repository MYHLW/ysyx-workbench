#ifdef CONFIG_MTRACE
#include <common.h>


void display_pread(paddr_t addr, int len) {
  printf("mtrace: read memory from 0x%08x, %d bytes\n", addr, len);
}

void display_pwrite(paddr_t addr, int len, word_t data) {
  printf("mtrace: write memory from 0x%08x, %d bytes, data: 0x%08x\n", addr, len, data);
}
#endif