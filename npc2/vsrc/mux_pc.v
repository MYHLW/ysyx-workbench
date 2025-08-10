`include "/home/wang/ysyx-workbench/npc/vsrc/rvseed_defines.v"
// 在 rvseed_defines.v 里，你可以加一行：
// `define PC_INC (`CPU_WIDTH)'(32'd4)

module muxpc #(
  parameter PC_INC = `CPU_WIDTH'h4
)(
    input                        ena,         // 使能，复位后才开始更新 PC
    input                        beq_branch,  // BEQ 分支指令是否有效
    input                        bne_branch,  // BNE 分支指令是否有效
    input                        blt_branch,  // BLT 分支指令是否有效
    input                        bltu_branch, // BLTU 分支指令是否有效
    input                        bge_branch,  // BGE 分支指令是否有效
    input                        bgeu_branch, // BGEU 分支指令是否有效
    input  [`CPU_WIDTH-1:0]      reg1_rdata,  // 寄存器1数据(忘记位宽这事了)
    input                        zero,        // ALU zero 标志
    input                        jal_jump,        // JAL
    input                        jalr_jump,        // JALR
    input  [`CPU_WIDTH-1:0]      imm,         // 已签扩的立即数
    input  [`CPU_WIDTH-1:0]      curr_pc,     // 当前 PC
    output reg [`CPU_WIDTH-1:0]  next_pc      // 下一个 PC
);

always @(*) begin
  if (!ena) begin
    // 尚未解锁时保持 PC 不变
    next_pc = curr_pc;
  end else if (jal_jump) begin
    // 无条件跳转JAL
    next_pc = curr_pc + imm;
  end else if (jalr_jump) begin
    // 无条件跳转JALR
    next_pc = (reg1_rdata + imm) & ~32'h1; //
  end else if (beq_branch && zero) begin
    // BEQ 条件成立
    next_pc = curr_pc + imm;
  end else if (bne_branch && ~zero) begin
    // BNE 条件成立
    next_pc = curr_pc + imm;
  end else if (blt_branch && ~zero) begin
    // BLT 条件成立
    next_pc = curr_pc + imm;
  end else if (bltu_branch && ~zero) begin
    // BLTU 条件成立
    next_pc = curr_pc + imm;
  end else if (bge_branch && zero) begin // BGE 条件成立
    // BGE 条件成立
    next_pc = curr_pc + imm;
  end else if (bgeu_branch && zero) begin
    // BGEU 条件成立
    next_pc = curr_pc + imm;
  end else begin
    // 默认顺序执行
    next_pc = curr_pc + PC_INC;
  end
end

endmodule
