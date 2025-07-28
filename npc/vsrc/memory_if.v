`include "/home/wang/ysyx-workbench/npc/vsrc/rvseed_defines.v"

// === 1. DPI‑C 接口导入 ===
import "DPI-C" function int unsigned      pmem_read  (input int unsigned raddr,input int unsigned i);
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
  input                         unsigned_load,  // 1 = zero‑extend (lbu/lhu), 0 = sign‑extend (lb/lh)
  output reg [`CPU_WIDTH-1:0]   rdata           // 读出数据
);

  // 写掩码：4 位，每位对应一个 byte
  reg [3:0] wmask;
  always @(*) begin
    case (size)
      2'b00: wmask = 4'b0001 << addr[1:0];  // byte
      2'b01: wmask = 4'b0011 << addr[1:0];  // halfword (2 bytes)
      2'b10: wmask = 4'b1111;               // word (4 bytes)
      default: wmask = 4'b0000;
    endcase
  end

  // 读数据临时存放
  reg [31:0] raw_data;

  always @(*) begin
    if (valid) begin
      // 1) 读一个 word（32-bit）并根据 addr[1:0] 选出需要的字节/半字
      raw_data = pmem_read(addr & ~2'b11,2);  // 地址下两位清零，读对齐的 word

      // 2) 根据 size 和 unsigned_load 进行扩展
      case (size)
        2'b00: begin // byte
          case (addr[1:0])
            2'b00: rdata = unsigned_load
                           ? {24'd0, raw_data[ 7: 0]}       // lbu
                           : {{24{raw_data[ 7]}}, raw_data[ 7: 0]}; // lb
            2'b01: rdata = unsigned_load
                           ? {24'd0, raw_data[15: 8]}
                           : {{24{raw_data[15]}}, raw_data[15: 8]};
            2'b10: rdata = unsigned_load
                           ? {24'd0, raw_data[23:16]}
                           : {{24{raw_data[23]}}, raw_data[23:16]};
            2'b11: rdata = unsigned_load
                           ? {24'd0, raw_data[31:24]}
                           : {{24{raw_data[31]}}, raw_data[31:24]};
          endcase
        end

        2'b01: begin // halfword
          if (addr[1] == 1'b0) begin
            // low halfword
            rdata = unsigned_load
                     ? {16'd0, raw_data[15: 0]}       // lhu
                     : {{16{raw_data[15]}}, raw_data[15: 0]}; // lh
          end else begin
            // high halfword
            rdata = unsigned_load
                     ? {16'd0, raw_data[31:16]}
                     : {{16{raw_data[31]}}, raw_data[31:16]};
          end
        end

        2'b10: begin // word
          rdata = raw_data; // lw 总是无符号扩展到 32 位
        end

        default: rdata = 0;
      endcase

      // 3) 如果是 store，再发写请求
      if (wen) begin
        pmem_write(addr, wdata, wmask);
      end
    end
    else begin
      rdata = 0;
    end
  end

endmodule
