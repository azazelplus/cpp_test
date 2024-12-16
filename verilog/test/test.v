`timescale 1ns/1ps
//这个测试用来看一下非阻塞赋值后波形图的变化.


module b_to_a(
	input clk,rst,
	input b,
	output reg a
);
	always @(posedge clk or posedge rst)begin
		if(rst)
			a<=0;
		else
			a<=b;
	end
endmodule

//testbench
module tb();
	reg clk;
	reg rst;
	reg b;
	wire a;//输出必须是wire. 但是如果这个信号要在always块里赋值, 则必须为reg,这个优先级更高. (编译器会自动处理这个矛盾：内部用 reg，外部视为 wire。)
	
	//instantiate
	b_to_a uut(
		.clk(clk),
		.rst(rst),
		.a(a),
		.b(b)
	);
	
	//generate clock (circle: #10, 即10ns)
	initial begin
		clk=0;
		forever #5 clk=~clk;
	end
	
	//generate test data
	initial begin
		rst=1;b=0;
		#10 rst =0;//10s后解除rst, 仿真正式开始.
		
		//change b during 1st circle()
		#15 b=1;//15ns时令b=1
		#10 b=0;//25ns时令b=0
		
		
		//分析:第一个周期,即15ns~25ns. 15ns时, b被重置为1,
		
		
		#50;
		$stop;
	end
	

	
endmodule
		













