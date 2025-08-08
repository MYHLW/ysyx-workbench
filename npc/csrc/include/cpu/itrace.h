#ifndef __ITRACE_H__
#define __ITRACE_H__    

// ----------- instruction trace -----------
#include "common.h"
//#ifdef CONFIG_ITRACE
#define MAX_IRINGBUF 16

typedef struct {
    uint64_t pc;
    uint32_t inst;
    char logbuf[128];
} ItraceNode;

extern ItraceNode iringbuf[MAX_IRINGBUF];
extern int p_cur;
extern bool full;

void trace_inst(word_t pc, uint32_t inst);
void display_inst();

#endif