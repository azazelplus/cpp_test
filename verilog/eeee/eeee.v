`timescale 1ns/1ps

// 模块定义：实现非阻塞赋值，检测输入信号的打拍（slap）效果
module slap_b_to_a(
    input clk,
    input rst,
    input b,
    output reg a
);
    always @(posedge clk or posedge rst) begin
        if (rst)
            a <= 0; // 当复位信号有效时，输出清零
        else
            a <= b; // 否则，输出等于输入的非阻塞赋值
    end
endmodule

// Testbench
module tb_slap_b_to_a();
    reg clk; // 时钟信号
    reg rst; // 复位信号
    reg b;   // 输入信号
    wire a;  // 输出信号

    // 实例化被测模块
    slap_b_to_a uut (
        .clk(clk),
        .rst(rst),
        .b(b),
        .a(a)
    );

    // 生成时钟信号：周期 10ns（100MHz）
    initial begin
        clk = 0;
        forever #5 clk = ~clk; // 每 5ns 翻转
    end

    // 生成测试信号
    initial begin
        // 初始化信号
        rst = 1; b = 0;

        // 10ns 后释放复位
        #10 rst = 0;

        // 在第一个时钟周期内改变输入信号 b
        #15 b = 1; // 15ns 时 b = 1
        #10 b = 0; // 25ns 时 b = 0

        // 多周期观察
        #50;

        // 结束仿真
        $stop;
    end
endmodule
