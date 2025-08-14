#include "cpu_operations.h"
#include "Vysyx_25020059_top.h"
#include "trace/itrace.h"
#include <verilated.h>
#include <verilated_vcd_c.h>
void difftest_step(vaddr_t pc, vaddr_t npc);
// 单周期执行
void single_cycle() {    
    dut.clk = 0;
    dut.eval();
    tfp->dump(ctx->time());
    ctx->timeInc(1);  
    
    // 添加指令追踪
    trace_inst(dut.curr_pc, dut.inst);
    
    dut.clk = 1;
    dut.eval();        
    tfp->dump(ctx->time());
    ctx->timeInc(1);    
    sim_cycle++;
    get_regs();
    difftest_step(dut.curr_pc, dut.next_pc);  // 调用差分测试步进
    // 检查周期数是否超过阈值
    if (sim_cycle >= MAX_CYCLE) {
        npc_trap(2);  // trap2表示周期超限
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

void init_cycle() {    
    get_regs();
    printf("6Current PC: 0x%08X\n", cpu.pc);
    dut.clk = 0;
    dut.eval();
    tfp->dump(ctx->time());
    ctx->timeInc(1);
    trace_inst(dut.curr_pc, dut.inst);
    dut.clk = 1;
    dut.eval();        
    tfp->dump(ctx->time());
    ctx->timeInc(1);    
    sim_cycle++;   
}

