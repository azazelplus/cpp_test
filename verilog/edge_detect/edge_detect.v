module edge_detect (
    input clk,
    input in,
    output reg pedge
);
    reg [7:0] prev_in;//存储之前的in状态.对每一位有 pedge=(prev_in==0&in==1) , 这等价于pedge=~prev_in*in 

    //notice: 非阻塞赋值语句是parallel的. 顺序无关紧要.
    always @(posedge clk)begin
        pedge <= ~prev_in & in; // 检测从 0 -> 1 的跳变
        prev_in <= in;         // 更新前一周期输入状态
    end

endmodule


// Testbench 模块
module tb_edge_detect();
    reg clk;          // 生成时钟
    reg in;      
    wire pedge;     
    
	
    // 实例化被测试模块
    edge_detect uut (
        .clk(clk),
        .in(in),
        .pedge(pedge)
    );
    
    // 生成时钟信号，每 5ns 翻转一次（10ns周期 -> 100MHz时钟）
    initial begin
        clk = 0;
        forever #5 clk = ~clk;
    end
    
    // 生成测试信号 
    initial begin
        // 初始化
        in = 0; 

        #25 in = 1; 
               
        // 等待几个时钟周期观察波形
        #50;
        
        // 结束仿真
        $stop;
    end
    
 
endmodule