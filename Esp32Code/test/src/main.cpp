#include <Arduino.h>

// 定义外部中断的Mode. 自己改123试一试
// 0: 无中断，读取Touch值
// 1：Touch中断，执行 TouchEvent()
// 2: 外部IO的中断
#define EXT_ISR_MODE 2


//Serial：是 Arduino 系统中用于串口通信的对象，ESP32 中也有。
void TouchEvent()
{
    Serial.printf("Touch Event.\r\n");
}

void PinIntEvent()
{
    Serial.printf("PinInt Event.\r\n");
}

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(115200);


// T0：ESP32 自带的触摸通道，对应GPIO4
// TouchEvent：当触摸值低于阈值时要调用的回调函数
// 40：触摸阈值，读到的值 <40 时认为“被触摸”    
#if 1 == EXT_ISR_MODE
    // Pin: T0(GPIO4), 函数指针:TouchEvent, 阈值: 40
    touchAttachInterrupt(T0, TouchEvent, 40);

#elif 2 == EXT_ISR_MODE
//设置外部中断要先初始化引脚. pinMode()函数可以用来初始化引脚(引脚名, 模式)
    pinMode(4, INPUT_PULLUP);
// attachInterrupt()函数功能：给指定引脚绑定一个中断服务函数（ISR），当引脚电平发生指定变化时，CPU 会暂停当前任务，跳到这个函数里执行。参数列表是 [监听引脚; 回调函数名; 触发条件]
    attachInterrupt(4, PinIntEvent, CHANGE);
#endif
}

void loop()
{
    // put your main code here, to run repeatedly:

#if 0 == EXT_ISR_MODE
    Serial.printf("touch:%d\r\n", touchRead(T0));
#endif

//这个delay函数的实现依靠FreeRTOS的系统节拍(默认1kHz), 此时该函数延迟x ms.
    delay(200);
}