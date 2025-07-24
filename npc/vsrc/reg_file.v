`include "../vsrc/rvseed_defines.v"

// === 1. DPI‑C 函数导入 ===

module reg_file (
    input                               clk,
    input                               rst_n,

    input                               reg_wen,// Register write enable
    input       [`REG_ADDR_WIDTH-1:0]   reg_waddr,// Register write address
    input       [`CPU_WIDTH-1:0]        reg_wdata,

    input       [`REG_ADDR_WIDTH-1:0]   reg1_raddr, // Register read address 1
    input       [`REG_ADDR_WIDTH-1:0]   reg2_raddr, // Register read address 2
    output reg  [`CPU_WIDTH-1:0]        reg1_rdata, // Register read data
    output reg  [`CPU_WIDTH-1:0]        reg2_rdata, // Register read data
    output reg [`CPU_WIDTH-1:0]         reg_f [`REG_DATA_DEPTH-1:0] // Register file array
);

//reg [`CPU_WIDTH-1:0] reg_f [0:`REG_DATA_DEPTH-1];

// Register write operation
// always @(posedge clk or negedge rst_n) begin
//     if (rst_n && reg_wen && (reg_waddr != 0)) begin
//         reg_f[reg_waddr] <= reg_wdata; // Write data to register
//     end
// end
always @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        reg_f[reg_waddr] <= 0; // 原来的代码没有正确处理异步复位的逻辑
    end else if (reg_wen && (reg_waddr != 0)) begin
        reg_f[reg_waddr] <= reg_wdata;
    end
end


// register 1 read
always @(*) begin
    if (reg1_raddr == 0) begin
        reg1_rdata = 0; // Return 0 for register 0
    end else begin
        reg1_rdata = reg_f[reg1_raddr]; // Read data from register 1
    end
end
// register 2 read
always @(*) begin
    if (reg2_raddr == 0) begin
        reg2_rdata = 0; // Return 0 for register 0
    end else begin
        reg2_rdata = reg_f[reg2_raddr]; // Read data from register 2
    end
end

endmodule