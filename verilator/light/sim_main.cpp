

#include "Vlight.h"  // 这里包含生成的Verilator头文件
#include "verilated.h"
#include <iostream>
#include <bitset>  // 提供cout二进制的转换打印

using namespace std;

//轻量化实现top模块的实例化.
Vlight* top;    
//tip: 如果.v文件中顶层模块是`light`，那么生成的C++类名通常是`Vlight`, top只是个对象名, 无需更改.

// single cycle simulation
void single_cycle(){
    top->clk = 0;   //set clk 0
    top->eval();    //evaluate the model
    top->clk=1;
    top->eval();
}


//rst函数. 持续复位状态n个周期,然后解除.
void rst(int n){
    top->rst = 1;
    while (n-->0) single_cycle();   //while(n-->0)是一种简写, 意思是for(; n==0 ;n--)
    top->rst = 0;
}


//
int main(int argc, char** argv){
    //初始化
    Verilated::commandArgs(argc, argv);
    top = new Vlight;

    //前10个cycle复位, 然后恢复
    rst(10);

    //进入循环仿真
    while(!Verilated::gotFinish()){
        single_cycle();

        //每个周期后, 以16位二进制格式, 打印LED的状态.
        cout<<"LED: " << bitset<16>(top->led) << endl;
        
    }


    free(top);
    return 0;
}

