// sdb.h
#ifndef SDB_H
#define SDB_H

#include "Vysyx_25020059_top.h"
#include <verilated.h>
#include <verilated_vcd_c.h>
#include <verilated_dpi.h>


// 声明全局变量（在 sdb.cpp 中定义，main.cpp 中也需要访问）
extern bool sim_done;       // 仿真结束标志
extern int trap_code;       // 陷阱代码
extern Vysyx_25020059_top dut;  // Verilog 模块实例（DUT）
extern VerilatedVcdC* tfp;  // 波形文件指针
extern VerilatedContext* ctx;  // 仿真上下文

// 声明仿真控制函数
void cmd_si(int steps);       // 单步执行
void cmd_continue();          // 继续运行
void cmd_info_reg();          // 查看寄存器
void cmd_help();              // 帮助命令
void sdb_mainloop();          // 命令行主循环

// 声明仿真控制函数
void single_cycle();                  // 单时钟周期
void reset(int n);                    // 复位函数

#endif  // SDB_H