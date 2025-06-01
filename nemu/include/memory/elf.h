#ifndef __ELF_H__
#define __ELF_H__

#include <stdint.h>

/* ELF 文件头 */
typedef struct {
    unsigned char e_ident[16];  /* 标识信息 */
    uint16_t      e_type;       /* 文件类型 */
    uint16_t      e_machine;    /* 目标架构 */
    uint32_t      e_version;    /* 版本 */
    uint32_t      e_entry;      /* 入口点地址 */
    uint32_t      e_phoff;      /* 程序头表偏移 */
    uint32_t      e_shoff;      /* 节头表偏移 */
    uint32_t      e_flags;      /* 标志 */
    uint16_t      e_ehsize;     /* ELF 头大小 */
    uint16_t      e_phentsize;  /* 程序头表项大小 */
    uint16_t      e_phnum;      /* 程序头表项数量 */
    uint16_t      e_shentsize;  /* 节头表项大小 */
    uint16_t      e_shnum;      /* 节头表项数量 */
    uint16_t      e_shstrndx;   /* 节名字符串表索引 */
} Elf32_Ehdr;

/* ELF 节头 */
typedef struct {
    uint32_t sh_name;      /* 节名，索引到字符串表 */
    uint32_t sh_type;      /* 节类型 */
    uint32_t sh_flags;     /* 节标志 */
    uint32_t sh_addr;      /* 节的内存地址 */
    uint32_t sh_offset;    /* 节在文件中的偏移 */
    uint32_t sh_size;      /* 节的大小 */
    uint32_t sh_link;      /* 关联节的索引 */
    uint32_t sh_info;      /* 额外信息 */
    uint32_t sh_addralign; /* 地址对齐 */
    uint32_t sh_entsize;   /* 表项大小（如果有） */
} Elf32_Shdr;

/* ELF 符号表项 */
typedef struct {
    uint32_t st_name;    /* 符号名，索引到字符串表 */
    uint32_t st_value;   /* 符号值（地址） */
    uint32_t st_size;    /* 符号大小 */
    unsigned char st_info;  /* 符号类型和绑定 */
    unsigned char st_other; /* 其他信息 */
    uint16_t st_shndx;   /* 节索引 */
} Elf32_Sym;

/* 符号类型宏 */
#define ELF32_ST_BIND(info)  ((info) >> 4)
#define ELF32_ST_TYPE(info)  ((info) & 0x0F)
#define ELF32_ST_INFO(bind, type)  (((bind) << 4) + ((type) & 0x0F))

/* 符号绑定类型 */
#define STB_LOCAL  0    /* 局部符号 */
#define STB_GLOBAL 1    /* 全局符号 */
#define STB_WEAK   2    /* 弱符号 */

/* 符号类型 */
#define STT_NOTYPE  0    /* 无类型 */
#define STT_OBJECT  1    /* 数据对象（变量） */
#define STT_FUNC    2    /* 函数 */
#define STT_SECTION 3    /* 节 */
#define STT_FILE    4    /* 文件 */

/* ELF 头标识常量 */
#define EI_MAG0       0    /* e_ident[] 索引 */
#define EI_MAG1       1
#define EI_MAG2       2
#define EI_MAG3       3
#define EI_CLASS      4    /* 位数：32 或 64 */
#define EI_DATA       5    /* 字节序 */
#define EI_VERSION    6    /* 版本 */
#define EI_OSABI      7    /* OS/ABI 标识 */
#define EI_ABIVERSION 8    /* ABI 版本 */
#define EI_PAD        9    /* 填充字节开始 */
#define EI_NIDENT     16   /* e_ident[] 大小 */

/* e_ident[] 魔数 */
#define ELFMAG0       0x7F /* 魔数第1字节 */
#define ELFMAG1       'E'  /* 魔数第2字节 */
#define ELFMAG2       'L'  /* 魔数第3字节 */
#define ELFMAG3       'F'  /* 魔数第4字节 */
#define ELFMAG        "\177ELF"
#define SELFMAG       4    /* 魔数长度 */

/* e_type 值 */
#define ET_NONE       0    /* 无类型 */
#define ET_REL        1    /* 可重定位文件 */
#define ET_EXEC       2    /* 可执行文件 */
#define ET_DYN        3    /* 共享对象文件 */
#define ET_CORE       4    /* 核心转储文件 */

/* e_machine 值（部分） */
#define EM_NONE       0    /* 无架构 */
#define EM_M32        1    /* AT&T WE 32100 */
#define EM_SPARC      2    /* SPARC */
#define EM_386        3    /* Intel 80386 */
#define EM_68K        4    /* Motorola 68000 */
#define EM_88K        5    /* Motorola 88000 */
#define EM_860        7    /* Intel 80860 */
#define EM_MIPS       8    /* MIPS R3000 */
#define EM_RISCV      243  /* RISC-V */

#endif /* __ELF_H__ */