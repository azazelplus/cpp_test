`timescale 1ns/1ps
//这个测试用来看一下非阻塞赋值(打拍slap)后波形图的变化.
//打拍(slap): 如果想得到信号signal的滞后一个周期的信号signal_prev, 可以在always块里进行`signal_prev <= signal;`
//结果: internal1和in同步 internal2比internal1之后一个周期, out比internal2滞后一个周期,共滞后in两个周期.
//之所以internal1和in同步, 是因为in是被testbench模块进行阻塞赋值导致的. 
//接下来的环节就是<=一次滞后一个周期啦!
module slap(
	input clk,rst,
	input in,
	output reg internal1,internal2,out
);

	//reg internal1,internal2;
	always @(posedge clk or posedge rst)begin
		if(rst)
			out<=0;
		else
			internal1<=in;
			internal2<=internal1;
			out <=internal2;
	end
endmodule

//testbench
module tb_slap();
	reg clk;
	reg rst;
	reg in;
	wire out;//输出必须是wire. 但是如果这个信号要在always块里赋值, 则必须为reg,这个优先级更高. (编译器会自动处理这个矛盾：内部用 reg，外部视为 wire。)
	
	//instantiate
	slap uut(
		.clk(clk),
		.rst(rst),
		.in(in),
		.out(out),
		.internal1(internal1),
		.internal2(internal2)
	);
	
	//generate clock (circle: #10, 即10ns)
	initial begin
		clk=0;
		forever #5 clk=~clk;
	end
	
	//generate test data
	initial begin
		rst=1;
		in=0;
		#10 rst =0;//10s后解除rst, 仿真正式开始.
		
		//change b during 1st circle()
		#15 in<=1;//15ns时(第一个周期上沿)令in=1
		#10 in=0;//25ns时(第二个周期上沿)令in=0
		
		
		//分析:在第一个周期上沿, 按照以下顺序执行:
		//1. `in=1;` [active event] 阻塞赋值在所有活动事件中优先级最高. 最先进行. 
		//2. `internal1 <= in;`, `internal2<=internal1;`, `out <=internal2;` 三个非阻塞赋值对右值的读取. [active event] 
		//3. 上面三个阻塞赋值对左值的更改. [inactive event]

		//于是internal1读取到右值1, 而internal2,out读取到右值0. 然后它们分别各自赋值.
		//于是, internal1和in同步, 在第一个周期上沿就变化, 而internal2和out读到了0, 不变.

		#50;
		$stop;
	end	
endmodule
		













