`timescale 1ns / 1ns

module adder_4bit_tb;
//notice! this module do not have any input or output!
//tb模块用reg和wire来定义输入和输出信号. 
//reg类型储存input并在仿真中驱动他们. 
//wire类型连接output, 使testbench模块可以通过监视wire来监视output的行为.

    // define DUT input and output signal
    reg [3:0] A;
    reg [3:0] B;
    wire [4:0] SUM;
    
    // instantiate the uut.实例化待测单元adder_4bit. uut: device under test.
    adder_4bit uut( 
        .A(A),
        .B(B),
        .SUM(SUM)
    );
    
    //initial the block
    initial begin
    
        //display sim form
        $monitor("Time=%0t A=%b B=%b SUM=%b", $time, A, B, SUM);
        //monitor是一个仿真任务, 用于在仿真期间实时实时显示指定信号的变化. 当监视的信号(此处为A,B,SUM)发生变化时, 输出指定信息到仿真控制台.
        //()内是C风格的格式化字符串, 指定了输出信息的格式. %b即以二进制格式显示. `$time`是内建变量.其值为当前仿真时间.
        
        //set 4 different group of input test. delay 10ns each.
            A = 4'b0001; B = 4'b0010; #10; // SUM 应为 3
            A = 4'b0101; B = 4'b0011; #10; // SUM 应为 8
            A = 4'b1111; B = 4'b0001; #10; // SUM 应为 16
            A = 4'b1010; B = 4'b0101; #10; // SUM 应为 15
			A = 4'b1010; B = 4'b0000; #10; // SUM 应为 10
            
        $finish;
    end
    
endmodule
    
    
    