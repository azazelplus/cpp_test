//set-reset触发器.
//真值表为:R为1则重置; 否则, S=1则输出1
module sr_ff(
    input clk,S,R,
    output reg Q
);
    always @(posedge clk) begin
        if(R)    //reset操作
            Q<=0;
        else if(S)//set操作
            Q<=1;
    end
endmodule




//32位的版本:


module top_module (
   input clk,         // 时钟信号
    input reset,       // 同步复位信号
    input [31:0] in,   // 32 位输入信号
    output reg [31:0] out // 32 位输出信号
);

    reg [31:0] prev_in;  // 32 位寄存器，用来保存上一个时钟周期的输入信号

    always @(posedge clk) begin
        if (reset) begin
            // 同步复位，所有输出都被置为 0
            out <= 32'b0;
        end 
        else begin
            // 捕捉 1 到 0 的变化
            for(int i=0;i<32;i++)begin:whatever
                    if(prev_in[i] & ~in[i])begin
                        out[i] <= 1; // 捕捉 1 到 0 的变化，`prev_in & ~in` 检测变化
                    end
                end

            end
            // 更新 prev_in 为当前输入
            prev_in <= in;       
    end
endmodule






