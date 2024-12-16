


module tb_dff;
    //声明信号
    reg d;
    reg clk;
    wire q;
    
    //实例化
    dff uut(
        .d(d),
        .clk(clk),
        .q(q)
    );
    
    //generate clock
    always begin
    	#5 clk =~clk;//每5时间单位反转时钟, 产生周期为10单位的时钟.
    end
    
    //initialize input
    initial begin
        clk=0;
        d=0;
        
        //观察一段时间
        #10 d=1;//10单位后, d设为1
        #10 d=0;
		#10 d=1;
		#10 d=0;
        
        #50 $finish;//仿真结束
    end  
endmodule



module dff(
    input d,clk, 
    output reg q
);
    always @(posedge clk)begin
        q<=d;
    end
endmodule