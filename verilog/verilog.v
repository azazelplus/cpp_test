//flow_led module by azazel 2024.10.17

module flow_led(
    input               sys_clk,    //system clock
    input               sys_rst_n,  //system_reset(negative_volt-effective)
    
    output reg [3:0]    led         //4 leds. *if not declear `reg`, the port variables will defult to  `wire` type.
    );     

//reg define
reg [23:0] counter;                 //create a 24 bit-width register(a counter that counts the clk.) 

//**************************************
//*****         main code
//**************************************

//use `counter` to count the sys_clk, timing for 0.2 sec. 
always @(posedge sys_clk or negedge sys_rst_n) begin 
    if(!sys_rst_n)
        counter <= 24'd0;   //when reset,  zero-ize the counter.
    else if (counter < 24'd1000_0000)
        counter <= counter +1'b1;   //当only  sys_clk上升时, 计数器+1.
    else
           counter <= 24'd0;    //当 counter达到上限后, 清零.



//use shift register(移位寄存器) to control the high/low levels of IO port, thereby changing the state of leds.
always @(posedge sys_clk or negedge sys_rst_n) begin  //`always` snippet works when: sys_clk having a posedg, or sys_rst_n having a negedg.
    if (!sys_rst_n)
        led <= 4'b0001;     //when sys_rst_n is 0, put led to 0001(primary status)
    else if (counter == 24'd1000000)
        led <= {led[2:0], led[3]};  //当计数器达到
    else
        led <= led;     //sustain current state. (in fact this line is redundant.)




//use shift register(移位寄存器) to control the high/low levels of IO port, thereby changing the state of leds.














