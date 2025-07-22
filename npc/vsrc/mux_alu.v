`include "../vsrc/rvseed_defines.v"

module mux_alu (
    input       [`ALU_SRC_WIDTH-1:0]    alu_src_sel,// 选择信号
    input       [`CPU_WIDTH-1:0]        reg1_rdata, // 寄存器1数据
    input       [`CPU_WIDTH-1:0]        reg2_rdata, // 寄存器2数据
    input       [`CPU_WIDTH-1:0]        imm,   // 立即数数据
    input       [`CPU_WIDTH-1:0]        curr_pc,

    output reg  [`CPU_WIDTH-1:0]        alu_src1,  // ALU输入1
    output reg  [`CPU_WIDTH-1:0]        alu_src2    

);

    always @(*) begin
        alu_src1 = reg1_rdata;     // defalut select reg1 data
        alu_src2 = reg2_rdata;     // default select reg2 data
        case (alu_src_sel)
            `ALU_SRC_REG: begin
                alu_src1 = reg1_rdata; // src1 = reg1
                alu_src2 = reg2_rdata; // src2 = reg2
            end
            `ALU_SRC_IMM: begin
                alu_src1 = reg1_rdata; // src1 = reg1
                alu_src2 = imm;   // src2 = imm
            end
            `ALU_SRC_FOUR_PC: begin
                alu_src1 = `CPU_WIDTH'b4; // src1 = 4
                alu_src2 = curr_pc; // src2 = pc
            end
            `ALU_SRC_IMM_PC: begin
                alu_src1 = imm;   // src1 = imm
                alu_src2 = curr_pc; // src2 = pc
            end
            // 其他情况可以根据需要添加
            default: begin
                alu_src1 = `CPU_WIDTH'b0;
                alu_src2 = `CPU_WIDTH'b0;
            end
        endcase
    end