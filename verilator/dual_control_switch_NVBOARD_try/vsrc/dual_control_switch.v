`timescale 1ns/1ps


module dual_control_switch(
    // 对应 NVBoard 的 SW0, SW1
    input  wire a,  
    input  wire b,  

    // 对应 NVBoard 的 LEDR0
    output wire f   
);
	assign f= a^b;

endmodule
