

module light(
	input clk,
	input rst,
	output reg [15:0] led
);
	parameter breath_time = 5000;	//呼吸灯发的呼吸周期
	parameter sim_cycle = 100000;	//仿真周期数
	reg [31:0] count;
	reg [31:0] cycle_count;	//for counting sim cycle。
	always @(posedge clk)begin
		if(rst) begin
			led<=1;
			count<=0;
		end else begin
			if(count ==0) led<={led[14:0],led[15]};
			count <= (count==breath_time) ? 32'b0 : count+32'b1;
			cycle_count <= cycle_count+1;	//仿真周期+1
		end
		
		if(cycle_count==sim_cycle) $finish;	//$finish用来被cpp中的Verilated::gotFinish()函数捕获.
		
	end
endmodule














