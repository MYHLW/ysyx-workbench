#include "cli.h"
#include "loader.h"  // 引入封装的加载接口
#include "memory.h"  // 引入内存相关接口
#include "cpu_operations.h"
#include "dpi/dpi_functions.h" // 引入DPI函数声明
#include "cpu_state.h"  // 引入CPU状态定义
#include "Vysyx_25020059_top.h"
#include "trace/itrace.h"  // 添加itrace支持
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <sys/time.h>
#include <string>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include <verilated_dpi.h>


// ----- 全局变量-----
const uint32_t MEM_BASE = 0x80000000U;
const uint32_t MEM_SIZE = 128 * 1024 * 1024;  // 128MB
uint8_t memory[MEM_SIZE];  // 全局内存数组（供loader和cli访问）

VerilatedContext* ctx       = nullptr;
VerilatedVcdC*    tfp       = nullptr;
bool              sim_done  = false;
int               trap_code = -1;
uint64_t          sim_cycle = 0;
Vysyx_25020059_top dut;
CPU_state cpu;

void get_regs(); // 获取寄存器状态
long load_img(char *img_file); // 获取程序大小
void init_difftest(char *ref_so_file, long img_size, int port);
void init_disasm(); // 初始化反汇编



int main(int argc, char** argv) {
    if (argc < 2) {
        std::fprintf(stderr, "Usage: %s <program.hex|program.bin>\n", argv[0]);
        return -1;
    }

    // 初始化内存并加载程序（使用封装的接口）
    std::memset(memory, 0, MEM_SIZE);
    load_program(argv[1]);  // 调用loader.h中的函数

    // 波形跟踪初始化
    Verilated::traceEverOn(true);
    ctx = new VerilatedContext;
    tfp = new VerilatedVcdC;
    dut.trace(tfp, 5);
    tfp->open("Vysyx_25020059.vcd");

    // 复位CPU
    reset(2);
    //single_cycle();
    init_cycle();  

    init_disasm();  // 初始化反汇编
    
    //diff
    //cpu.pc = dut.curr_pc;  // 设置初始PC
    long img_size = load_img(argv[1]);
    const char *diff_so_file = "/home/wang/ysyx-workbench/nemu/build/libriscv32-nemu-interpreter-so.so";
    init_difftest((char *)diff_so_file, img_size, 1234);

    // 启动命令行调试
    sdb_mainloop();
    
    // 清理资源
    tfp->close();
    delete tfp;
    delete ctx;
    return 0;
}