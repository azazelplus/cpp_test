
#include "./led/bsp_led.h"   
#include "delay.h"		//这个led需要用我的delay模块.


 /**
  * @brief  初始化控制LED的IO
  * @param  无
  * @retval 无
  */
void LED_GPIO_Config(void)
{		
		/*定义一个GPIO_InitTypeDef类型的结构体*/
		GPIO_InitTypeDef GPIO_InitStructure;

		/*开启LED相关的GPIO外设时钟*/
		RCC_APB2PeriphClockCmd( LED1_GPIO_CLK | LED2_GPIO_CLK | LED3_GPIO_CLK, ENABLE);
	

		/*设置引脚模式为通用推挽输出*/
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   

		/*设置引脚速率为50MHz */   
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 

	
  #if RED_ENA	
		/*********************************初始化RED*****************************/
	
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = LED1_GPIO_PIN;
		/*调用库函数，初始化GPIO*/
		GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);	
		/************************************************************************/	
  #endif


	#if GREEN_ENA	
		/*********************************初始化GREEN*****************************/
	
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = LED2_GPIO_PIN;

		/*调用库函数，初始化GPIO*/
		GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);
		/************************************************************************/
  #endif


	#if BLUE_ENA		
		/*********************************初始化BLUE*****************************/		
		/*选择要控制的GPIO引脚*/
		GPIO_InitStructure.GPIO_Pin = LED3_GPIO_PIN;

		/*调用库函数，初始化GPIOF*/
		GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStructure);
		/************************************************************************/
	#endif	
		
		
		/* 关闭所有led灯	*/
		GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN);
		
		/* 关闭所有led灯	*/
		GPIO_SetBits(LED2_GPIO_PORT, LED2_GPIO_PIN);	 
    
    /* 关闭所有led灯	*/
		GPIO_SetBits(LED3_GPIO_PORT, LED3_GPIO_PIN);
}




void RED_SPARKLE(void){
		/*****************red闪烁******************************/
		int i=5;
		while(i--){
		GPIO_ResetBits(LED1_GPIO_PORT, LED1_GPIO_PIN);				Delay(0x05FFFF);
		GPIO_SetBits(LED1_GPIO_PORT, LED1_GPIO_PIN);					Delay(0x05FFFF);
		}
		/*****************red闪烁******************************/
}


void GREEN_SPARKLE(void){
		/*****************GREEN闪烁******************************/
		int i=5;
		while(i--){
		GPIO_ResetBits(LED2_GPIO_PORT, GPIO_Pin_0);				Delay(0x05FFFF);
		GPIO_SetBits(LED2_GPIO_PORT, GPIO_Pin_0);					Delay(0x05FFFF);
		}
		/*****************GREEN闪烁******************************/
}

void BLUE_SPARKLE(void){
		/*****************BLUE闪烁******************************/
		int i=5;
		while(i--){
		GPIO_ResetBits(LED3_GPIO_PORT, GPIO_Pin_1);				Delay(0x05FFFF);
		GPIO_SetBits(LED3_GPIO_PORT, GPIO_Pin_1);					Delay(0x05FFFF);
		}
		/*****************BLUE闪烁******************************/
	}


















/*********************************************END OF FILE**********************/
