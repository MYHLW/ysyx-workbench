`include "../vsrc/rvseed_defines.v"

// === 1. DPI‑C 接口导入 ===
import "DPI-C" function logic [31:0]    pmem_read  (input logic [31:0] raddr);
import "DPI-C" function void        pmem_write (input int waddr,input int wdata,input byte wmask);

module memory_if (
  input                         clk,
  input                         rst_n,
  input                         valid,    // 指令是否为 load/store
  input                         wen,      // store?
  input    [`CPU_WIDTH-1:0]     addr,     // 访问地址
  input    [`CPU_WIDTH-1:0]     wdata,    // 写数据
  input    [1:0]                size,     // 00=byte, 10=word
  input                         unsigned_load, // lb vs lbu
  output   [`CPU_WIDTH-1:0]     rdata     // 读出数据
);

  // 计算写掩码 wmask：只对低两位有效
  wire [3:0] wmask;
  always @(*) begin
    case (size)
      2'b00: wmask = 4'b0001 << (addr[1:0]);  // byte
      2'b10: wmask = 4'b1111;                 // word
      default: wmask = 4'b0000;
    endcase
  end

  always @(*) begin
    if (!valid) begin
      rdata = 0;
    end else begin
      // 先读
      int raw = pmem_read(addr);
      // 根据 load 类型做符号／零扩展
      case (size)
        2'b00: // byte
          rdata = unsigned_load
                  ? {24'b0, raw[7:0]}
                  : {{24{raw[7]}}, raw[7:0]};
        2'b01: // halfword
          rdata = unsigned_load
                  ? {16'b0, raw[15:0]}
                  : {{16{raw[15]}}, raw[15:0]};
        2'b10: // word
          rdata = raw;
        default:
          rdata = 0;
      endcase

      // 再写（如果是 store）
      if (wen) begin
        pmem_write(addr, wdata, wmask);
      end
    end
  end

endmodule
