#include "bsp_rtc.h"

#include "stm32f10x.h"

#include <stdio.h>

#include "stm32f10x_exti.h"
#include "delay.h"

//rtc闹钟触发标志. 复习:__IO是stm一个宏, ==volatile, 表达这个变量可能被硬件中断或改变, 不允许优化和缓存偷懒, 时刻监视.
__IO uint8_t rtc_alarm_triggered = 0;



//rtc外设配置中断, 即在NVIC中注册RTC中断通道
void RTC_NVIC_Config(void)
{
	

    NVIC_InitTypeDef NVIC_InitStructure;	//NVIC配置结构体


	  EXTI_InitTypeDef EXTI_InitStructure;	//EXIT配置结构体
	    
	
	
    EXTI_ClearITPendingBit(EXTI_Line17);// 清除 EXTI Line17 的中断挂起标志
	  // 连接 EXTI Line17 到 RTC Alarm
	  EXTI_InitStructure.EXTI_Line = EXTI_Line17;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
	
	
	
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);	//设置 中断优先级分组策略在 不使用 HAL、完全裸机风格（比如你现在的库） 中，这个配置 是必须的，否则后面 NVIC_Init() 设置的优先级可能会被忽略或不生效。
	
		//注意这不是 RTC_IRQn 而是 RTCAlarm_IRQn）
    NVIC_InitStructure.NVIC_IRQChannel = RTCAlarm_IRQn;
	//享有最高优先级.
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


//初始化rtc外设.
void RTC_Configuration(void)
{
		//打开 PWR 和 BKP 外设时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
	
		//允许访问后备寄存器（BKP 寄存器）
    PWR_BackupAccessCmd(ENABLE);
	
		//复位RTC和BKP寄存器的备份域, 好习惯.
    BKP_DeInit();
		
		//启用LSE
    RCC_LSEConfig(RCC_LSE_ON);
	
		//等待LSE稳定(起振)
    while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);
	
		//设置RTC的时钟源为LSE
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
	
		//使能RTC时钟
    RCC_RTCCLKCmd(ENABLE);

	  // 等待 RTC 寄存器同步完成（必须）
    // 因为 APB 时钟快、RTC 慢，需要同步后才允许操作 RTC
    RTC_WaitForSynchro();
		
		//等待上一条命令完成（RTC 是低速外设，需等待确认）
    RTC_WaitForLastTask();

		//使能 RTC 的闹钟中断（Alarm 中断）.RTC有三种中断来源, 用三个寄存器控制.
    RTC_ITConfig(RTC_IT_ALR, ENABLE);
		
		//再次等待上条写命令完成
    RTC_WaitForLastTask();


		//设置 RTC 的分频器，使其以 1Hz 计数
    // LSE = 32768 Hz → 32767 分频后每秒进 1（1 Hz）
    RTC_SetPrescaler(32767);
    RTC_WaitForLastTask();
}


//配置一个seconds秒后触发的闹钟.
void RTC_SetAlarmInSeconds(uint32_t seconds)
{
		//RTC_GetCounter()库函数读取当前RTC计数器的值, 即UNIX时间戳.
    uint32_t current_time = RTC_GetCounter();
	
		//RTC_SetAlarm()函数对RTC外设*设置闹钟*(请参见RTC外设产生中断的三种方式, alarm就是其中一种). 届时,RTC会产生一个中断信号.
    RTC_SetAlarm(current_time + seconds);
	
		//等待上面函数的寄存器写操作完成.
    RTC_WaitForLastTask();
}



//RTC的中断服务函数. 在it.c中转发这个函数, 实现解耦的效果.
void BSP_RTCAlarm_IRQHandler(void)
{
    if (RTC_GetITStatus(RTC_IT_ALR) != RESET)
    {
				//清除中断标志
        RTC_ClearITPendingBit(RTC_IT_ALR);
			
				//清除外部中断线
        RTC_WaitForLastTask();
			
				//设置闹钟触发变量为1

        rtc_alarm_triggered = 1;
			
		/*****************red闪烁******************************/
		//GPIO_ResetBits(GPIOB, GPIO_Pin_5);				Delay(0x0FFFFF);
		//GPIO_SetBits(GPIOB, GPIO_Pin_5);					Delay(0x0FFFFF);
		//GPIO_ResetBits(GPIOB, GPIO_Pin_5);					Delay(0x0FFFFF);
		//GPIO_SetBits(GPIOB, GPIO_Pin_5);					Delay(0x0FFFFF);
		/*****************red闪烁******************************/
						
				EXTI_ClearITPendingBit(EXTI_Line17);
    }
}

//RTC的第二种中断函数, 触发时发送gpio信号.
void BSP_RTCAlarm_IRQHandler_2(void)
{
    if (RTC_GetITStatus(RTC_IT_ALR) != RESET)
    {
				//清除中断标志
        RTC_ClearITPendingBit(RTC_IT_ALR);
			
				//清除外部中断线
        RTC_WaitForLastTask();
			
			  // 初始化 GPIOC 引脚13 为推挽输出模式，输出高电平

        RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);  // 使能 GPIOC 时钟

        GPIO_InitTypeDef GPIO_InitStructure;
        GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
        GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
        GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
        GPIO_Init(GPIOC, &GPIO_InitStructure);

        GPIO_SetBits(GPIOC, GPIO_Pin_13);  // 输出高电平
			
			
						
				EXTI_ClearITPendingBit(EXTI_Line17);
    }
}
