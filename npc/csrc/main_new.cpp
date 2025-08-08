// main_new.cpp (modified)
// 你原来的头文件和实现为基础，加入了 difftest 初始化/清理的调用点

#include "cli.h"
#include "loader.h"  // 引入封装的加载接口（loader.cpp 已被修改以导出 program_size）
#include "Vysyx_25020059_top.h"
#include "itrace.h"  // 添加 itrace 支持
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <sys/time.h>
#include <string>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include <verilated_dpi.h>

// difftest 函数在 difftest.cpp 中实现，这里声明外部接口以便调用
extern bool init_difftest_for_npc(const char* so_path, uint32_t init_pc);
extern bool difftest_step_and_check(uint32_t dut_pc);
extern void fini_difftest();

#define MEM_FAULT_CODE   0xdeadbeef  // 定义内存故障码
#define MEM_ACCESS_FAULT 1           // 定义内存访问错误trap码
#define MAX_CYCLE 10000000  // 最大允许周期数，超过则触发trap

// ----- 全局变量（供外部引用：loader.cpp和cli.cpp）-----
// 注意：这些变量与之前你给出的 main_new.cpp 保持一致
const uint32_t MEM_BASE = 0x80000000U;
const uint32_t MEM_SIZE = 128 * 1024 * 1024;  // 128MB
uint8_t memory[MEM_SIZE];  // 全局内存数组（供loader和cli访问）

VerilatedContext* ctx       = nullptr;
VerilatedVcdC*    tfp       = nullptr;
bool              sim_done  = false;
int               trap_code = -1;
uint64_t          sim_cycle = 0;
Vysyx_25020059_top dut;

// 单周期执行
void single_cycle() {
    dut.clk = 0;
    dut.eval();
    if (tfp) tfp->dump(ctx->time());
    ctx->timeInc(1);

    // 添加指令追踪
    trace_inst(dut.curr_pc, dut.inst);

    dut.clk = 1;
    dut.eval();
    if (tfp) tfp->dump(ctx->time());
    ctx->timeInc(1);
    sim_cycle++;

    // 检查周期数是否超过阈值
    if (sim_cycle >= MAX_CYCLE) {
        npc_trap(2);  // 用新的trap码（比如2）表示周期超限
        sim_done = true;
    }
}

// 复位用：不做 pmem_read
void reset_cycle() {
    dut.clk = 1;
    dut.eval();
    if (tfp) tfp->dump(ctx->time());
    ctx->timeInc(1);

    dut.clk = 0;
    dut.eval();
    if (tfp) tfp->dump(ctx->time());
}

// 复位 n 个周期（带 rst）
void reset(int n) {
    while(n > 0) {
        dut.clk = 0;

        if (tfp) tfp->dump(ctx->time());
        ctx->timeInc(1);

        dut.clk = 1;
        dut.rst = 1;
        dut.eval();
        if (tfp) tfp->dump(ctx->time());
        ctx->timeInc(1);

        dut.rst = 0;
        n--;
    }
}

int main(int argc, char** argv) {
    if (argc < 2) {
        std::fprintf(stderr, "Usage: %s <program.hex|program.bin>\n", argv[0]);
        return -1;
    }

    // 初始化内存并加载程序（使用封装的接口）
    std::memset(memory, 0, MEM_SIZE);
    load_program(argv[1]);  // 调用 loader.cpp 中的函数（会设置 program_size）

    // 波形跟踪初始化
    Verilated::traceEverOn(true);
    ctx = new VerilatedContext;
    tfp = new VerilatedVcdC;
    dut.trace(tfp, 5);
    tfp->open("Vysyx_25020059.vcd");

    // 复位 CPU
    reset(2);

    // ----- 初始化 DiffTest（可通过环境变量 NEMU_SO 指定 so 路径） -----
    const char *so_path = std::getenv("NEMU_SO");
    if (!so_path) {
        so_path = "/home/wang/ysyx-workbench/nemu/build/riscv32-nemu-interpreter-so";
    }

    // 使用 DUT 当前 PC 作为 init_pc（更理想的是从 dut 中读出真正的入口 PC）
    uint32_t dut_init_pc = dut.curr_pc;
    if (!init_difftest_for_npc(so_path, dut_init_pc)) {
        std::fprintf(stderr, "[DIFTEST] init failed, running without difftest.\n");
    } else {
        std::fprintf(stdout, "[DIFTEST] enabled (so=%s)\n", so_path);
    }

    // 启动命令行调试（sdb）
    sdb_mainloop();

    // 清理资源
    fini_difftest(); // 关闭并释放 nemu so
    if (tfp) {
      tfp->close();
      delete tfp;
      tfp = nullptr;
    }
    if (ctx) {
      delete ctx;
      ctx = nullptr;
    }
    return 0;
}

// ===================DPI 端口===========================
extern "C" void npc_trap(int code) {
    if (!sim_done) {
        sim_done = true;
        trap_code = code;
        // 在 trap 时打印指令环形缓冲区
        display_inst();
    }
    printf("NPC_TRAP: code=%d\n", code);
    printf("%ld cycles executed.\n", sim_cycle);
    std::printf("\n");
    if (trap_code == 0) {
        std::printf("\033[32m[NPC] HIT GOOD TRAP: program exited successfully.\033[0m\n");
    } else {
        std::printf("\033[31m[NPC] HIT BAD TRAP: program failed (code=%d).\033[0m\n", trap_code);
    }
}

// 定义设备地址
#define SERIAL_PORT 0xa00003f8  // 串口地址，与 NEMU 保持一致
#define RTC_PORT    0xa0000048  // 时钟地址，与 NEMU 保持一致
#define VGACTL_PORT 0xa0000100  // VGA 控制器地址，与 NEMU 保持一致
#define FB_ADDR     0xa1000000  // 帧缓冲区地址，与 NEMU 保持一致
#define KBD_ADDR    0xa0000060  // 键盘地址，与 NEMU 保持一致

// 获取当前时间（微秒）
uint64_t get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (uint64_t)tv.tv_sec * 1000000 + tv.tv_usec;
}

extern "C" uint32_t pmem_read(uint32_t vaddr, int i) {
    uint32_t value = 0;

    // 处理 MMIO 读取
    if (vaddr == RTC_PORT) {
        value = (uint32_t)get_time();
    }
    else if (vaddr == RTC_PORT + 4) {
        value = (uint32_t)(get_time() >> 32);
    }
    // 处理普通内存读取
    else if (vaddr >= MEM_BASE && vaddr < MEM_BASE + MEM_SIZE) {
        uint32_t off = vaddr - MEM_BASE;
        memcpy(&value, memory + off, sizeof(value));
    }
    else if (vaddr == SERIAL_PORT) {
        value = 0;  // 串口读取，返回0表示可以写入
    }
    else if (vaddr == VGACTL_PORT) {
        // 返回VGA控制寄存器的值（屏幕大小）
        return (300 << 16) | 400;
    }
    else if (vaddr == VGACTL_PORT + 4) {
        // 返回同步状态，始终为1表示就绪
        return 1;
    }
    else if (vaddr >= FB_ADDR && vaddr < FB_ADDR + 400 * 300 * 4) {
        // 从帧缓冲区读取像素数据
        uint32_t fb_offset = vaddr - FB_ADDR;
        uint32_t val;
        memcpy(&val, memory + MEM_SIZE - (400 * 300 * 4) + fb_offset, sizeof(val));
        return val;
    }
    else {
        printf("pmem_read: address out of bounds: 0x%08X\n", vaddr);
        npc_trap(MEM_ACCESS_FAULT);
        return MEM_FAULT_CODE;
    }

    return value;
}

extern "C" void pmem_write(uint32_t addr, uint32_t data, uint8_t wmask) {
    // 处理 MMIO 写入
    if (addr == SERIAL_PORT) {
        putchar(data & 0xff);
        fflush(stdout);
    }
    // 处理VGA控制器写入
    else if (addr == VGACTL_PORT) {
        static uint32_t vgactl = 0;
        vgactl = data;
    }
    else if (addr == VGACTL_PORT + 4) {
        // VGA同步信号
    }
    // 处理帧缓冲区写入
    else if (addr >= FB_ADDR && addr < FB_ADDR + 400 * 300 * 4) {
        uint32_t fb_offset = addr - FB_ADDR;
        uint8_t *fb_ptr = (uint8_t *)&data;
        for (int i = 0; i < 4; i++) {
            if (wmask & (1 << i)) {
                memory[MEM_SIZE - (400 * 300 * 4) + fb_offset + i] = fb_ptr[i];
            }
        }
    }
    // 处理普通内存写入
    else if (addr >= MEM_BASE && addr < MEM_BASE + MEM_SIZE) {
        uint32_t off_byte = addr - MEM_BASE;
        uint32_t off_word = off_byte & ~0x3u;
        uint8_t *p = memory + off_word;
        for (int i = 0; i < 4; i++) {
            if (wmask & (1u << i)) {
                p[i] = uint8_t((data >> (i * 8)) & 0xFF);
            }
        }
    }
    else {
        printf("pmem_write: address out of bounds: 0x%08X\n", addr);
        npc_trap(MEM_ACCESS_FAULT);
    }
}

/* 
 * 调用 difftest_step_and_check 的位置提示：
 *
 * 你应该在 sdb 的 'si' 命令完成 **一条指令**（即 DUT 的单条指令执行完毕并提交）之后
 * 调用 difftest_step_and_check(dut.curr_pc);
 * 
 * 例如（伪代码）：
 *
 *   // sdb 命令处理：用户输入 "si 1"
 *   execute_one_insn_on_dut();   // 你的现有逻辑：推动时钟直到一条指令完成
 *   if (!difftest_step_and_check(dut.curr_pc)) {
 *       // diff 不一致：你可以打印信息并进入交互式调试
 *       fprintf(stderr, "DiffTest mismatch at PC 0x%08x\n", dut.curr_pc);
 *       // 例如把 sim_done 置为 true 或者进入 sdb 交互
 *   }
 *
 * 不要把 difftest_step_and_check 放在 single_cycle() 里（因为 single_cycle() 是一个时钟周期，不等同于一条指令）。
 */

