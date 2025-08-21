



#include "Vour.h"
#include "verilated.h"

int main(int argc, char** argv){

    VerilatedContext* contextp = new VerilatedContext;//创建环境
    contextp->commandArgs(argc, argv);//传入命令行参数

    Vour* top = new Vour{contextp};//创建顶层模块实例. contextp是构造函数的参数.
    while(!contextp->gotFinish()){
        top->eval();//仿真
        //不需要+1时间步, 因为这是个简单的单次行为级仿真
    }
    delete top;//删除顶层模块实例
    delete contextp;//删除环境
    return 0;    
}











