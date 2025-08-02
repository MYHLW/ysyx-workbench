#ifndef __TRACE_H__
#define __TRACE_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

// 环形缓冲区大小
#define IRINGBUF_SIZE 16

// 指令追踪结构体
typedef struct {
    uint64_t pc;
    uint32_t inst;
    char disasm[128];
} InstTrace;

// 环形缓冲区
extern InstTrace iringbuf[IRINGBUF_SIZE];
extern int iringbuf_index;

// 追踪功能开关
extern bool enable_itrace;
extern bool enable_mtrace;
extern bool enable_ftrace;

// 追踪函数声明
void init_trace();
void trace_instruction(uint64_t pc, uint32_t inst);
void trace_memory(bool is_write, uint64_t addr, uint64_t data, uint8_t len);
void trace_function(uint64_t pc, bool is_call, const char* func_name);
void print_iringbuf();

#endif