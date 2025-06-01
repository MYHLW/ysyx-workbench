// /***************************************************************************************
// * Copyright (c) 2014-2024 Zihao Yu, Nanjing University
// *
// * NEMU is licensed under Mulan PSL v2.
// * You can use this software according to the terms and conditions of the Mulan PSL v2.
// * You may obtain a copy of Mulan PSL v2 at:
// *          http://license.coscl.org.cn/MulanPSL2
// *
// * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// *
// * See the Mulan PSL v2 for more details.
// ***************************************************************************************/

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <fcntl.h>
// #include <unistd.h>
// #include "utils.h"
// #include "elf.h"
// #include "cpu/decode.h"
// #include "local-include/reg.h"
// #include <cpu/cpu.h>
// #include <cpu/ifetch.h>
// #include <cpu/decode.h>


// /* ELF 文件数据和符号表 */
// static uint8_t *elf_data = NULL;
// static size_t elf_size = 0;
// static Elf32_Sym *symtab = NULL;
// static char *strtab = NULL;
// static int symtab_count = 0;

// extern char *elf_file;  // ELF 文件路径，需在其他地方定义
// /* 调用栈和深度 */
// #define MAX_STACK_DEPTH 100
// static vaddr_t call_stack[MAX_STACK_DEPTH];
// static int stack_depth = 0;

// /* 初始化函数跟踪 */
// bool init_ftrace() {
//     #ifdef CONFIG_FTRACE
//     if (!elf_file) {
//         Log("ELF file not specified for function tracing");
//         return false;
//     }

//     int fd = open(elf_file, O_RDONLY);
//     if (fd < 0) {
//         perror("Failed to open ELF file");
//         return false;
//     }

//     /* 获取文件大小 */
//     elf_size = lseek(fd, 0, SEEK_END);
//     lseek(fd, 0, SEEK_SET);

//     /* 读取 ELF 文件内容 */
//     elf_data = malloc(elf_size);
//     if (read(fd, elf_data, elf_size) != elf_size) {
//         perror("Failed to read ELF file");
//         free(elf_data);
//         close(fd);
//         return false;
//     }
//     close(fd);

//     /* 解析 ELF 头 */
//     Elf32_Ehdr *ehdr = (Elf32_Ehdr *)elf_data;

//     /* 验证是否为 ELF 文件 */
//     if (memcmp(ehdr->e_ident, ELFMAG, SELFMAG) != 0) {
//         printf("Not an ELF file\n");
//         free(elf_data);
//         return false;
//     }

//     /* 验证架构是否为 RISC-V */
//     if (ehdr->e_machine != EM_RISCV) {
//         printf("Not a RISC-V ELF file\n");
//         free(elf_data);
//         return false;
//     }

//     /* 查找符号表和字符串表 */
//     Elf32_Shdr *shdr = (Elf32_Shdr *)(elf_data + ehdr->e_shoff);
//     char *shstrtab = (char *)(elf_data + shdr[ehdr->e_shstrndx].sh_offset);

//     int symtab_idx = -1, strtab_idx = -1;

//     for (int i = 0; i < ehdr->e_shnum; i++) {
//         if (shdr[i].sh_type == SHT_SYMTAB || shdr[i].sh_type == SHT_DYNSYM) {
//             symtab_idx = i;
//         }
//         if (symtab_idx >= 0 && shdr[i].sh_type == SHT_STRTAB && 
//             shdr[symtab_idx].sh_link == i) {
//             strtab_idx = i;
//         }
//     }

//     if (symtab_idx < 0 || strtab_idx < 0) {
//         printf("ELF file does not contain symbol table\n");
//         free(elf_data);
//         return false;
//     }

//     /* 获取符号表和字符串表 */
//     symtab = (Elf32_Sym *)(elf_data + shdr[symtab_idx].sh_offset);
//     strtab = (char *)(elf_data + shdr[strtab_idx].sh_offset);
//     symtab_count = shdr[symtab_idx].sh_size / sizeof(Elf32_Sym);

//     Log("Function tracing initialized with %d symbols", symtab_count);
//     return true;
//     #else
//     return false;
//     #endif
// }

// /* 查找地址对应的符号名 */
// const char *lookup_symbol(vaddr_t addr) {
//     #ifdef CONFIG_FTRACE
//     static char addr_str[20];

//     /* 线性查找最接近的函数符号 */
//     vaddr_t best_offset = ~0;
//     const char *best_name = NULL;

//     for (int i = 0; i < symtab_count; i++) {
//         if (ELF32_ST_TYPE(symtab[i].st_info) == STT_FUNC &&
//             symtab[i].st_value <= addr &&
//             addr - symtab[i].st_value < best_offset) {
//             best_offset = addr - symtab[i].st_value;
//             best_name = strtab + symtab[i].st_name;
//         }
//     }

//     if (best_name) {
//         return best_name;
//     }

//     /* 如果没找到，返回地址的字符串表示 */
//     snprintf(addr_str, sizeof(addr_str), "0x%08x", addr);
//     return addr_str;
//     #else
//     return "unknown";
//     #endif
// }

// /* 检查是否为函数返回指令 */
// bool is_function_return(Decode *s) {
//     #ifdef CONFIG_FTRACE
//     uint32_t instr = s->isa.inst;
//     /* 函数返回通常是 jalr x0, x1, 0 (ret) */
//     return (instr & 0x7F) == 0x67 &&  /* JALR 指令 */
//            ((instr >> 15) & 0x1F) == 1 &&  /* rs1 = x1 */
//            ((instr >> 7) & 0x1F) == 0;     /* rd = x0 */
//     #else
//     return false;
//     #endif
// }

// /* 获取指令的助记符 */
// const char *get_instr_mnemonic(Decode *s) {
//     #ifdef CONFIG_FTRACE
//     // 简化版：从logbuf中提取助记符
//     char *p = s->logbuf;
//     while (*p && (*p == ' ' || *p == '\t')) p++; // 跳过前导空格
//     char *start = p;
//     while (*p && !(*p == ' ' || *p == '\t')) p++;
//     if (p > start) {
//         static char mnemonic[16];
//         strncpy(mnemonic, start, p - start);
//         mnemonic[p - start] = '\0';
//         return mnemonic;
//     }
//     return "unknown";
//     #else
//     return "unknown";
//     #endif
// }

// /* 在指令执行前进行跟踪 */
// void ftrace_before_execution(Decode *s) {
//     #ifdef CONFIG_FTRACE
//     uint32_t instr = s->isa.inst;
//     vaddr_t pc = s->pc;
//     vaddr_t next_pc = s->snpc;
    
//     /* 检查是否为 JAL 指令 */
//     if ((instr & 0x7F) == 0x6F) {  /* JAL */
//         int rd = (instr >> 7) & 0x1F;
//         /* 计算JAL目标地址 */
//         vaddr_t target = pc + ((instr & 0x80000000) ? 0xFFF00000 : 0) |
//                         ((instr & 0x000FF000) >> 12) |
//                         ((instr & 0x00100000) >> 9) |
//                         ((instr & 0x7FE00000) >> 20);
        
//         const char *func_name = lookup_symbol(target);
//         const char *mnemonic = get_instr_mnemonic(s);
        
//         /* 记录调用栈 */
//         if (stack_depth < MAX_STACK_DEPTH - 1) {
//             call_stack[stack_depth++] = next_pc;
//         }
        
//         /* 输出调用信息 */
//         printf("%*sCALL %-15s (0x%08x) <- %-15s (0x%08x) [rd=%d]\n", 
//                stack_depth * 2, "", 
//                func_name, target,
//                lookup_symbol(pc), pc, rd);
//     }
//     /* 检查是否为 JALR 指令 */
//     else if ((instr & 0x7F) == 0x67) {  /* JALR */
//         int rd = (instr >> 7) & 0x1F;
//         int rs1 = (instr >> 15) & 0x1F;
//         vaddr_t rs1_val = gpr(rs1);
//         int16_t imm = (int16_t)((instr >> 20) & 0x7FF);
//         vaddr_t target = (rs1_val + imm) & ~1;  /* 清除最低位确保对齐 */
        
//         const char *func_name = lookup_symbol(target);
//         const char *mnemonic = get_instr_mnemonic(s);
        
//         /* 如果是函数返回 */
//         if (is_function_return(s)) {
//             if (stack_depth > 0) {
//                 vaddr_t return_addr = call_stack[--stack_depth];
//                 printf("%*sRET  %-15s (0x%08x) -> %-15s (0x%08x)\n", 
//                        stack_depth * 2, "", 
//                        func_name, pc,
//                        lookup_symbol(return_addr), return_addr);
//             } else {
//                 printf("RET  %-15s (0x%08x) -> invalid stack depth\n", 
//                        func_name, pc);
//             }
//         }
//         /* 否则是普通的 JALR 调用 */
//         else {
//             if (stack_depth < MAX_STACK_DEPTH - 1) {
//                 call_stack[stack_depth++] = next_pc;
//             }
//             printf("%*sCALL %-15s (0x%08x) <- %-15s (0x%08x) [rd=%d, rs1=%d]\n", 
//                    stack_depth * 2, "", 
//                    func_name, target,
//                    lookup_symbol(pc), pc, rd, rs1);
//         }
//     }
//     #endif
// }

// /* 清理资源 */
// void ftrace_cleanup() {
//     #ifdef CONFIG_FTRACE
//     if (elf_data) {
//         free(elf_data);
//         elf_data = NULL;
//         Log("Function tracing resources released");
//     }
//     #endif
// }