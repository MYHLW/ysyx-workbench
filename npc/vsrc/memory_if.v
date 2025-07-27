`include "../vsrc/rvseed_defines.v"

// === 1. DPI‑C 接口导入 ===
// 使用 SystemVerilog 内建类型，不用 C 头文件里的 uint32_t
import "DPI-C" function int unsigned      pmem_read  (input int unsigned raddr);
import "DPI-C" function        void       pmem_write (input int unsigned waddr,
                                                        input int unsigned wdata,
                                                        input byte           wmask);

module memory_if (
  input                  clk,
  input                  rst_n,
  input                  valid,          // load/store
  input                  wen,            // store?
  input [`CPU_WIDTH-1:0] addr,
  input [`CPU_WIDTH-1:0] wdata,
  input        [1:0]     size,
  input                  unsigned_load,
  output reg [`CPU_WIDTH-1:0] rdata
);

  // 流水寄存
  reg                  valid_r;
  reg                  wen_r;
  reg [`CPU_WIDTH-1:0] addr_r;
  reg [`CPU_WIDTH-1:0] wdata_r;
  reg         [1:0]    size_r;
  reg                  unsigned_load_r;

  always @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      valid_r        <= 0;
      wen_r          <= 0;
      addr_r         <= 0;
      wdata_r        <= 0;
      size_r         <= 0;
      unsigned_load_r<= 0;
      rdata          <= 0;
    end else begin
      // 拍寄所有输入
      valid_r        <= valid;
      wen_r          <= wen;
      addr_r         <= addr;
      wdata_r        <= wdata;
      size_r         <= size;
      unsigned_load_r<= unsigned_load;

      if (valid_r) begin
        // 1) 读操作
        if (!wen_r) begin
          int unsigned raw = pmem_read(addr_r);
          unique case (size_r)
            2'b00: rdata <= unsigned_load_r ? {24'b0, raw[7:0]} : {{24{raw[7]}}, raw[7:0]};
            2'b01: rdata <= unsigned_load_r ? {16'b0, raw[15:0]}: {{16{raw[15]}}, raw[15:0]};
            2'b10: rdata <= raw;
            default: rdata <= 0;
          endcase
        end
        // 2) 写操作
        else begin
          // 生成 wmask
          reg [3:0] wmask;
          case (size_r)
            2'b00: wmask = 4'b0001 << addr_r[1:0];
            2'b01: wmask = 4'b0011 << addr_r[1:0];
            2'b10: wmask = 4'b1111;
            default: wmask = 0;
          endcase
          pmem_write(addr_r, wdata_r, wmask);
        end
      end
    end
  end

endmodule

