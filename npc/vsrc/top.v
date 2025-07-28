//top.v  只实现了 ADDI 等算术／分支／跳转指令的最小子集 
//如果后续要加 BEQ、LUI、AUIPC、JALR、Load/Store 等，再补相应控制信号和数据通路即可。
`include "/home/wang/ysyx-workbench/npc/vsrc/rvseed_defines.v"
module  ysyx_25020059_top(
	input                         clk,
    input                         rst,
	output [31:0]                 inst,
	output[`CPU_WIDTH-1:0]        curr_pc,
    output[`CPU_WIDTH-1:0]        next_pc,
    output[`CPU_WIDTH-1:0]        reg_f [`REG_DATA_DEPTH-1:0] // Register file array
);
wire                         rst_n;
assign                       rst_n = !rst; // active low reset
wire                         ena;
//wire [`CPU_WIDTH-1:0]        curr_pc;    // current pc addr
//wire [`CPU_WIDTH-1:0]        next_pc;    // next pc addr

wire                         branch;     // branch flag
wire                         zero;       // alu result is zero
wire                         jal_jump;       // jump flag
wire                         jalr_jump;       // jalr jump flag

//wire [`CPU_WIDTH-1:0]        inst;       // instruction

wire                         reg_wen;    // register write enable
wire [`REG_ADDR_WIDTH-1:0]   reg_waddr;  // register write address
wire [`CPU_WIDTH-1:0]        reg_wdata;  // register write data
wire [`REG_ADDR_WIDTH-1:0]   reg1_raddr; // register 1 read address
wire [`REG_ADDR_WIDTH-1:0]   reg2_raddr; // register 2 read address
wire [`CPU_WIDTH-1:0]        reg1_rdata; // register 1 read data
wire [`CPU_WIDTH-1:0]        reg2_rdata; // register 2 read data

wire [`IMM_GEN_OP_WIDTH-1:0] imm_gen_op; // immediate extend opcode
wire [`CPU_WIDTH-1:0]        imm;        // immediate

wire [`ALU_OP_WIDTH-1:0]     alu_op;     // alu opcode
wire [`ALU_SRC_WIDTH-1:0]    alu_src_sel;// alu source select flag
wire [`CPU_WIDTH-1:0]        alu_src1;   // alu source 1
wire [`CPU_WIDTH-1:0]        alu_src2;   // alu source 2
wire [`CPU_WIDTH-1:0]        alu_res;    // alu result

wire                         mem_valid, mem_wen;
wire [1:0]                   mem_size;
wire                         mem_unsigned;
wire [`CPU_WIDTH-1:0]        mem_rdata;

//wire [`CPU_WIDTH-1:0]        inst; // Instruction fetched from memory


assign reg_wdata = (mem_valid && !mem_wen) ? mem_rdata : alu_res; // 如果是 load 指令，则写入读出的数据，否则写入 ALU 结果

pc_reg u_pc_reg_0(
    .clk                            ( clk                           ),
    .rst_n                          ( rst_n                         ),
    .ena                            ( ena                           ),
    .next_pc                        ( next_pc                       ),
    .curr_pc                        ( curr_pc                       ),
    .inst                           ( inst                          )
);

muxpc u_mux_pc_0(
    .ena                            ( ena                           ),
    .branch                         ( branch                        ),
    .reg1_rdata                     ( reg1_rdata                    ),
    .zero                           ( zero                          ),
    .jal_jump                       ( jal_jump                      ),
    .jalr_jump                      ( jalr_jump                     ),
    .imm                            ( imm                           ),
    .curr_pc                        ( curr_pc                       ),
    .next_pc                        ( next_pc                       )
);



ctrl u_ctrl_0(
    .inst                           ( inst                          ),
    .a0                             ( reg_f[10]                     ), // 假设 a0 寄存器为 reg_f[10]
    .branch                         ( branch                        ),
    .jal_jump                       ( jal_jump                      ),
    .jalr_jump                      ( jalr_jump                     ),
    .reg_wen                        ( reg_wen                       ),
    .reg1_raddr                     ( reg1_raddr                    ),
    .reg2_raddr                     ( reg2_raddr                    ),
    .reg_waddr                      ( reg_waddr                     ),
    .imm_gen_op                     ( imm_gen_op                    ),
    .alu_op                         ( alu_op                        ),
    .alu_src_sel                    ( alu_src_sel                   ),
    // …原有信号…
    .mem_valid                      (mem_valid                      ),
    .mem_wen                        (mem_wen                        ),
    .mem_size                       (mem_size                       ),
    .mem_unsigned                   (mem_unsigned                   )
//    .mem_wdata                      (mem_wdata                      )
);

reg_file u_reg_file_0(
    .clk                            ( clk                           ),
    .rst_n                          ( rst_n                         ),
    .reg_wen                        ( reg_wen                       ),
    .reg_waddr                      ( reg_waddr                     ),
    .reg_wdata                      ( reg_wdata                     ),
    .reg1_raddr                     ( reg1_raddr                    ),
    .reg2_raddr                     ( reg2_raddr                    ),
    .reg1_rdata                     ( reg1_rdata                    ),
    .reg2_rdata                     ( reg2_rdata                    ),
    .reg_f                          ( reg_f                         ) // Register file array
);

imm_gen u_imm_gen_0(
    .inst                           ( inst                          ),
    .imm_gen_op                     ( imm_gen_op                    ),
    .imm                            ( imm                           )
);

mux_alu u_mux_alu_0(
    .alu_src_sel                    ( alu_src_sel                   ),
    .reg1_rdata                     ( reg1_rdata                    ),
    .reg2_rdata                     ( reg2_rdata                    ),
    .imm                            ( imm                           ),
    .curr_pc                        ( curr_pc                       ),
    .alu_src1                       ( alu_src1                      ),
    .alu_src2                       ( alu_src2                      )
);

alu u_alu_0(
    .alu_op                         ( alu_op                        ),
    .alu_src1                       ( alu_src1                      ),
    .alu_src2                       ( alu_src2                      ),
    .zero                           ( zero                          ),
    .alu_res                        ( alu_res                       )
);

memory_if u_mem_if_0(
    .clk                            (clk),
    .rst_n                          (rst_n),
    .valid                          (mem_valid),
    .wen                            (mem_wen),
    .addr                           (alu_res), // 由 alu_res 提供地址
    .wdata                          (reg2_rdata), // 写数据来自寄存器 rs2
    .size                           (mem_size),
    .unsigned_load                  (mem_unsigned),
    .rdata                          (mem_rdata) // 读出数据,应该要跟加法的写入做一个选择
);



endmodule