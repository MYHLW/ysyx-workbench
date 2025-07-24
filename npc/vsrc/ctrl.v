`include "../vsrc/rvseed_defines.v"

// === 1. DPI‑C 函数导入 ===
import "DPI-C" function void npc_trap(input int code);

module ctrl (
    input      [`CPU_WIDTH-1:0]        inst,       // instruction input

    output reg                         branch,     // branch flag
    output reg                         jal_jump,       
    output reg                         jalr_jump,       // jalr jump flag

    output reg                         reg_wen,    // register write enable
    output reg [`REG_ADDR_WIDTH-1:0]   reg_waddr,  // register write address
    output reg [`REG_ADDR_WIDTH-1:0]   reg1_raddr, // register 1 read address
    output reg [`REG_ADDR_WIDTH-1:0]   reg2_raddr, // register 2 read address
    
    output reg [`IMM_GEN_OP_WIDTH-1:0] imm_gen_op, // immediate extend opcode

    output reg [`ALU_OP_WIDTH-1:0]     alu_op,     // alu opcode
    output reg [`ALU_SRC_WIDTH-1:0]    alu_src_sel // alu source select flag
);

wire [`OPCODE_WIDTH-1:0] opcode = inst[`OPCODE_WIDTH-1:0];            
wire [`FUNCT3_WIDTH-1:0] funct3 = inst[`FUNCT3_WIDTH+`FUNCT3_BASE-1:`FUNCT3_BASE];
wire [`FUNCT7_WIDTH-1:0] funct7 = inst[`FUNCT7_WIDTH+`FUNCT7_BASE-1:`FUNCT7_BASE]; 
wire [`REG_ADDR_WIDTH-1:0] rd   = inst[`REG_ADDR_WIDTH+`RD_BASE-1:`RD_BASE]; 
wire [`REG_ADDR_WIDTH-1:0] rs1  = inst[`REG_ADDR_WIDTH+`RS1_BASE-1:`RS1_BASE]; 
wire [`REG_ADDR_WIDTH-1:0] rs2  = inst[`REG_ADDR_WIDTH+`RS2_BASE-1:`RS2_BASE]; 
wire [11:0]             imm12   = inst[31:20];  // 用于 ebreak 指令的高 12 位

always @(*) begin
    branch      = 1'b0;
    jal_jump    = 1'b0;
    jalr_jump   = 1'b0;
    reg_wen     = 1'b0;
    reg1_raddr  = `REG_ADDR_WIDTH'b0;
    reg2_raddr  = `REG_ADDR_WIDTH'b0;
    reg_waddr   = `REG_ADDR_WIDTH'b0;
    imm_gen_op  = `IMM_GEN_I;
    alu_op      = `ALU_AND;
    alu_src_sel = `ALU_SRC_REG;

    // ebreak 检测：SYSTEM opcode + funct3==0 + imm12==1
    if (opcode ==  7'b1110011 && funct3 == 3'b000 && imm12 == 12'h001) begin
        // 通知仿真环境：执行 ebreak，退出仿真
        npc_trap(0);
    end
    
    case (opcode)
        `INST_TYPE_R: begin
            reg_wen     = 1'b1;
            reg1_raddr  = rs1;
            reg2_raddr  = rs2;
            reg_waddr   = rd;
            alu_src_sel = `ALU_SRC_REG;
            case (funct3)
                `INST_ADD_SUB: 
                    alu_op = (funct7 == `FUNCT7_INST_A) ? `ALU_ADD : `ALU_SUB; // A:add B:sub 
            endcase
        end
        `INST_TYPE_I: begin
            reg_wen     = 1'b1;
            reg1_raddr  = rs1;
            reg_waddr   = rd;
            alu_src_sel = `ALU_SRC_IMM;
            case (funct3)
                `INST_ADDI: 
                    alu_op = `ALU_ADD; 
            endcase
        end
        // JALR: I 型跳转指令
        `INST_JALR: begin
            jalr_jump        = 1'b1;
            reg_wen     = 1'b1;
            reg1_raddr  = rs1;
            reg_waddr   = rd;
            imm_gen_op  = `IMM_GEN_I;
            alu_op      = `ALU_ADD;
            alu_src_sel = `ALU_SRC_FOUR_PC; //pc + 4
        end
        `INST_TYPE_B: begin
            reg1_raddr  = rs1;
            reg2_raddr  = rs2;
            imm_gen_op  = `IMM_GEN_B;
            alu_src_sel = `ALU_SRC_REG;
            case (funct3)
                `INST_BNE: begin
                    branch     = 1'b1;
                    alu_op     = `ALU_SUB;
                end
            endcase
        end
        
        `INST_JAL: begin // only jal
            jal_jump        = 1'b1;
            reg_wen     = 1'b1;
            reg_waddr   = rd;
            imm_gen_op  = `IMM_GEN_J;
            alu_op      = `ALU_ADD;
            alu_src_sel = `ALU_SRC_FOUR_PC; //pc + 4   
        end
        `INST_LUI: begin // only lui
            reg_wen     = 1'b1;
            reg1_raddr  = `REG_ADDR_WIDTH'b0; // x0 = 0
            reg_waddr   = rd;
            imm_gen_op  = `IMM_GEN_U;
            alu_op      = `ALU_ADD;
            alu_src_sel = `ALU_SRC_IMM; // x0 + imm
        end
        `INST_AUIPC: begin
            reg_wen     = 1'b1;
            reg_waddr   = rd;
            imm_gen_op  = `IMM_GEN_U;
            alu_op      = `ALU_ADD;
            alu_src_sel = `ALU_SRC_IMM_PC; // pc + imm
        end
        `INST_TYPE_S: begin  //目前还是空指令，没有实现写入内存的操作
            reg1_raddr  = rs1;
            reg2_raddr  = rs2;
            imm_gen_op  = `IMM_GEN_S;
            alu_src_sel = `ALU_SRC_IMM; //
            case (funct3)
                `INST_SB: 
                    alu_op = `ALU_ADD; // store byte
                `INST_SH: 
                    alu_op = `ALU_ADD; // store halfword
                `INST_SW: 
                    alu_op = `ALU_ADD; // store word
            endcase
        end
    endcase 
end

endmodule