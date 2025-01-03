//一个简单的FSM.
//有两个状态A和B，(状态)输入in，输出out。
//当输入为1时，状态保持不变，当输入为0时，状态在下个时钟周期切换。(状态转移规则)
//当state为A时，out为1，当state为B时，out为0。(状态输出规则)

	//a FSM is usually coded in 3 parts: 
	//1.state register 状态寄存器
	//2.state transform logic 状态转移逻辑(combinational logic)
	//3.state output logic 状态输出逻辑(sequence logic)

module top_module (
	input clk,
	input in,
	input areset,//asynchronous reset
	output reg out
);

	//1.state register. assign states.(give name and value)
    parameter A=666,B=233;//it doesnt matter what value we give to each state, as long as they are different.
	//but if assigning large values, the state register may need more bits.(此处因为用了666这样的搞怪数字，所以state和next_state需要很多位)
	reg [10:0]state,next_state;//`state` and `next_state` register. Used to store the current state and the next state.
	

	//2.state transform logic.
	//given the current `state` and the `input`, calculate the `next state`.
	always @(*)begin
		case(state)
			A: next_state = in ? A : B;
			B: next_state = in ? B : A;
		endcase
	end

	always @(posedge clk or posedge areset)begin
		if(areset)	state <= B;//reset to state B
		else state <= next_state;//otherwise, update the state.
	end


	//3.state output logic.	
	//A: out = 0; 
	//B: out = 1;
	always @(*)begin
		case(state)
			A: out = 1'b0;
			B: out = 1'b1;
		endcase
	end
endmodule