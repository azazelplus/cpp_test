
//verilator不提供自动仿真功能, 需要cpp代码驱动, 这就是对每个.v模块文件的sim.main.cpp的作用. 它被称为wrapper.
#if 0
	#define TOP_NAME Vdual_control_switch  //定义顶层模块类名

	// 第1步: 定义一个辅助宏, 它的作用是把传进来的任何东西变成字符串.
	#define STRINGIFY(x) #x
	// 第2步: 定义第二个宏, 它调用第一个宏.
	// 这一步是关键! 它会先"展开"参数, 然后再把它传递给 STRINGIFY
	#define TO_STRING(x) STRINGIFY(x)



	#include TO_STRING(TOP_NAME.h)	//verilator自动生成的头文件, 其名为`V[top_module_name].h`.  其中[top_module_name]是.v代码的顶层模块名.  运行verilator --cc witch.v后自动生成, 在obj_dir目录下.
#endif


#include Vdual_control_switch.h	


#include "verilated.h"	//同上
#include <stdio.h>	
#include <stdlib.h>
#include <assert.h>
#include "verilated_vcd_c.h"	//如果需要波形生成, 引入VCD波形头文件.


#define USE_NVBOARD 1

#if USE_NVBOARD
// NVBoard 相关头文件
#include <nvboard.h>	
// 自动生成的绑定代码
#include "auto_bind.cpp"
#endif

int main(int argc, char** argv){
	
	//初始化verilator环境.
      VerilatedContext* contextp = new VerilatedContext;	//创建`仿真上下文类`对象 contextp. `VerilatedContext`这个类是verilog提供的仿真环境管理器, 其成员和方法能实现多个管理功能之类的.
      contextp->commandArgs(argc, argv);	//解析命令行参数      
	  contextp->traceEverOn(true);	//启用波形跟踪
	  //设置完环境管理器contextp后, 在其基础上创建模块对象top.
	  Vtop* top = new Vtop{contextp};		//创建Vour类(verilator的顶层模块) top, 绑定它到仿真上下文.  此处模块类名是 V{模块名}，其中 {模块名} 是你 Verilog 顶层模块（module）的名
	  
	  
	//创建VCD波形记录对象tfp(trace file pointer)
	VerilatedVcdC* tfp = new VerilatedVcdC;
	top->trace(tfp, 99);	//指定信号跟踪深度.深度为1则只记录顶层模块的信号变化. 深度更高则记录子模块的变量的变化. 常用默认值99, 意为记录所有有意义信号.
	tfp->open("wave.vcd");	//打开波形文件"wave.vcd",并准备将数据写入.在仿真结束后就可以使用工具(如 GTKWave)查看这个文件, 得到波形.
	
	#if USE_NVBOARD
	/***************************************************/
	nvboard_bind_all_pins(&dut);
	nvboard_init();
	/***************************************************/
	#endif

	  
	//循环执行仿真. 
	for(int i=0;i<100;++i){		//运行一百个时钟周期, verilator默认将dump的时间步长设为1ps. 随机测试我们的XOR门
		//生成随机输入信号.
		int a = rand() & 1;	//rand()返回一个大整数, 如`00110000000111001`. 和1进行&运算时只取最低位, 由于0&1=0,1&1=1, 而最低位随机, 所以`rand()&1`可以随即给出0或1.
		int b = rand() & 1;
		top->a = a;	//传递给verilog模块
		top->b = b;
		top->eval();	//run sim
		
		tfp->dump(i);	//波形记录对象tfp记录时间步i的信号
		
		printf("a = %d, b = %d, f = %d \n", a, b, top->f);
		assert(top->f == (a^b));	//assertion检查XOR计算是否正确.
		#if USE_NVBOARD
		nvboard_update();
		#endif
	}
	//仿真结束清理.
	delete top;
	delete contextp;
	delete tfp;

	#if USE_NVBOARD
	nvboard_quit();
	#endif

	return 0;
}


