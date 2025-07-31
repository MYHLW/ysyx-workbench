//#ifdef CONFIG_FTRACE

#include <common.h>
#include <elf.h>

typedef struct ElfFunc {
    uint32_t addr;  // 函数起始地址
    uint32_t size;  // 函数体的大小
    char* name;     // 函数名
} ElfFunc;

ElfFunc* elfuncs = NULL;  // 函数项数组
int elfunc_num = 0;       // 函数项的个数
char* elfunc_strtab = NULL;  // string table

void read_elf(const char* elf_path) {
    // 读取elf文件
    FILE* fp = fopen(elf_path, "rb");
    if (!fp) {
        panic("failed to open elf file %s", elf_path);
    }
    
    fseek(fp, 0, SEEK_END);
    int elf_size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    unsigned char* elf = (unsigned char*)malloc(elf_size);
    if (!elf) {
        panic("failed to allocate memory for elf file %s", elf_path);
    }
    
    if(fread(elf, 1, elf_size, fp) != elf_size) {
        panic("failed to read elf file %s", elf_path);
    }
    fclose(fp);

    // 验证ELF文件魔数
    Elf32_Ehdr* elf_header = (Elf32_Ehdr*)elf;
    if (elf_header->e_ident[EI_MAG0] != ELFMAG0 ||
        elf_header->e_ident[EI_MAG1] != ELFMAG1 ||
        elf_header->e_ident[EI_MAG2] != ELFMAG2 ||
        elf_header->e_ident[EI_MAG3] != ELFMAG3) {
        panic("invalid ELF file %s", elf_path);
    }

    // 解析elf文件
    elfunc_num = 0;
    elfuncs = NULL;
    elfunc_strtab = NULL;

    // 检查节头表偏移是否合理
    if (elf_header->e_shoff + elf_header->e_shnum * sizeof(Elf32_Shdr) > elf_size) {
        panic("invalid section header table in ELF file %s", elf_path);
    }
    
    Elf32_Shdr* elf_shdrs = (Elf32_Shdr*)(elf + elf_header->e_shoff);
    
    // 读取string table
    int strtab_found = 0;
    for (int si = 0; si < elf_header->e_shnum; si++) {
        Elf32_Shdr shdr = elf_shdrs[si];
        if (shdr.sh_type == SHT_STRTAB && si != elf_header->e_shstrndx) {
            // 释放之前分配的内存（如果有）
            if (elfunc_strtab) {
                free(elfunc_strtab);
            }
            
            elfunc_strtab = (char*)malloc(shdr.sh_size);
            if (!elfunc_strtab) {
                panic("failed to allocate memory for string table");
            }
            
            memcpy(elfunc_strtab, elf + shdr.sh_offset, shdr.sh_size);
            strtab_found = 1;
            break;
        }
    }
    
    if (!strtab_found) {
        panic("no suitable string table found in ELF file %s", elf_path);
    }

    // 解析symbol table
    int symtab_found = 0;
    for (int si = 0; si < elf_header->e_shnum; si++) {
        Elf32_Shdr shdr = elf_shdrs[si];
        if (shdr.sh_type == SHT_SYMTAB) {
            // 检查符号表是否有效
            if (shdr.sh_entsize == 0 || shdr.sh_size % shdr.sh_entsize != 0) {
                continue; // 无效的符号表，跳过
            }
            
            Elf32_Sym* symtab = (Elf32_Sym*)(elf + shdr.sh_offset);
            
            // 获取symbol table中函数项的个数
            for (int i = 0; i < shdr.sh_size / shdr.sh_entsize; i++) {
                Elf32_Sym sym = symtab[i];
                if (ELF32_ST_TYPE(sym.st_info) == STT_FUNC) {
                    elfunc_num++;
                }
            }
            
            // 分配内存存储函数信息
            if (elfuncs) {
                free(elfuncs); // 释放之前分配的内存（如果有）
            }
            
            elfuncs = (ElfFunc*)malloc(sizeof(ElfFunc) * elfunc_num);
            if (!elfuncs) {
                panic("failed to allocate memory for function table");
            }
            
            ElfFunc* item = elfuncs;
            for (int i = 0; i < shdr.sh_size / shdr.sh_entsize; i++) {
                Elf32_Sym sym = symtab[i];
                if (ELF32_ST_TYPE(sym.st_info) == STT_FUNC) {
                    item->addr = sym.st_value;
                    item->size = sym.st_size;
                    item->name = elfunc_strtab + sym.st_name;
                    item += 1;
                }
            }
            
            symtab_found = 1;
            break; // 只处理第一个符号表
        }
    }
    
    if (!symtab_found) {
        // 如果没有找到符号表，可以选择不panic，但函数追踪功能将不可用
        Log("warning: no symbol table found in ELF file %s, function tracing disabled", elf_path);
        if (elfuncs) {
            free(elfuncs);
            elfuncs = NULL;
        }
        elfunc_num = 0;
    }
    
    free(elf);
    
    // 添加调试信息
    Log("ELF file %s parsed: %d functions found", elf_path, elfunc_num);
}

int print_ftrace_level = 0;

void print_ftrace(uint32_t inst_addr, uint32_t func_addr, int is_enter) {
    // 检查是否有函数信息
    if (!elfuncs || elfunc_num == 0) {
        printf("0x%08x: %s ???\n", inst_addr, is_enter ? "call" : "ret");
        return;
    }
    
    printf("0x%08x: ", inst_addr);
    if (is_enter != 1) {
        print_ftrace_level--;
    }
    
    // 限制缩进级别，防止过度缩进导致的问题
    if (print_ftrace_level < 0) print_ftrace_level = 0;
    if (print_ftrace_level > 100) print_ftrace_level = 100;
    
    for (int i = 0; i < print_ftrace_level; i++) {
        printf(" ");
    }
    
    if (is_enter == 1) {
        print_ftrace_level++;
        printf("call ");
    }
    else {
        printf("ret ");
    }
    
    for (int i = 0; i < elfunc_num; i++) {
        if (func_addr >= elfuncs[i].addr && func_addr < elfuncs[i].addr + elfuncs[i].size) {
            // 确保name指针有效
            if (!elfuncs[i].name) {
                printf("unknown\n");
            } else {
                printf("%s\n", elfuncs[i].name);
            }
            return; 
        }
    }
    printf("???\n");
}

//#endif