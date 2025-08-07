`include "/home/wang/ysyx-workbench/npc/vsrc/rvseed_defines.v"

module alu(
    input       [`ALU_OP_WIDTH-1:0] alu_op,
    input       [`CPU_WIDTH-1:0]    alu_src1,
    input       [`CPU_WIDTH-1:0]    alu_src2,
    output reg                      zero,
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
        `ALU_SLTU:
            alu_res = (alu_src1 < alu_src2) ? `CPU_WIDTH'd1 : `CPU_WIDTH'd0;
        `ALU_BLT: begin
            alu_res = ($signed(alu_src1) < $signed(alu_src2)) ? `CPU_WIDTH'd1 : `CPU_WIDTH'd0;
            zero = ~alu_res[0];
        end
        `ALU_BLTU: begin
            alu_res = (alu_src1 < alu_src2) ? `CPU_WIDTH'd1 : `CPU_WIDTH'd0;
            zero = ~alu_res[0];
        end
        `ALU_SLT:
            alu_res = ($signed(alu_src1) < $signed(alu_src2)) ? `CPU_WIDTH'd1 : `CPU_WIDTH'd0;
        `ALU_AND:
            alu_res = alu_src1 & alu_src2;
        `ALU_OR:
            alu_res = alu_src1 | alu_src2;
        `ALU_XOR:
            alu_res = alu_src1 ^ alu_src2;
        `ALU_SLL:
            alu_res = alu_src1 << alu_src2;
        `ALU_SRL:
            alu_res = alu_src1 >> alu_src2;
        `ALU_SRA:
            alu_res = $signed(alu_src1) >>> alu_src2;
        
    endcase
end
endmodule
