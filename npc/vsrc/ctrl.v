`include "/home/wang/ysyx-workbench/npc/vsrc/rvseed_defines.v"

// === 1. DPI‑C 函数导入 ===
import "DPI-C" function void npc_trap(input int code);

module ctrl (
    input      [`CPU_WIDTH-1:0]        inst,       // instruction input
    input      [`CPU_WIDTH-1:0]        a0,         // a0 input

    output reg                         beq_branch,     // beq branch flag
    output reg                         bne_branch,     // bne branch flag
    output reg                         blt_branch,     // blt branch flag
    output reg                         bltu_branch,    // bltu branch flag
    output reg                         bge_branch,     // bge branch flag
    output reg                         bgeu_branch,    // bgeu branch flag
    output reg                         jal_jump,       
    output reg                         jalr_jump,       // jalr jump flag

    output reg                         reg_wen,    // register write enable
    output reg [`REG_ADDR_WIDTH-1:0]   reg_waddr,  // register write address
    output reg [`REG_ADDR_WIDTH-1:0]   reg1_raddr, // register 1 read address
    output reg [`REG_ADDR_WIDTH-1:0]   reg2_raddr, // register 2 read address
    
    output reg [`IMM_GEN_OP_WIDTH-1:0] imm_gen_op, // immediate extend opcode

    output reg [`ALU_OP_WIDTH-1:0]     alu_op,     // alu opcode
    output reg [`ALU_SRC_WIDTH-1:0]    alu_src_sel, // alu source select flag

    // === memory ===
    output reg                         mem_valid,       // 是 load/store 指令
    output reg                         mem_wen,         // store?
    output reg [1:0]                   mem_size,        // 00=byte, 10=word
    output reg                         mem_unsigned    // 对 load：是否零扩展
    //output reg [`CPU_WIDTH-1:0]        mem_wdata        // 由 reg2_rdata 提供
);

wire [`OPCODE_WIDTH-1:0] opcode = inst[`OPCODE_WIDTH-1:0];            
wire [`FUNCT3_WIDTH-1:0] funct3 = inst[`FUNCT3_WIDTH+`FUNCT3_BASE-1:`FUNCT3_BASE];
wire [`FUNCT7_WIDTH-1:0] funct7 = inst[`FUNCT7_WIDTH+`FUNCT7_BASE-1:`FUNCT7_BASE]; 
wire [`REG_ADDR_WIDTH-1:0] rd   = inst[`REG_ADDR_WIDTH+`RD_BASE-1:`RD_BASE]; 
wire [`REG_ADDR_WIDTH-1:0] rs1  = inst[`REG_ADDR_WIDTH+`RS1_BASE-1:`RS1_BASE]; 
wire [`REG_ADDR_WIDTH-1:0] rs2  = inst[`REG_ADDR_WIDTH+`RS2_BASE-1:`RS2_BASE]; 
wire [11:0]             imm12   = inst[31:20];  // 用于 ebreak 指令的高 12 位
wire [31:0]             code    = a0; 

always @(*) begin
    beq_branch  = 1'b0;
    bne_branch  = 1'b0;
    blt_branch  = 1'b0;
    bltu_branch = 1'b0;
    bge_branch  = 1'b0;
    bgeu_branch = 1'b0;
    jal_jump    = 1'b0;
    jalr_jump   = 1'b0;
    reg_wen     = 1'b0;
    reg1_raddr  = `REG_ADDR_WIDTH'b0;
    reg2_raddr  = `REG_ADDR_WIDTH'b0;
    reg_waddr   = `REG_ADDR_WIDTH'b0;
    imm_gen_op  = `IMM_GEN_I;
    alu_op      = `ALU_AND;
    alu_src_sel = `ALU_SRC_REG;
    mem_valid    = 0;
    mem_wen      = 0;
    mem_size     = 2'b00;
    mem_unsigned = 0;
    //mem_wdata    = `CPU_WIDTH'b0;

    // ebreak 检测：
    if (opcode ==  7'b1110011 && funct3 == 3'b000 && imm12 == 12'h001) begin
        npc_trap(code);
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
                `INST_SLT:
                    alu_op = `ALU_SLT;
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
                `INST_SLTIU:
                    alu_op = `ALU_SLTU;
                `INST_ANDI:
                    alu_op = `ALU_AND;
                `INST_SLLI:
                    alu_op = `ALU_SLL;
                `INST_SRLI_SRAI:
                    alu_op = (funct7 == `FUNCT7_INST_A) ? `ALU_SRL : `ALU_SRA;
            endcase
        end
        // JALR: I 型跳转指令
        `INST_JALR: begin
            jalr_jump        = 1'b1;
            reg_wen     = 1'b1;
            reg1_raddr  = rs1;
            reg_waddr   = rd;
            //imm_gen_op  = `IMM_GEN_I;
            alu_op      = `ALU_ADD;
            alu_src_sel = `ALU_SRC_FOUR_PC; //pc + 4
        end
        `INST_TYPE_B: begin
            reg1_raddr  = rs1;
            reg2_raddr  = rs2;
            imm_gen_op  = `IMM_GEN_B;
            alu_src_sel = `ALU_SRC_REG;
            case (funct3)
                `INST_BEQ: begin
                    beq_branch = 1'b1;
                    alu_op     = `ALU_SUB;
                end
                `INST_BNE: begin
                    bne_branch = 1'b1;
                    alu_op     = `ALU_SUB;
                end
                `INST_BLT: begin
                    blt_branch = 1'b1;
                    alu_op     = `ALU_BLT;
                end
                `INST_BLTU: begin
                    bltu_branch = 1'b1;
                    alu_op      = `ALU_BLTU;
                end
                `INST_BGE: begin
                    bge_branch = 1'b1; // 新增 bge_branch 信号
                    alu_op      = `ALU_BLT; // bge 可以通过 blt 的反向逻辑实现
                end
                `INST_BGEU: begin
                    bgeu_branch = 1'b1;
                    alu_op      = `ALU_BLTU;
                end
            endcase
        end
        
        `INST_JAL: begin // only jal
            jal_jump    = 1'b1;
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
        `INST_TYPE_S: begin
            mem_valid   = 1'b1; // load/store 指令
            mem_wen     = 1'b1; // store
            reg_wen     = 1'b0; // store 不写寄存器
            //mem_wdata   = reg2_rdata; // 写数据来自寄存器rs2          
            reg1_raddr  = rs1;
            reg2_raddr  = rs2;
            imm_gen_op  = `IMM_GEN_S;
            alu_src_sel = `ALU_SRC_IMM; // src1 = reg1_rdata, src2 = imm
            case (funct3)
                `INST_SB: begin
                    alu_op = `ALU_ADD; // store byte
                    mem_size = 2'b00; // byte
                end
                `INST_SH: begin
                    alu_op = `ALU_ADD; // store halfword
                    mem_size = 2'b01; // halfword
                end
                `INST_SW: begin
                    alu_op = `ALU_ADD; // store word
                    mem_size = 2'b10; // word
                end
            endcase
        end
        `INST_TYPE_IL: begin // lb/lh/lw/lbu/lhu
            mem_valid   = 1'b1; // load/store 指令
            mem_wen     = 1'b0;  // load
            reg_wen     = 1'b1;
            reg1_raddr  = rs1;
            reg_waddr   = rd;
            imm_gen_op  = `IMM_GEN_I; 
            alu_src_sel = `ALU_SRC_IMM;
            case (funct3)
                `INST_LB: begin
                    alu_op = `ALU_ADD; // load byte
                    mem_size = 2'b00; // byte
                    mem_unsigned = 1'b0; // lb
                end
                `INST_LH: begin
                    alu_op = `ALU_ADD; // load halfword
                    mem_size = 2'b01; // halfword
                    mem_unsigned = 1'b0; // lh
                end
                `INST_LW: begin
                    alu_op = `ALU_ADD; // load word
                    mem_size = 2'b10; // word
                    mem_unsigned = 1'b0; // lw
                end
                `INST_LBU: begin
                    alu_op = `ALU_ADD; // load byte unsigned
                    mem_size = 2'b00; // byte
                    mem_unsigned = 1'b1; // lbu 需要零扩展
                end
                `INST_LHU: begin
                    alu_op = `ALU_ADD; // load halfword unsigned
                    mem_size = 2'b01; // halfword
                    mem_unsigned = 1'b1; // lhu
                end
            endcase
            
            // mem_valid   = 1'b1;
            // mem_wen     = (opcode == `INST_TYPE_S) ? 1'b1 : 1'b0;
            // mem_wdata   = reg2_rdata;
        end

            


    endcase 
end

endmodule