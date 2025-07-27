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

  // 写掩码寄存器
  reg [3:0] wmask_reg;
  reg [`CPU_WIDTH-1:0] wdata_reg;
  reg [`CPU_WIDTH-1:0] addr_reg;
  reg write_pending;
  
  // 写掩码生成（组合逻辑）
  always @(*) begin
    case (size)
      2'b00: wmask = 4'b0001 << addr[1:0];  // byte
      2'b01: wmask = 4'b0011 << addr[1:0];  // halfword
      2'b10: wmask = 4'b1111;               // word
      default: wmask = 4'b0000;
    endcase
  end

  // 读路径：组合逻辑
  always @(*) begin
    if (!valid || wen) begin  // 写操作时不产生读数据
      rdata = '0;
    end else begin
      int unsigned raw = pmem_read(addr);
      
      case (size)
        2'b00: rdata = unsigned_load ? {24'b0, raw[7:0]} : {{24{raw[7]}}, raw[7:0]};
        2'b01: rdata = unsigned_load ? {16'b0, raw[15:0]} : {{16{raw[15]}}, raw[15:0]};
        2'b10: rdata = raw;
        default: rdata = '0;
      endcase
    end
  end

  // 写路径：时序逻辑（同步写操作）
  always @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
      write_pending <= 1'b0;
    end else begin
      // 捕获写请求
      if (valid && wen) begin
        wmask_reg <= wmask;
        wdata_reg <= wdata;
        addr_reg <= addr;
        write_pending <= 1'b1;
      end else begin
        write_pending <= 1'b0;
      end
      
      // 执行写操作
      if (write_pending) begin
        pmem_write(addr_reg, wdata_reg, wmask_reg);
      end
    end
  end

endmodule
