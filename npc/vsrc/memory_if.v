`include "../vsrc/rvseed_defines.v"

// === 1. DPI‑C 接口导入 ===
// 使用 SystemVerilog 内建类型，不用 C 头文件里的 uint32_t
import "DPI-C" function int unsigned      pmem_read  (input int unsigned raddr);
import "DPI-C" function        void       pmem_write (input int unsigned waddr,
                                                        input int unsigned wdata,
                                                        input byte           wmask);

module memory_if (
  input                         clk,
  input                         rst_n,
  input                         valid,          // 指令是否为 load/store
  input                         wen,            // store?
  input  [`CPU_WIDTH-1:0]       addr,           // 访问地址
  input  [`CPU_WIDTH-1:0]       wdata,          // 写数据
  input  [1:0]                  size,           // 00=byte, 01=halfword, 10=word
  input                         unsigned_load,  // lb vs lbu, lh vs lhu
  output reg [`CPU_WIDTH-1:0]   rdata           // 读出数据
);

  // 写掩码：4 位，每位对应一个 byte
  reg [3:0] wmask;
  always @(*) begin
    case (size)
      2'b00: wmask = 4'b0001 << addr[1:0];  // byte
      2'b01: wmask = 4'b0011 << addr[1:0];  // halfword
      2'b10: wmask = 4'b1111;               // word
      default: wmask = 4'b0000;
    endcase
  end

  always @(*) begin
    if (valid) begin // 有读写请求时
      // 1) 发起读请求
      rdata = pmem_read(addr);

      // 2) 发起写请求（如果是 store）
      if (wen) begin
        pmem_write(addr, wdata, wmask);
      end
    end
    else begin
      rdata = '0;
    end
  end

endmodule
