`include "../vsrc/rvseed_defines.v"

// 在 rvseed_defines.v 里，你可以加一行：
// `define PC_INC (`CPU_WIDTH)'(32'd4)

module muxpc #(
  parameter PC_INC = `CPU_WIDTH'h4
)(
    input                        ena,         // 使能，复位后才开始更新 PC
    input                        branch_eq,   // BEQ 有效
    input                        branch_ne,   // BNE 有效
    input                        zero,        // ALU zero 标志
    input                        jump,        // JAL/JALR 有效
    input  [`CPU_WIDTH-1:0]      imm,         // 已签扩的立即数
    input  [`CPU_WIDTH-1:0]      curr_pc,     // 当前 PC
    output reg [`CPU_WIDTH-1:0]  next_pc      // 下一个 PC
);

always @(*) begin
  if (!ena) begin
    // 尚未解锁时保持 PC 不变
    next_pc = curr_pc;
  end else if (jump) begin
    // 无条件跳转（JAL/JALR）
    next_pc = curr_pc + imm;
  end else if (branch_eq && zero) begin
    // BEQ 条件成立
    next_pc = curr_pc + imm;
  end else if (branch_ne && ~zero) begin
    // BNE 条件成立
    next_pc = curr_pc + imm;
  end else begin
    // 默认顺序执行
    next_pc = curr_pc + PC_INC;
  end
end

endmodule
