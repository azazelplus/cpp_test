
//verilator不提供自动仿真功能, 需要cpp代码驱动, 这就是对每个.v模块文件的sim.main.cpp的作用. 它被称为wrapper.

#include "verilated.h"	//同上
#include <stdio.h>	
#include <stdlib.h>
#include <assert.h>
#include "verilated_vcd_c.h"	//如果需要波形生成, 引入VCD波形头文件.

// NVBoard 相关头文件
#include <nvboard.h>	
// 自动生成的绑定代码



#if 1
	#include "Vdual_control_switch.h"
#endif

#define USE_TRACE 0	//是否启用波形跟踪功能. 如果启用, Makefile中也要启用-Wl,--trace选项.
#define USE_NVBOARD 1	//是否启用NVBoard功能.

#define ONLY_ASSIGN 1	//模块仅包含组合逻辑, 不包含时序逻辑


#define TOP_MODULE_NAME "dual_control_switch"	//顶层模块名.





//全局指针top.
static Vdual_control_switch* top = nullptr;

/*********************常用函数**********************/
void nvboard_bind_all_pins(Vdual_control_switch* top);  //绑定引脚的声明.

// single cycle simulation.
static void single_cycle() {
#if !ONLY_ASSIGN
    top->clk = 0; 
	top->eval();
    top->clk = 1; 
	top->eval();
#else
	// 如果是组合逻辑, 只需要调用一次 eval() 即可.
	top->eval();
#endif
}

//rst函数. 持续复位状态n个周期,然后解除.
static void reset(int n) {
#if !ONLY_ASSIGN
    top->rst = 1;
    while (n-- > 0) single_cycle();
    top->rst = 0;
#else
	// 不需要复位
#endif
}
/*********************常用函数**********************/



int main(int argc, char** argv){
	
	/*************初始化verilator环境.***********************/

	//创建`仿真上下文类`对象 contextp. `VerilatedContext`这个类是verilog提供的仿真环境管理器, 其成员和方法能实现多个管理功能之类的. 对只有一个顶层模块的项目不需要这个.
	VerilatedContext* contextp = new VerilatedContext;	

	contextp->commandArgs(argc, argv);	//解析命令行参数

	//设置完环境管理器contextp后, 在其基础上创建模块对象top.
	top = new Vdual_control_switch{contextp};		//创建Vour类(verilator的顶层模块) top, 绑定它到仿真上下文.  此处模块类名是 V{模块名}，其中 {模块名} 是你 Verilog 顶层模块（module）的名

	/*
	对于跑单个顶层的模块完全可以简化成:
	Verilated::commandArgs(argc, argv);
	top = new Vdual_control_switch;
	*/
	/*************初始化verilator环境.***********************/

	
	#if USE_TRACE
		contextp->traceEverOn(true);	//启用波形跟踪

		//创建VCD波形记录对象tfp(trace file pointer)
		VerilatedVcdC* tfp = new VerilatedVcdC;

		top->trace(tfp, 99);	//指定信号跟踪深度.深度为1则只记录顶层模块的信号变化. 深度更高则记录子模块的变量的变化. 常用默认值99, 意为记录所有有意义信号.
		tfp->open("wave.vcd");	//打开波形文件"wave.vcd",并准备将数据写入.在仿真结束后就可以使用工具(如 GTKWave)查看这个文件, 得到波形
	#endif

	#if USE_NVBOARD
		/***************************************************/
		nvboard_bind_all_pins(top);
		nvboard_init();
		/***************************************************/
	#endif

	reset(10);

	//循环执行仿真. 
	while(!Verilated::gotFinish()){
		#if USE_NVBOARD
			nvboard_update();                 // NVBoard 刷新
			single_cycle();                   // 单周期执行
		#endif
	}

	//仿真结束清理.
	delete top;
	delete contextp;

	#if USE_TRACE
		delete tfp;
	#endif

	#if USE_NVBOARD
		nvboard_quit();
	#endif

	return 0;
}


