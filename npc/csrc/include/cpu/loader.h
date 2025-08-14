#ifndef LOADER_H
#define LOADER_H

#include <cstdint>

// 声明外部依赖（来自main_new.cpp的全局变量和宏）
extern uint8_t memory[];
extern const uint32_t MEM_BASE;
extern const uint32_t MEM_SIZE;

// 加载程序（根据文件后缀自动选择方式）
void load_program(const char* filename);

#endif // LOADER_H