`include "/home/wang/ysyx-workbench/npc/vsrc/rvseed_defines.v"

// === 1. DPI‑C 接口导入 ===
// 使用 SystemVerilog 内建类型，不用 C 头文件里的 uint32_t
import "DPI-C" function int unsigned      pmem_read  (input int unsigned raddr,input int i);
import "DPI-C" function        void       pmem_write (input int unsigned waddr,
                                                        input int unsigned wdata,
                                                        input byte           wmask);

module memory_if (
  input                         clk,
  input                         rst_n,
  input                         valid,          // 有效访存（load/store）周期
  input                         wen,            // store？为 1 则写，否则读
  input  [`CPU_WIDTH-1:0]       addr,           // 访问地址（字节级）
  input  [`CPU_WIDTH-1:0]       wdata,          // 写数据（32 位）
  input  [1:0]                  size,           // 00=byte, 01=halfword, 10=word
  input                         unsigned_load,  // 1=LBU/LHU，0=LB/LH
  output reg [`CPU_WIDTH-1:0]   rdata           // 读出数据（32 位）
);

  // 写掩码：4 位，每位对应一个 byte
  reg [3:0] wmask;
  always @(*) begin
    case (size)
      2'b00: wmask = 4'b0001 << addr[1:0];  // SB: 只写一个 byte
      2'b01: wmask = 4'b0011 << addr[1:0];  // SH: 写两个连续 byte（低半字或跨边界）
      2'b10: wmask = 4'b1111;               // SW: 写整字
      default: wmask = 4'b0000;
    endcase
  end

  // 主组合逻辑：发起读/写，并做 load 时的字节提取和符号/零扩展
  always @(*) begin
    if (valid) begin
      // 1) 直接从 DPI-C 读整字
      int unsigned raw = pmem_read(addr);

      // 2) 如果是写操作（store），马上发起
      if (wen) begin
        pmem_write(addr, wdata, wmask);
      end

      // 3) 如果是读操作，根据 size 和 unsigned_load 提取/扩展
      if (!wen) begin
        case (size)
          2'b00: begin  // Byte
            // 取出对应字节
            case (addr[1:0])
              2'd0: rdata = raw[7:0];
              2'd1: rdata = raw[15:8];
              2'd2: rdata = raw[23:16];
              2'd3: rdata = raw[31:24];
            endcase
            // 符号扩展或零扩展
            if (!unsigned_load)
              rdata = { {24{rdata[7]}}, rdata[7:0] };  // LB
            else
              rdata = { 24'd0, rdata[7:0] };          // LBU
          end

          2'b01: begin  // Halfword
            // 取出对应半字
            if (addr[1] == 1'b0)
              rdata = raw[15:0];
            else
              rdata = raw[31:16];
            // 符号扩展或零扩展
            if (!unsigned_load)
              rdata = { {16{rdata[15]}}, rdata[15:0] };  // LH
            else
              rdata = { 16'd0, rdata[15:0] };            // LHU
          end

          2'b10: begin  // Word
            rdata = raw;  // LW
          end

          default: rdata = '0;
        endcase
      end
    end
    else begin
      rdata = '0;
    end
  end

endmodule
