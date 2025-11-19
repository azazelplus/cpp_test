
//This is an example similar to the Example C++ Execution, but using SystemC. by azazel


#include "Vour.h"
//#include "verilated.h" //为何不需要这个头文件了?

using namespace std; //使用标准命名空间
using namespace sc_core;//使用SystemC的核心命名空间

//main函数的名字必须是sc_main, 因为这是SystemC的入口点.
int sc_main(int argc, char** argv){

    Verilated::commandArgs(argc, argv);//传入命令行参数
    sc_clock clk{"clk", 10, SC_NS, 0.5, 3, SC_NS, true};//创建名为`clk`的时钟信号, `10`ns周期(SC_NS表示纳秒), 50%占空比, 初始延迟`3`ns, `true`表示正边沿触发.
    Vour* top = new Vour{"top"};//创建一个顶层模块实例`top`, 名称为`top`.使用初始化参数列表:{top}.
    top->clk(clk);//将top的时钟`top->clk`连接到创建的时钟信号`clk`
    while (!Verilated::gotFinish())
    {
        sc_start(1, SC_NS);//SystemC仿真, 每次仿真1NS. 
    }
    delete top;//删除顶层模块实例
    return 0;//返回0表示正常结束

}











