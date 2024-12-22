//module clock(
module top_module(
    input clk,
    input reset,//同步复位
    input ena,//电子钟开关
    output pm,//0上午,1下午
    output [7:0] hh,
    output [7:0] mm,
    output [7:0] ss); 

    //声明信号,连接到输入
    reg [3:0] h1,h2,m1,m2,s1,s2,pm_reg;
    reg hena, mena, sena, pmena;
    assign hh = {h2,h1};
    assign mm = {m2,m1};
    assign ss = {s2,s1};
    //assign pm_reg = pm;

    //例化模块
    bcdcounter_1to12 hhcounter(clk, reset, hena, h1, h2);
    bcdcounter_0to59 mmcounter(clk, reset, mena, m1,m2);
    bcdcounter_0to59 sscounter(clk, reset, sena, s1,s2);
    counter_0to1 pmcounter(clk, reset, pmena, {hh,mm,ss}, pm);


    //驱动使能信号
    assign sena=ena;
    assign mena=ena & ({s2,s1}=={4'd5,4'd9});   //xx:59时mm进位
    assign hena=ena & ({m2,m1}=={4'd5,4'd9}) & ({s2,s1}=={4'd5,4'd9});    //xx:59:59时hh进位
    assign pmena=ena;

endmodule


//实现pm信号, 其实就是一个监测器.
module counter_0to1(
    input clk, reset,
    input ena,
    input [23:0]signal,//要监测的信号. 本次监测:当信号从0001_0001变为0001_0010时跳变.
    output reg out
);
    //reg [7:0]signal_prev;//通过打拍储存监测信号上个周期的值

    always @(posedge clk) begin

        if(reset)
            out<=0;
        else if(ena)begin
            //if((signal==8'b00010010)&(signal_prev==8'b00010001))
            if(signal==24'b0001_0001_0101_1001_0101_1001)//11:59:59
                out<=~out;  
        end  
        //signal_prev<=signal;//打拍   
    end
endmodule
//另一个思路是边缘捕获: 利用打拍创建一个信号的D触发器, 监测信号(hh)从11变为12时, 捕获信号. 这样做(即counter_0to1)会导致监测比hh跳变的那个周期慢一个周期.
//事实上, d触发器的d和q总是相差一个周期. 所谓modelsim中在tb中写"在时钟上沿阻塞赋值(#10 in=1;)"后, d和q会同步变化(因为阻塞赋值`程序层面`优先级比非阻塞赋值的右值读取高). 但是实际上这是不可综合的: 硬件层面上, d触发器的信号稳定需要一定时间, 而所有电路里clk信号是老大! 如果在clk上沿一瞬间给d触发器阻塞赋值信号, d触发器此时根本没稳定, 读出来的也是不可用数据呀! 写tb正确的做法是在时钟下沿给in赋值, 或者上沿过后一小段时间(hlsbit的网站波形图就是这样,类似#10.001)
//知道上述问题后, 自然可以明白: 要想让pm随hh变化的那个同周期也变化, 读取hh的变化是会慢一个周期, 应该读取"使hh将要变化的因素", 也就是"11:59:59". 不过如果不做题的话, 实际应用中,慢一个周期其实也可以接受. 

//mm和ss计数器(mod60)
module bcdcounter_0to59 (
	input clk,
	input reset,
	input enable,
	output reg [3:0] q1,q2
);
    always @(posedge clk) 
        begin
            if(reset)//重置
                {q1,q2}<=8'b0;
            else if(enable)begin
                if(q1==4'd9)begin//进位
                   if(q2==4'd5)begin//59 to 00
                        q1<=4'd0;
                        q2<=4'd0;
                   end else begin//39 to 40
                        q1<=0;
                        q2<=q2+1;
                   end
                end else//不进位
                    q1<=q1+1; 
            end   
        end
endmodule

//hh计数器(mod12)
module bcdcounter_1to12 (
	input clk,
	input reset,
	input enable,
	output reg [3:0] h1,h2
);
    always @(posedge clk) 
        begin
            if(reset)begin
                {h2,h1}<={4'd1,4'd2};//重置为12
            end
            else if(enable)begin
                if({h2,h1}=={4'd1,4'd2})begin
                    {h2,h1}<={4'd0,4'd1};//12to1
                end else if(h1==4'd9)begin//09to10
                    {h2,h1}<={4'd1,4'd0};
                end else
                    h1<=h1+1;
            end
        end
endmodule