

#include "Vlight.h"  // 这里包含生成的Verilator头文件
#include "verilated.h"
#include <iostream>
#include <bitset>  // 提供cout二进制的转换打印


#include <nvboard.h>


using namespace std;

//Vlight* top;    
//轻量化实现top模块的实例化.
//tip: 如果.v文件中顶层模块是`light`，那么生成的C++类名通常是`Vlight`, top只是个对象名, 无需更改.
//对象top是verilator跟据light.v的顶层模块module light创建的, 其成员变量映射自.v文件中的所有信号.
//verilator还会对这个类自动生成一些常见成员函数供仿真和测试, 如: 
//.eval()用于执行单次仿真评估, 
//.final()在仿真结束时调用, 清理和释放资源, 
//.trace()启用波形跟踪功能,
//.dump()将当前仿真状态写入波形文件,
//.信号名()获取或设置clk信号的值.


static TOP_NAME dut;  //TOP_NAME是一个在verilator生成的某个cpp文件中定义好的一个宏, 在nvboard参与编译的cpp文件里, 定义为V[顶部模块名]. 是一个类名. 这里生成一个实例叫做dut.

void nvboard_bind_all_pins(Vlight* top);  //绑定引脚的声明.


// single cycle simulation
static void single_cycle(){
    dut.clk = 0;   //set clk 0
    dut.eval();    //evaluate the model
    dut.clk=1;
    dut.eval();
}


//rst函数. 持续复位状态n个周期,然后解除.
static void reset(int n){
    dut.rst = 1;
    while (n-->0) single_cycle();   //while(n-->0)是一种简写, 意思是for(; n==0 ;n--)
    dut.rst = 0;
}


//
int main(int argc, char** argv){
    //nvboard init.
    nvboard_bind_all_pins(&dut);  //绑定引脚
    nvboard_init();                     //初始化

    //初始化
    //Verilated::commandArgs(argc, argv);
    //top = new Vlight;

    //前10个cycle复位, 然后恢复
    reset(10);

    //进入循环仿真
    while(1){
        nvboard_update();   //更新nvboard状态
        single_cycle();

        //每个周期后, 以16位二进制格式, 打印LED的状态.
        //cout<<"LED: " << bitset<16>(top->led) << endl;   
    }

    //free(top);
    //return 0;
}

