`include "../vsrc/rvseed_defines.v"

module alu(
    input       [`ALU_OP_WIDTH-1:0] alu_op,
    input       [`CPU_WIDTH-1:0]    alu_src1,
    input       [`CPU_WIDTH-1:0]    alu_src2,
    output                          zero,
    output reg  [`CPU_WIDTH-1:0]    alu_res
    //后续加入overflow, carry等信号
);

always @(*) begin
  case (alu_op)
    `ALU_ADD:  alu_res = alu_src1 +  alu_src2;
    `ALU_SUB:  alu_res = alu_src1 -  alu_src2;
    `ALU_AND:  alu_res = alu_src1 &  alu_src2;
    `ALU_OR :  alu_res = alu_src1 |  alu_src2;
    `ALU_XOR:  alu_res = alu_src1 ^  alu_src2;
    `ALU_SLL:  alu_res = alu_src1 << alu_src2[4:0];
    `ALU_SRL:  alu_res = alu_src1 >> alu_src2[4:0];
    `ALU_SRA:  alu_res = $signed(alu_src1) >>> alu_src2[4:0];
    `ALU_SLT:  alu_res = ($signed(alu_src1) < $signed(alu_src2));
    // … 如有更多操作在此添加 …
    default:   alu_res = `CPU_WIDTH'b0;
  endcase

  // zero 标志：只要结果为 0 都置位
  assign zero = (alu_res == `CPU_WIDTH'b0);
end

endmodule
