`include "/home/wang/ysyx-workbench/npc/vsrc/rvseed_defines.v"

//import "DPI-C" function int unsigned      pmem_read  (input int unsigned raddr,input int unsigned i);

module pc_reg (
    input                        clk,
    input                        rst_n,
    input       [`CPU_WIDTH-1:0] next_pc, // Next PC value
    output reg  [`CPU_WIDTH-1:0] curr_pc, // Current PC value
    output reg                   ena, //system enable signal 可以用来控制整个 NPC 的启动，比如在没复位完之前屏蔽所有其他逻辑。
    input                        csr_mret, // when asserted, restore mepc
    input                        csr_ecall, // when asserted, jump to mtvec
    input       [`CPU_WIDTH-1:0] mepc,
    input       [`CPU_WIDTH-1:0] mtvec,
    output reg  [`CPU_WIDTH-1:0] inst // Instruction fetched from memory
);
//pc_reg 用 csr_mret / csr_ecall 和 mepc / mtvec 来决定 use_pc，从而把 mret/ecall 的控制放到取指处（单周期行为
reg [`CPU_WIDTH-1:0] use_pc;

always @(*) begin
    // choose which PC to fetch: priority mret > ecall > normal next_pc
    if (csr_mret) begin
        use_pc = mepc;
    end else if (csr_ecall) begin
        use_pc = mtvec;
    end else begin
        use_pc = next_pc;
    end
end

always @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        ena <= 0; // Reset enable signal
        curr_pc <= 32'h8000_0000; // Reset current PC to default
        inst <= 32'h0;
    end else begin
        ena <= 1;
        // fetch instruction at chosen PC (use_pc)
        inst <= pmem_read(use_pc,1);
        curr_pc <= use_pc;
    end
end

endmodule
