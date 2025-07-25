#include "Vysyx_25020059_top.h"
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <verilated.h>
#include <verilated_vcd_c.h>
#include <verilated_dpi.h>

// 仿真内存基址和大小定义
#define MEM_BASE       0x80000000U
#define MEM_SIZE       (8 * 1024 * 1024) // 8MB

static Vysyx_25020059_top dut;
static uint8_t *memory;

// // 在现有头文件后添加
// #include <readline/readline.h>   // 用于命令行输入
// #include <readline/history.h>    // 记录命令历史
// #include <map>                   // 存储命令映射

// // 全局变量：控制仿真状态
// static bool is_running = false;  // 是否处于连续运行状态
 static uint64_t sim_cycle = 0;   // 记录总仿真周期数

// // 声明后续需要的函数
// void cmd_si(int steps);          // 单步执行函数
// void cmd_continue();             // 继续运行函数
// void cmd_info_reg();             // 查看寄存器信息
// void cmd_help();                 // 帮助命令

// // 命令处理函数类型
// typedef void (*cmd_func_t)(const char* args);

// // 命令映射（命令名 -> 处理函数）
// std::map<std::string, cmd_func_t> cmd_table = {
//     {"si",    [](const char* args) { 
//         int steps = args ? atoi(args) : 1;  // 支持 si 10 执行10步
//         cmd_si(steps); 
//     }},
//     {"c",     [](const char* args) { cmd_continue(); }},  // 继续运行
//     {"info r",[](const char* args) { cmd_info_reg(); }},  // 查看寄存器
//     {"help",  [](const char* args) { cmd_help(); }},      // 帮助
//     {"q",     [](const char* args) { sim_done = true; }},  // 退出
// };

// 将虚拟地址转换为内存数组偏移
static inline uint32_t guest_to_host(uint32_t addr) {
    return addr - MEM_BASE;
}

// 从仿真内存读取一条指令
uint32_t pmem_read(uint32_t * /*unused*/, uint32_t vaddr) {
    uint32_t off = guest_to_host(vaddr);
    return *(uint32_t *)(memory + off);
}

// 从文件加载二进制镜像到仿真内存
void load_image(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    // 读入数据
    size_t sz = fread(memory, 1, MEM_SIZE, fp);
    fclose(fp);
    printf("Loaded binary '%s' (%zu bytes) at 0x%08X\n", filename, sz, MEM_BASE);
}

// 一个时钟周期
// 改写原 single_cycle，增加周期计数和状态更新
void single_cycle(VerilatedVcdC *tfp, VerilatedContext *ctx) {
    dut.clk = 0; 
    dut.eval();
    tfp->dump(ctx->time());  // 记录波形
    ctx->timeInc(1);

    dut.clk = 1; 
    dut.eval();
    tfp->dump(ctx->time());  // 记录波形
    ctx->timeInc(1);

    sim_cycle++;  // 周期计数+1
}

// 复位 n 个周期
static void reset(int n, VerilatedVcdC *tfp, VerilatedContext *ctx) {
    dut.rst = 1; 
    while (n-- > 0) single_cycle(tfp, ctx);
    dut.rst = 0; 
}

// ============ DPI‑C: ebreak 触发退出 ==============
// 在 main.cpp（全局作用域）
static bool sim_done = false;
static int  trap_code = -1;

// DPI 回调
extern "C" void npc_trap(int code) {
  if (!sim_done) {
    sim_done   = true;
    trap_code  = code;
  }
}

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <program.bin>\n", argv[0]);
        return -1;
    }
    // 分配仿真内存
    memory = (uint8_t *)malloc(MEM_SIZE);
    if (!memory) {
        perror("malloc");
        return -1;
    }
    memset(memory, 0, MEM_SIZE);

    // 加载用户程序
    load_image(argv[1]);

    // Verilator 波形追踪设置
    Verilated::traceEverOn(true);
    VerilatedContext *ctx = new VerilatedContext;
    VerilatedVcdC *tfp = new VerilatedVcdC;
    dut.trace(tfp, 5);
    tfp->open("Vysyx_25020059.vcd");

    reset(2, tfp, ctx);


    // 仿真主循环，直到 ebreak 调用 npc_trap 退出进程
    while (!Verilated::gotFinish() && !sim_done) {
        // 单周期推进
        single_cycle(tfp, ctx);

        // 同步打印 PC 和指令
        printf("PC=0x%08X inst=0x%08X \n", (uint32_t)dut.curr_pc, dut.inst); // 假设 reg_f[1] 是要打印的寄存器
        //printf("reg=0x%08X \n",(uint32_t)dut.reg_f[1])

    }
    
    // 循环结束后，再打印 GOOD/BAD TRAP
    printf("\n");
    if (trap_code == 0) {
        printf("\033[32m[NPC] HIT GOOD TRAP: program exited successfully.\033[0m\n");
    } else {
        printf("\033[31m[NPC] HIT BAD TRAP: program failed (code=%d).\033[0m\n",trap_code);
    }
    printf("\n");
    // 清理（理论上不可达）
    tfp->close();
    delete tfp;
    delete ctx;
    free(memory);
    return 0;
}


//============= 2. 命令行交互 ==============
