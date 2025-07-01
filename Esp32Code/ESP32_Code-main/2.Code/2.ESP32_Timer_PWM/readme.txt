

这个例程演示timer的使用以及PWM模块的使用.

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

PWM的作用:

| 应用        | 原理                     |
| --------- | ---------------------- |
| 控制 LED 亮度 | 改变电流平均值（占空比大就亮）        |
| 控制电机转速    | 控制供电时间（占空比大就快）         |
| 声音输出      | 调整方波频率/占空比模拟音频波形       |
| DAC 模拟输出  | PWM + 低通滤波器 → 模拟连续电压信号 |


此例程我们有一个motor模块, 输出不同大小的电压, 模拟驱动一个motor, 最终实现是一个典型的 双通道直流电机控制逻辑（H 桥控制）.具体拆解:


我们使能了ledc2,3两个PWM通道:
const int Motor_channel_PWMA = 2;
const int Motor_channel_PWMB = 3;

使用了6个IO口: GPIO5, GPIO6, GPIO19, GPIO18, GPIO17, GPIO16
const int Motor_PWM_PinA = 5;
const int Motor_PWM_PinB = 4;
const int Motor_INA1 = 19;
const int Motor_INA2 = 18;
const int Motor_INB1 = 16;
const int Motor_INB2 = 17;
它们的作用是:
| 引脚名                       | 作用                      | 对应函数                 |
| ------------------------- | ----------------------- | -------------------- |
| `Motor_PWM_PinA` (GPIO 5) | 电机 A 的 **PWM 信号输出**（调速） | `ledcAttachPin(...)` |
| `Motor_PWM_PinB` (GPIO 4) | 电机 B 的 **PWM 信号输出**（调速） | `ledcAttachPin(...)` |
| `Motor_INA1` (GPIO 19)    | 电机 A 方向控制 - 引脚 1       	| `digitalWrite()` 控制  |
| `Motor_INA2` (GPIO 18)    | 和INA1取反       				| `digitalWrite()` 控制  |
| `Motor_INB1` (GPIO 16)    | 电机 B 方向控制 - 引脚 1       	 | `digitalWrite()` 控制  |
| `Motor_INB2` (GPIO 17)    | 和INB1取反       				| `digitalWrite()` 控制  |



// void Motor_Control(int Cnt_L, int Cnt_R)是电机的控制程序，分别是左右两个轮子的占空比（0-1024）
// 该函数接受两个参数: Cnt_L 和 Cnt_R，分别表示左轮和右轮的占空比。比如Motor_Control(512, -300);表示：左轮正转，速度约 50%, 右轮反转，速度约 30%, 实现小车原地右转.
// 函数做的事: 让Motor_INA1和Motor_INA2引脚输出高电平(当轮子占空比为正);
// 然后使用初始化好的两个PWM通道, 调用ledcWrite()来使得Motor_channel_PWMA, Motor_channel_PWMB引脚输出PWM波形, 以控制电机的速度.









