`include "../vsrc/rvseed_defines.v"

// 引入 DPI-C 接口
import "DPI-C" function void npc_itrace(input logic [31:0] pc);


module pc_reg (
    input                        clk,
    input                        rst_n,
    input       [`CPU_WIDTH-1:0] next_pc, // Next PC value
    output reg  [`CPU_WIDTH-1:0] curr_pc, // Current PC value
    output reg                   ena //system enable signal 可以用来控制整个 NPC 的启动，比如在没复位完之前屏蔽所有其他逻辑。
);

always @(posedge clk or negedge rst_n) begin
    if (!rst_n) begin
        ena <= 0; // Reset enable signal
        curr_pc <= 32'h8000_0000; // Reset current PC to 0
    end else begin
        ena <= 1; // Enable signal is set
        curr_pc <= next_pc; 
         // 在 PC 更新后调用 itrace
        npc_itrace(next_pc);
    end
end

endmodule
