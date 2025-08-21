

module our(clk);
	input clk;	// Clock is required to get initial activation
	
	always @(posedge clk) begin
		$display("hello world");
		$finish;
	end
endmodule


改进gui，加入滤波。

使用外部物理定时器(TPL5110定时器开关模块接收单片机请求)方案,
修改程序:  
单片机rtc定时休眠取消，按照RTC中断发送定时器请求.

选型一个寄存触发器作为电子开关。(选为CD4013，配置为tff）
选型轻量级mos管2N7002接受TFF。


















