// csrc/utils/itrace.h
#ifndef __ITRACE_H__
#define __ITRACE_H__

#include <cstdint>

// 初始化 itrace 系统
void init_itrace();

// 记录一条指令到环形缓冲区
void itrace_record(uint64_t pc, uint32_t inst);

// 打印环形缓冲区中的指令历史
void itrace_print_history();

// 设置是否启用指令记录
void itrace_set_enabled(bool enabled);

// 检查是否启用了指令记录
bool itrace_is_enabled();

#endif