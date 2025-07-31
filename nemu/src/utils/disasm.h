#ifndef DISASM_H
#define DISASM_H

#include <stdint.h>
#include <stddef.h>

/*
 * 初始化反汇编器
 * 加载capstone库并配置适合当前ISA的反汇编环境
 */
void init_disasm();

/*
 * 反汇编一条指令并将结果写入字符串
 * @param str: 存储反汇编结果的缓冲区
 * @param size: 缓冲区大小
 * @param pc: 指令的程序计数器（地址）
 * @param code: 指令的二进制数据
 * @param nbyte: 指令的字节长度
 */
void disassemble(char *str, int size, uint64_t pc, uint8_t *code, int nbyte);

#endif // DISASM_H