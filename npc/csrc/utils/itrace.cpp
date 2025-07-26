// csrc/utils/itrace.cpp
#include "itrace.h"
#include "disasm.h"
#include <cstring>
#include <cstdio>

// Forward declaration for disassembler initialization
void init_disasm();

// Forward declaration for disassemble function
void disassemble(char *str, size_t size, uint64_t pc, const uint8_t *code, int nbyte);

// 环形缓冲区配置
constexpr size_t IRINGBUF_SIZE = 16;

// 指令条目结构
struct IringEntry {
    uint64_t pc;
    uint32_t inst;
    char disasm[64];
};

// 模块内部状态
static IringEntry iringbuf[IRINGBUF_SIZE];
static size_t iringbuf_idx = 0;
static bool enabled = true;  // 默认启用
static bool initialized = false;

// 初始化 itrace 系统
void init_itrace() {
    if (!initialized) {
        init_disasm();  // 初始化反汇编器
        initialized = true;
    }
    
    // 清空环形缓冲区
    iringbuf_idx = 0;
    for (auto& entry : iringbuf) {
        entry.pc = 0;
        entry.inst = 0;
        entry.disasm[0] = '\0';
    }
}

// 记录一条指令到环形缓冲区
void itrace_record(uint64_t pc, uint32_t inst) {
    if (!enabled || !initialized) return;
    
    // 反汇编指令
    char disasm_buf[128];
    disassemble(disasm_buf, sizeof(disasm_buf), pc, (uint8_t*)&inst, 4);
    
    // 保存到环形缓冲区
    size_t idx = iringbuf_idx % IRINGBUF_SIZE;
    iringbuf[idx].pc = pc;
    iringbuf[idx].inst = inst;
    strncpy(iringbuf[idx].disasm, disasm_buf, sizeof(iringbuf[idx].disasm)-1);
    iringbuf[idx].disasm[sizeof(iringbuf[idx].disasm)-1] = '\0';
    
    iringbuf_idx++;
}

// 打印环形缓冲区中的指令历史
void itrace_print_history() {
    if (!initialized || iringbuf_idx == 0) {
        printf("No instruction history recorded\n");
        return;
    }
    
    size_t start_idx = 0;
    size_t count = (iringbuf_idx < IRINGBUF_SIZE) ? iringbuf_idx : IRINGBUF_SIZE;
    
    if (iringbuf_idx > IRINGBUF_SIZE) {
        start_idx = iringbuf_idx % IRINGBUF_SIZE;
    }
    
    printf("\n===== Last %zu instructions before trap =====\n", count);
    for (size_t i = 0; i < count; i++) {
        size_t idx = (start_idx + i) % IRINGBUF_SIZE;
        printf("%c 0x%08lX: %-20s // 0x%08X\n",
               (i == count - 1) ? '>' : ' ',
               iringbuf[idx].pc,
               iringbuf[idx].disasm,
               iringbuf[idx].inst);
    }
    printf("===========================================\n");
}

// 设置是否启用指令记录
void itrace_set_enabled(bool enable) {
    enabled = enable;
    if (enabled && !initialized) {
        init_itrace();
    }
}

// 检查是否启用了指令记录
bool itrace_is_enabled() {
    return enabled;
}