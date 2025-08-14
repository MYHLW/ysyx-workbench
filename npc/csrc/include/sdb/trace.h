#ifndef __TRACE_H__
#define __TRACE_H__

void init_disasm();
void disassemble2(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);

#endif