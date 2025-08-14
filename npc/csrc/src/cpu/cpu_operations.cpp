#include "cpu_operations.h"
#include "Vysyx_25020059_top.h"
#include "trace/itrace.h"
#include <verilated.h>
#include <verilated_vcd_c.h>

// 单周期执行
void single_cycle() {    
    dut.clk = 0;
    dut.eval();
    tfp->dump(ctx->time());
    ctx->timeInc(1);
    
    // 添加指令追踪
    trace_inst(dut.curr_pc, dut.inst);
    get_regs();
    
    dut.clk = 1;
    dut.eval();        
    tfp->dump(ctx->time());
    ctx->timeInc(1);    
    sim_cycle++;
    
    // 检查周期数是否超过阈值
    if (sim_cycle >= MAX_CYCLE) {
        npc_trap(2);  // 用新的trap码（比如2）表示周期超限
        sim_done = true;
    }
}

void reset(int n) {
    while(n > 0) {
        dut.clk = 0;
        dut.rst = 1;
        dut.eval();
        tfp->dump(ctx->time());
        ctx->timeInc(1);

        dut.clk = 1;
        dut.rst = 1;
        dut.eval();
        tfp->dump(ctx->time());
        ctx->timeInc(1);

        dut.rst = 0;
        n--;
    }
}