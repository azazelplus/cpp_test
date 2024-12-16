在该`modelsim测试文件夹`中, 初始的源文件为:
	* 待测模块`adder_4bit.v`
	* 为了测试该模块而为其编写的testbench模块`adder_4bit_tb`
其他文件(夹)为在该文件夹内运行modelsim产生的工程文件.

测试方法:
	1.进入modelsim 创建新的仿真工程. file->new->project->定位到包含两个.v文件(一个模块一个tb模块)的文件夹
	2.在新的仿真工程里添加.v文件并编译它们. 在`project窗口`编译两个.v文件.
	3.选择`library窗口`(或者直接start simulation)->work->adder_4bit_tb.v(tb文件为顶层模块, 测试要测试顶层模块.)->simulate,开始一个simulate.
	在`sim窗口`选择adder_4bit_tb->uut(uut是tb代码中实例化adder_4bit的moduel名), 右键它->add wave
	可以得到`波形图窗口`. 如果想让时间开始运行, 在`sim`窗口上方一大坨按钮中寻找run lenth并设置为想要的步长间隔,然后点击右侧的`run`,开始逐步长模拟.
	若要停止, 在上方`simulate`中选择`end simulate`即可.
	
本次加法器测试结果:
	每个通道看起来有两条线,这是因为它们是多位的,四个折线如果不全是0或1, 叠加起来就看起来有两条线了.
	每个通道中间的数字即为该通道信号值的大小,可以用选定radix表示.