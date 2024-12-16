//a simple adder by azazel.



//notice that A,B,sum are all default to type `wire`.
module adder_4bit(
	input [3:0] A,
	input [3:0] B,
	output [4:0] SUM
);
	assign SUM = A+B;
endmodule