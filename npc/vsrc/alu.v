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
    zero = 1'b0;
    alu_res = `CPU_WIDTH'b0;
    case (alu_op)
        `ALU_ADD: 
            alu_res = alu_src1 +  alu_src2;
        `ALU_SUB:begin 
            alu_res = alu_src1 -  alu_src2;
            zero = (alu_res == `CPU_WIDTH'b0) ? 1'b1 : 1'b0;
        end
    endcase
end
endmodule
