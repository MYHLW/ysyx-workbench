// csrc/utils/disasm.h
#ifndef __DISASM_H__
#define __DISASM_H__

#include <cstdint>
#include <cstddef>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * 初始化反汇编器
 * 必须在其他函数前调用
 */
void init_disasm();

// /**
//  * 反汇编一条指令
//  * 
//  * @param str     输出缓冲区
//  * @param size    缓冲区大小
//  * @param pc      指令地址
//  * @param code    指令二进制数据
//  * @param nbyte   指令长度（字节）
//  */
void disassemble(char *str, size_t size, uint64_t pc, uint8_t *code, int nbyte);

#ifdef __cplusplus
}
#endif

#endif // __DISASM_H__