#include <Arduino.h>
#include "Motor.h"

/* esp32的PWM模块成为LEDC模块（LED Controller）, 有十六路通道, 分为两个group, 分别编号chan 0~7. 但是由于映射到实现硬件timer上只有四个timer, 如果使用相同的timer(比如ledc: 0和ledc: 1), 那么就会冲突, 需要避开. 或者让它们输出相同的波形.
 * LEDC Chan to Group/Channel/Timer Mapping
** ledc: 0  => Group: 0, Channel: 0, Timer: 0
** ledc: 1  => Group: 0, Channel: 1, Timer: 0
** ledc: 2  => Group: 0, Channel: 2, Timer: 1
** ledc: 3  => Group: 0, Channel: 3, Timer: 1
** ledc: 4  => Group: 0, Channel: 4, Timer: 2
** ledc: 5  => Group: 0, Channel: 5, Timer: 2
** ledc: 6  => Group: 0, Channel: 6, Timer: 3
** ledc: 7  => Group: 0, Channel: 7, Timer: 3
** ledc: 8  => Group: 1, Channel: 0, Timer: 0
** ledc: 9  => Group: 1, Channel: 1, Timer: 0
** ledc: 10 => Group: 1, Channel: 2, Timer: 1
** ledc: 11 => Group: 1, Channel: 3, Timer: 1
** ledc: 12 => Group: 1, Channel: 4, Timer: 2
** ledc: 13 => Group: 1, Channel: 5, Timer: 2
** ledc: 14 => Group: 1, Channel: 6, Timer: 3
** ledc: 15 => Group: 1, Channel: 7, Timer: 3
*/

// 绑定的IO
const int Motor_PWM_PinA = 5;//输出PWM电压信号, 用来控制左轮电机的速度
const int Motor_PWM_PinB = 4;
const int Motor_INA1 = 19;//输出高/低电平, 用来描述左轮是正转还是反转
const int Motor_INA2 = 18;//和Motor_INA1取反. 两引脚形成有方向的电流, 控制左轮电机方向.
const int Motor_INB1 = 16;
const int Motor_INB2 = 17;

// PWM的通道，共16个(0-15)，分为高低速两组，
// 高速通道(0-7): 80MHz时钟，低速通道(8-15): 1MHz时钟
// 0-15都可以设置，只要不重复即可，参考上面的列表
// 如果有定时器的使用，千万要避开!!!
const int Motor_channel_PWMA = 2;
const int Motor_channel_PWMB = 3;

// PWM频率，直接设置即可
int Motor_freq_PWM = 1000;

// PWM分辨率，取值为 0-20 之间，这里填写为10，那么后面的ledcWrite()里面填写的pwm值就在 0 - 2的10次方 之间 也就是 0-1024
int Motor_resolution_PWM = 10;

void Motor_Init(void)
{
    pinMode(Motor_INA1, OUTPUT);
    pinMode(Motor_INA2, OUTPUT);
    pinMode(Motor_INB1, OUTPUT);
    pinMode(Motor_INB2, OUTPUT);

    //ledcSetup()函数用来初始化PWM通道.
    //参数:
    // 1. PWM通道编号(0-15)
    // 2. PWM频率(Hz)
    // 3. PWM分辨率位数(0-20). 设置后, 之后生成PWM信号时, ledcWrite(chan, duty)函数的duty参数在0~2^n-1之间.
    ledcSetup(Motor_channel_PWMA, Motor_freq_PWM, Motor_resolution_PWM); // 设置通道
    ledcSetup(Motor_channel_PWMB, Motor_freq_PWM, Motor_resolution_PWM); // 设置通道


    //PWM绑定到具体IO口. 将 LEDC 通道绑定到指定 IO 口上以实现输出
    ledcAttachPin(Motor_PWM_PinA, Motor_channel_PWMA);                  
    ledcAttachPin(Motor_PWM_PinB, Motor_channel_PWMB);
}

void PWM_SetDuty(uint16_t DutyA, uint16_t DutyB)
{
    ledcWrite(Motor_channel_PWMA, DutyA);
    ledcWrite(Motor_channel_PWMB, DutyB);
}

// 电机的控制程序，分别是左右两个轮子的占空比（0-1024）
// 该函数接受两个参数: Cnt_L 和 Cnt_R，分别表示左轮和右轮的占空比。比如Motor_Control(512, -300);表示：左轮正转，速度约 50%, 右轮反转，速度约 30%, 实现小车原地右转.
// 函数做的事: 让Motor_INA1和Motor_INA2引脚输出高电平(当轮子占空比为正);
// 然后使用初始化好的两个PWM通道, 调用ledcWrite()来使得Motor_channel_PWMA, Motor_channel_PWMB引脚输出PWM波形, 以控制电机的速度.
void Motor_Control(int Cnt_L, int Cnt_R)
{
    if (Cnt_L >= 0) // 左轮正向转
    {
        //digitalWrite()函数是arduino框架里控制引脚输出电平.
        //参数1: io引脚号
        //参数2: 输出电平, HIGH(0x1)或LOW(0x0)
        digitalWrite(Motor_INA1, HIGH);
        digitalWrite(Motor_INA2, LOW);
        ledcWrite(Motor_channel_PWMA, Cnt_L);
    }
    else // 左轮反向转
    {
        digitalWrite(Motor_INA1, LOW);
        digitalWrite(Motor_INA2, HIGH);
        ledcWrite(Motor_channel_PWMA, -Cnt_L);
    }

    if (Cnt_R >= 0) // 右轮正向转
    {
        digitalWrite(Motor_INB1, HIGH);
        digitalWrite(Motor_INB2, LOW);
        ledcWrite(Motor_channel_PWMB, Cnt_R);
    }
    else // 右轮反向转
    {
        digitalWrite(Motor_INB1, LOW);
        digitalWrite(Motor_INB2, HIGH);
        ledcWrite(Motor_channel_PWMB, -Cnt_R);
    }
}
