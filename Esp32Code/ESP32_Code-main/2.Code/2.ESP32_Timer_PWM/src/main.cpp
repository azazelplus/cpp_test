#include <Arduino.h>
#include "../lib/Motor/Motor.h"

#define PMW_EN 1

int interruptCounter = 0;
//hw_timer_t 是一个结构体类型，表示硬件定时器的句柄
hw_timer_t *timer = NULL;

//	函数名称：onTimer()
//	函数功能：中断服务的功能，它必须是一个返回void（空）且没有输入参数的函数
//  为使编译器将代码分配到IRAM内，中断处理程序应该具有 IRAM_ATTR 属性
//  https://docs.espressif.com/projects/esp-idf/zh_CN/release-v4.3/esp32/api-reference/storage/spi_flash_concurrency.html


//中断函数: 对我们的自定义全局变量打印并++; 逢5重置为1
//IRAM_ATTR即宏定义等效的__attribute__((section(".iram1"))), 这是一个GCC编译器的内建关键字, 告诉编译器把这个函数（或变量）放到指定的段中. 这个函数就会被链接器安排放入 .iram1 代码段（即 IRAM 中）而不是默认的 .text 段（一般是 SPI flash 里）。
void IRAM_ATTR TimerEvent()
{
    Serial.println(interruptCounter++);
    if (interruptCounter > 5)
    {
        interruptCounter = 1;
    }
}
void setup()
{
    Serial.begin(115200);//初始化串口

#if PMW_EN

    Motor_Init();

#endif

    //	函数名称：timerBegin()
    //	函数功能：Timer初始化，分别有三个参数
    //	函数输入：1. 定时器编号（0到3，对应全部4个硬件定时器）
    //			 2. 预分频器数值（ESP32计数器基频为80M，80分频单位是微秒）, 即1个计数器周期为1us
    //			 3. 计数器向上（true）或向下（false）计数的标志
    //	函数返回：一个指向 hw_timer_t 结构类型的指针
    timer = timerBegin(0, 80, true);

    //	函数名称：timerAttachInterrupt()
    //	函数功能：绑定定时器的中断处理函数，分别有三个参数
    //	函数输入：1. 指向已初始化定时器的指针（本例子：timer）
    //			 2. 中断服务函数的函数指针
    //			 3. 表示中断触发类型是边沿（true）还是电平（false）的标志
    //	函数返回：无
    timerAttachInterrupt(timer, &TimerEvent, true);

    //	函数名称：timerAlarmWrite()
    //	函数功能：指定触发定时器中断的计数器值，分别有三个参数
    //	函数输入：1. 指向已初始化定时器的指针（本例子：timer）
    //			 2. 第二个参数是触发中断的计数器值（1000000 us -> 1s）
    //			 3. 定时器在产生中断时是否重新加载的标志
    //	函数返回：无
    timerAlarmWrite(timer, 1000000, true);
    timerAlarmEnable(timer); //	使能定时器
}
void loop()
{

#if PMW_EN

    // PWM_SetDuty()函数是我们自己在motor.cpp写的. 其实就是调用两次函数ledcWrite(chan, duty). 
    // ledcWrite(chan, duty)函数:
    // 用来设置指定通道的PWM占空比.
    // 两个参数: 
    // chan是通道编号(0~15). ESP32 有最多 16 个 PWM 通道（编号 0～15），叫做 LEDC 通道. 编
    // duty是占空比值(8位PWM的话就是0~1023). 设置512就是50%占空比(高低电平各一半时间)

    PWM_SetDuty(200 * interruptCounter, 200 * interruptCounter);

#endif
}
