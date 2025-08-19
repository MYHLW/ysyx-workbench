`include "/home/wang/ysyx-workbench/npc/vsrc/rvseed_defines.v"

module csr (
    input                           clk,
    input                           rst_n,

    // from ctrl
    input                           csr_read,
    input                           csr_write,
    input       [11:0]              csr_addr,
    input       [`REG_ADDR_WIDTH-1:0] csr_rs1_addr, // which GPR provides write data
    input       [`CPU_WIDTH-1:0]    reg1_rdata,     // GPR rs1 data (for CSR write)

    input       [1:0]               csr_op,         // 00=NONE, 01=CSRRW, 10=CSRRS

    input                           csr_ecall,
    input                           csr_mret,

    // for ecall: record current pc into mepc
    input       [`CPU_WIDTH-1:0]    curr_pc,

    // CSR read output (driven combinationally)
    output reg  [`CPU_WIDTH-1:0]    csr_rdata,

    // expose these CSR regs to top (按你要求作为顶层输出)
    output reg  [`CPU_WIDTH-1:0]    mstatus,
    output reg  [`CPU_WIDTH-1:0]    mtvec,
    output reg  [`CPU_WIDTH-1:0]    mepc,
    output reg  [`CPU_WIDTH-1:0]    mcause
);

// CSR addresses we care about (standard RISC-V)
// mstatus = 0x300, mtvec = 0x305, mepc = 0x341, mcause = 0x342
localparam CSR_MSTATUS = 12'h300;
localparam CSR_MTVEC   = 12'h305;
localparam CSR_MEPC    = 12'h341;
localparam CSR_MCAUSE  = 12'h342;

always @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        // reset CSRs
        mstatus <= 32'h0;
        mtvec   <= 32'h8000_0000; // 按你要求的默认值
        mepc    <= 32'h0;
        mcause  <= 32'h0;
        // NOTE: 不在时序块里对 csr_rdata 赋初值，csr_rdata 由组合块驱动
    end else begin
        // 1) CSR write for CSRRW / CSRRS
        if (csr_write) begin
            case (csr_addr)
                CSR_MSTATUS: begin
                    if (csr_op == 2'b01) begin // CSRRW
                        mstatus <= reg1_rdata;
                    end else if (csr_op == 2'b10) begin // CSRRS
                        mstatus <= mstatus | reg1_rdata;
                    end
                end
                CSR_MTVEC: begin
                    if (csr_op == 2'b01) mtvec <= reg1_rdata;
                    else if (csr_op == 2'b10) mtvec <= mtvec | reg1_rdata;
                end
                CSR_MEPC: begin
                    if (csr_op == 2'b01) mepc <= reg1_rdata;
                    else if (csr_op == 2'b10) mepc <= mepc | reg1_rdata;
                end
                CSR_MCAUSE: begin
                    if (csr_op == 2'b01) mcause <= reg1_rdata;
                    else if (csr_op == 2'b10) mcause <= mcause | reg1_rdata;
                end
                default: ; // ignore other CSRs for now
            endcase
        end

        // 2) ecall handling (raise trap)
        if (csr_ecall) begin
            mepc   <= curr_pc; // <-- 关键：保存 ecall 的下一条指令地址
            mcause <= 32'd11;      // ecall from M-mode: cause=11
            // Follow NEMU's isa_raise_intr behavior:
            mstatus <= 32'h0000_1800;
        end

        // 3) mret handling: restore status and clear mcause
        if (csr_mret) begin
            // apply NEMU-like sequence (use old mstatus on RHS)
            mstatus <= ( (mstatus & ~(1<<3))                 // clear MIE
                        | (( (mstatus & (1<<7)) >> 4))      // MPIE -> MIE
                        | (1<<7)                            // set MPIE = 1
                      ) & ~((1<<11) | (1<<12));              // clear MPP bits
            mcause  <= 32'h0;
            // mepc unchanged here (pc will be set by top/pc_reg using mepc)
        end
    end
end

// CSR read combinational (only place that assigns csr_rdata)
always @(*) begin
    if (csr_read) begin
        case (csr_addr)
            CSR_MSTATUS: csr_rdata = mstatus;
            CSR_MTVEC:   csr_rdata = mtvec;
            CSR_MEPC:    csr_rdata = mepc;
            CSR_MCAUSE:  csr_rdata = mcause;
            default:     csr_rdata = 32'h0;
        endcase
    end else begin
        csr_rdata = 32'h0;
    end
end

endmodule
