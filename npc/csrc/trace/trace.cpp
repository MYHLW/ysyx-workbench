#include "trace.h"
#include "capstone.h"

// 全局变量定义
InstTrace iringbuf[IRINGBUF_SIZE];
int iringbuf_index = 0;
bool enable_itrace = true;
bool enable_mtrace = true;
bool enable_ftrace = true;

// 用于反汇编的capstone句柄
static csh handle;

void init_trace() {
    // 初始化capstone
    if (cs_open(CS_ARCH_RISCV, CS_MODE_RISCV32, &handle) != CS_ERR_OK) {
        printf("ERROR: Failed to initialize capstone!\n");
        exit(1);
    }
    cs_option(handle, CS_OPT_DETAIL, CS_OPT_ON);
}

void trace_instruction(uint64_t pc, uint32_t inst) {
    if (!enable_itrace) return;

    // 使用capstone进行反汇编
    cs_insn *insn;
    size_t count = cs_disasm(handle, (uint8_t*)&inst, 4, pc, 1, &insn);
    
    // 保存到环形缓冲区
    iringbuf[iringbuf_index].pc = pc;
    iringbuf[iringbuf_index].inst = inst;
    if (count > 0) {
        snprintf(iringbuf[iringbuf_index].disasm, sizeof(iringbuf[iringbuf_index].disasm),
                "%s %s", insn[0].mnemonic, insn[0].op_str);
        cs_free(insn, count);
    } else {
        snprintf(iringbuf[iringbuf_index].disasm, sizeof(iringbuf[iringbuf_index].disasm),
                "<invalid>");
    }

    // 更新环形缓冲区索引
    iringbuf_index = (iringbuf_index + 1) % IRINGBUF_SIZE;
}

void trace_memory(bool is_write, uint64_t addr, uint64_t data, uint8_t len) {
    if (!enable_mtrace) return;
    
    printf("[mtrace] %s 0x%lx: 0x%lx (len=%d)\n",
           is_write ? "write" : "read", addr, data, len);
}

void trace_function(uint64_t pc, bool is_call, const char* func_name) {
    if (!enable_ftrace) return;
    
    static int call_depth = 0;
    if (is_call) {
        printf("[ftrace] %*s-> %s\n", call_depth * 2, "", func_name);
        call_depth++;
    } else {
        call_depth--;
        printf("[ftrace] %*s<- %s\n", call_depth * 2, "", func_name);
    }
}

void print_iringbuf() {
    printf("\n=== Instruction Ring Buffer ===\n");
    for (int i = 0; i < IRINGBUF_SIZE; i++) {
        int idx = (iringbuf_index - 1 - i + IRINGBUF_SIZE) % IRINGBUF_SIZE;
        if (iringbuf[idx].pc != 0) {
            printf("%s0x%08lx: %08x  %s\n",
                   i == 0 ? "--> " : "    ",
                   iringbuf[idx].pc,
                   iringbuf[idx].inst,
                   iringbuf[idx].disasm);
        }
    }
    printf("===========================\n");
}