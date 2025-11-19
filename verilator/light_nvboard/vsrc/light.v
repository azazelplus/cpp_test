// 为了接入nvboard, 保持原有逻辑不变，仅做以下调整：
// 1. 移除仿真部分和$finish语句（硬件不需要仿真结束）
// 2. 将led改为wire类型(多一个led_reg)

module light(
	input clk,
	input rst,
	output [15:0] led
);
	reg [15:0]led_reg;
	assign led = led_reg;
	parameter breath_time = 5000000;	//流水灯的流水周期为0.5s
	//parameter sim_cycle = 100000;	//仿真周期数
	reg [31:0] count;	//记录流水灯距离上一次移位的时间
	//reg [31:0] cycle_count;	//for counting sim cycle。
	always @(posedge clk)begin
		if(rst) begin
			led_reg<=1;
			count<=0;
		end else begin
			if(count ==0) led_reg<={led_reg[14:0],led_reg[15]};
			count <= (count==breath_time) ? 32'b0 : count+32'b1;
			//cycle_count <= cycle_count+1;	//仿真周期+1
		end
		
		//if(cycle_count==sim_cycle) $finish;	//$finish用来被cpp中的Verilated::gotFinish()函数捕获.
		
	end
endmodule














