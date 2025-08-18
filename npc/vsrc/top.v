`include "/home/wang/ysyx-workbench/npc/vsrc/rvseed_defines.v"
module  ysyx_25020059_top(
    input                         clk,
    input                         rst,
    output [31:0]                 inst,
    output[`CPU_WIDTH-1:0]        curr_pc,
    output[`CPU_WIDTH-1:0]        next_pc,
    output[`CPU_WIDTH-1:0]        reg_f [`REG_DATA_DEPTH-1:0], // Register file array

    // expose CSR regs as top outputs (按你要求为 output reg [31:0]，我在 module body 用组合赋值把它们驱动)
    output reg [31:0]             o_mstatus,
    output reg [31:0]             o_mtvec,
    output reg [31:0]             o_mepc,
    output reg [31:0]             o_mcause
);

wire                         rst_n;
assign                       rst_n = !rst; // active low reset
wire                         ena;

wire                         beq_branch;     // beq branch flag
wire                         bne_branch;     // bne branch flag
wire                         blt_branch;     // blt branch flag
wire                         bltu_branch;    // bltu branch flag
wire                         bge_branch;
wire                         bgeu_branch;    // bgeu branch flag
wire                         zero;       // alu result is zero
wire                         jal_jump;       // jump flag
wire                         jalr_jump;       // jalr jump flag

wire                         reg_wen;    // register write enable
wire [`REG_ADDR_WIDTH-1:0]   reg_waddr;  // register write address
wire [`CPU_WIDTH-1:0]        reg_wdata_internal;  // candidate write data
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

// CSR signals from ctrl
wire                         csr_read;
wire                         csr_write;
wire [11:0]                  csr_addr;
wire [`REG_ADDR_WIDTH-1:0]   csr_rs1_addr;
wire                         csr_mret;
wire                         csr_ecall;
wire [1:0]                   csr_op;

// CSR module outputs
wire [`CPU_WIDTH-1:0]        csr_rdata;
wire [`CPU_WIDTH-1:0]        csr_mstatus;
wire [`CPU_WIDTH-1:0]        csr_mtvec;
wire [`CPU_WIDTH-1:0]        csr_mepc;
wire [`CPU_WIDTH-1:0]        csr_mcause;

// next_pc from muxpc (normal next_pc); later pc_reg will choose mret/ecall override
wire [`CPU_WIDTH-1:0]        next_pc_from_mux;

// choose reg_wdata: CSR read (csrr*) has priority for writing back to rd
assign reg_wdata_internal = (csr_read) ? csr_rdata :
                            ((mem_valid && !mem_wen) ? mem_rdata : alu_res);

// connect final outputs (reg_f is produced by reg_file)
wire [`CPU_WIDTH-1:0]        reg_wdata = reg_wdata_internal;

// instantiate modules
pc_reg u_pc_reg_0(
    .clk                            ( clk                           ),
    .rst_n                          ( rst_n                         ),
    .next_pc                        ( next_pc_from_mux              ),
    .csr_mret                       ( csr_mret                      ),
    .csr_ecall                      ( csr_ecall                     ),
    .mepc                           ( csr_mepc                      ),
    .mtvec                          ( csr_mtvec                     ),
    .curr_pc                        ( curr_pc                       ),
    .ena                            ( ena                           ),
    .inst                           ( inst                          )
);

muxpc u_mux_pc_0(
    .ena                            ( ena                           ),
    .beq_branch                     ( beq_branch                    ),
    .bne_branch                     ( bne_branch                    ),
    .blt_branch                     ( blt_branch                    ),
    .bltu_branch                    ( bltu_branch                   ),
    .bge_branch                     ( bge_branch                    ),
    .bgeu_branch                    ( bgeu_branch                   ),
    .reg1_rdata                     ( reg1_rdata                    ),
    .zero                           ( zero                          ),
    .jal_jump                       ( jal_jump                      ),
    .jalr_jump                      ( jalr_jump                     ),
    .imm                            ( imm                           ),
    .curr_pc                        ( curr_pc                       ),
    .next_pc                        ( next_pc_from_mux              )
);

// pass a0 as reg_f[10] like before; reg_f is an output from reg_file instance
ctrl u_ctrl_0(
    .inst                           ( inst                          ),
    .a0                             ( reg_f[10]                     ),
    .beq_branch                     ( beq_branch                    ),
    .bne_branch                     ( bne_branch                    ),
    .blt_branch                     ( blt_branch                    ),
    .bltu_branch                    ( bltu_branch                   ),
    .bge_branch                     ( bge_branch                    ),
    .bgeu_branch                    ( bgeu_branch                   ),
    .jal_jump                       ( jal_jump                      ),
    .jalr_jump                      ( jalr_jump                     ),
    .reg_wen                        ( reg_wen                       ),
    .reg1_raddr                     ( reg1_raddr                    ),
    .reg2_raddr                     ( reg2_raddr                    ),
    .reg_waddr                      ( reg_waddr                     ),
    .imm_gen_op                     ( imm_gen_op                    ),
    .alu_op                         ( alu_op                        ),
    .alu_src_sel                    ( alu_src_sel                   ),
    .mem_valid                      ( mem_valid                     ),
    .mem_wen                        ( mem_wen                       ),
    .mem_size                       ( mem_size                      ),
    .mem_unsigned                   ( mem_unsigned                  ),
    // CSR interface
    .csr_read                       ( csr_read                      ),
    .csr_write                      ( csr_write                     ),
    .csr_addr                       ( csr_addr                      ),
    .csr_rs1_addr                   ( csr_rs1_addr                  ),
    .csr_mret                       ( csr_mret                      ),
    .csr_ecall                      ( csr_ecall                     ),
    .csr_op                         ( csr_op                        )
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

// CSR instance: use reg1_rdata as write source when ctrl requests write
csr u_csr_0(
    .clk                            ( clk                           ),
    .rst_n                          ( rst_n                         ),
    .csr_read                       ( csr_read                      ),
    .csr_write                      ( csr_write                     ),
    .csr_addr                       ( csr_addr                      ),
    .csr_rs1_addr                   ( csr_rs1_addr                  ),
    .reg1_rdata                     ( reg1_rdata                    ),
    .csr_ecall                      ( csr_ecall                     ),
    .csr_mret                       ( csr_mret                      ),
    .curr_pc                        ( curr_pc                       ),
    .csr_rdata                      ( csr_rdata                     ),
    .mstatus                        ( csr_mstatus                   ),
    .mtvec                          ( csr_mtvec                     ),
    .mepc                           ( csr_mepc                      ),
    .mcause                         ( csr_mcause                    ),
    .csr_op                         ( csr_op                        )
);

// imm_gen, mux_alu, alu, memory_if unchanged:
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
    .rdata                          (mem_rdata) // 读出数据
);

// drive top-level CSR outputs (you asked them to be output reg)
always @(*) begin
    o_mstatus = csr_mstatus;
    o_mtvec   = csr_mtvec;
    o_mepc    = csr_mepc;
    o_mcause  = csr_mcause;
end

// For convenience expose next_pc as the mux output (note pc_reg may override when mret/ecall)
assign next_pc = next_pc_from_mux;

endmodule
