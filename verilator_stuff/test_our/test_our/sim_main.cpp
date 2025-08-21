  #include "Vour.h"
  #include "verilated.h"
  int main(int argc, char** argv) {
	  //初始化verilator环境.
      VerilatedContext* contextp = new VerilatedContext;	//创建`仿真上下文类`对象 contextp. `VerilatedContext`这个类是verilog提供的仿真环境管理器, 其成员和方法能实现多个管理功能之类的.
      contextp->commandArgs(argc, argv);	//解析命令行参数
      Vour* top = new Vour{contextp};		//创建顶层模块类(verilator的顶层模块) top, 绑定它到仿真上下文. 此处模块类名是 V{模块名}，其中 {模块名} 是你 Verilog 顶层模块（module）的名
	  
      while (!contextp->gotFinish()) {	//gotFinish()方法的作用: 如果.v代码里有$finish语句, 返回true(表示仿真应该终止), 否则返回false. 如果你的.v代码里没有仿真部分, 只有你设计的模块, gotFinish()就没用咯. 自己编写循环仿真吧.
			top->eval(); 
		  }
      delete top;
      delete contextp;
      return 0;
  }
