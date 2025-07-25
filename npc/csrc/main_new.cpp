// csrc/main_new.cpp
#include "cli.h"
#include "Vysyx_25020059_top.h"
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include <verilated_dpi.h>

// ----- 全局变量定义 -----
VerilatedContext* ctx       = nullptr;
VerilatedVcdC*    tfp       = nullptr;
bool              sim_done  = false;
int               trap_code = -1;
uint64_t          sim_cycle = 0;
Vysyx_25020059_top dut;
uint8_t*          memory    = nullptr;

#define MEM_BASE    0x80000000U
#define MEM_SIZE    (8 * 1024 * 1024)  // 8MB

// 虚拟地址转宿主地址
static inline uint32_t guest_to_host(uint32_t addr) {
    return addr - MEM_BASE;
}

// 从仿真内存读取指令
uint32_t pmem_read(uint32_t* /*unused*/, uint32_t vaddr) {
    uint32_t off = guest_to_host(vaddr);
    return *(uint32_t*)(memory + off);
}

// 加载程序镜像
void load_image(const char* filename) {
    FILE* fp = std::fopen(filename, "rb");
    if (!fp) {
        std::perror("fopen");
        std::exit(EXIT_FAILURE);
    }
    size_t sz = std::fread(memory, 1, MEM_SIZE, fp);
    std::fclose(fp);
    std::printf("Loaded binary '%s' (%zu bytes) at 0x%08X\n",
                filename, sz, MEM_BASE);
}

// 单周期执行
void single_cycle() {
    dut.clk = 0;
    dut.eval();
    tfp->dump(ctx->time());
    ctx->timeInc(1);

    dut.clk = 1;
    dut.eval();
    dut.inst = pmem_read(nullptr, dut.curr_pc);
    tfp->dump(ctx->time());
    ctx->timeInc(1);

    sim_cycle++;
}

// 复位 n 周期
void reset(int n) {
    dut.rst = 1;
    while (n-- > 0) single_cycle();
    dut.rst = 0;
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::fprintf(stderr, "Usage: %s <program.bin>\n", argv[0]);
        return -1;
    }

    // 分配并清零内存
    memory = (uint8_t*)std::malloc(MEM_SIZE);
    if (!memory) { std::perror("malloc"); return -1; }
    std::memset(memory, 0, MEM_SIZE);

    load_image(argv[1]);

    // 打开波形跟踪
    Verilated::traceEverOn(true);
    ctx = new VerilatedContext;
    tfp = new VerilatedVcdC;
    dut.trace(tfp, 5);
    tfp->open("Vysyx_25020059.vcd");

    // 复位
    reset(2);

    // 启动命令行调试
    sdb_mainloop();

    // 结束后输出 Trap 状态
    std::printf("\n");
    if (trap_code == 0) {
        std::printf("\033[32m[NPC] HIT GOOD TRAP: program exited successfully.\033[0m\n");
    } else {
        std::printf("\033[31m[NPC] HIT BAD TRAP: program failed (code=%d).\033[0m\n", trap_code);
    }

    // 清理
    tfp->close();
    delete tfp;
    delete ctx;
    std::free(memory);
    return 0;
}
