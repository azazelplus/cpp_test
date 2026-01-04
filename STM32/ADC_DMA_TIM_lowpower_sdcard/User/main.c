//2025.6.22.azazel
 //这是来自USART1接发项目文件夹的基础上进行的adc单通道中断读取项目的基础上的阈值检测.
 //的基础上的USART1_ADC_DMA.
 //的基础上的USART1_ADC_DMA_TIMled.
 //的基础上的rtc休眠
 
 #define USE_BEEP 1

#define USE_THRES 1	//开启阈值检测

#define USE_UART 1



#include "stm32f10x.h"
#include "bsp_usart.h"
#include "bsp_adc.h"
#include "bsp_tim.h"
#include "bsp_led.h"
#include "bsp_rtc.h"
#include "delay.h"

#if USE_BEEP
#include "bsp_beep.h"
#endif


#include "ff.h"
#include "./sdio/bsp_sdio_sdcard.h"

#include "logger.h"


extern __IO uint16_t ADC_ConvertedValue;
extern uint8_t led_timer_count;

int worktime = 3;
int sleeptime = 999;

//局部变量.用来保存转换计算后的电压值
float ADC_ConvertedValueLocal;
#define THRESHOLD_VOLTAGE 0.05f



#if 0
/*************************************************************************/
FATFS fs;													/* FatFs文件系统对象 */
FIL fnew;													/* 文件对象 */
FRESULT res_state;                /* 文件操作结果 */
UINT fnum;            					  /* 文件成功读写数量 */
BYTE ReadBuffer[1024]={0};        /* 读缓冲区 */
float WriteBuffer[] =              /* 写缓冲区*/
{1,2,3}; 
extern  SD_CardInfo SDCardInfo;//?????????
// 数据记录器状态
typedef enum {
    LOGGER_UNINIT = 0,
    LOGGER_READY,
    LOGGER_WRITING,
    LOGGER_ERROR
} LoggerState;
// 数据记录器初始化
LoggerState logger_init(void);
// 记录ADC数据
void log_adc_value(float adc_value);
// 关闭记录器
void logger_close(void);
/*************************************************************************/
#endif



int main(void)
{	
	
	
	
		

	
	/****************************除了RTC外的初始化***************************************/
	#if USE_UART
  USART_Config();  /*初始化USART 配置模式为 115200 8-N-1，中断接收*/
	ADCx_Init();	//初始化adc
	LED_GPIO_Config();	//初始化LED
	BasicTIM_Init();		//初始化TIM
	#endif
	/*************************************************************************/
	
	
	/****************************RTC初始化*********************************************/	
	RTC_NVIC_Config();	// RTC 中断通道配置
	#if USE_UART
  printf("\r\n\r\n即将运行RTC_Config\r\n"); RTC_Configuration();	printf("\r\n\r\n RTC_Config运行完毕\r\n");// RTC 外设初始化（LSE、分频器、Alarm 中断使能）
	#endif
	/*************************************************************************/

/*************************************************************************/
    // 初始化数据记录器
    if (logger_init() != LOGGER_READY) {
			#if USE_UART
        printf("Logger init failed! Continue without logging...\r\n");
			#endif
    }
/*************************************************************************/
	
  while(1)
	{	 
			
		rtc_alarm_triggered = 0; // 清标志		
		RTC_SetAlarmInSeconds(worktime);	//设定工作闹钟: 工作时间为5秒
		
		
		/******************************工作循环*******************************************/
		while(!rtc_alarm_triggered){
			//电压值=寄存器值/4096*3.3
			ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3; 
			
			// 记录电压值
			log_adc_value(ADC_ConvertedValueLocal);
			
			
			
			/*****************************阈值检测逻辑********************************************/
			#if USE_THRES
			if (ADC_ConvertedValueLocal >= THRESHOLD_VOLTAGE)//如果超过阈限
			{
					// 将 LED 置低，点亮 LED
					GPIO_ResetBits(GPIOB, GPIO_Pin_0);
					// 重置计时器为 x（ x * 中断触发频率(0.1s) = x/10s）
					led_timer_count = 5; 
			#if USE_BEEP				
								BEEP( BEEP_ON ); 			  // 响
								Delay(0x0FFFFF);	
								BEEP( BEEP_OFF );		  // 不响
								Delay(0x0FFFFF);
			#endif
			}
			#endif	
			/*****************************阈值检测逻辑********************************************/			
			} 
		/******************************工作循环*******************************************/


		
		
		/* —— 工作闹钟触发后进入这里 —— */
		rtc_alarm_triggered = 0; // 清标志
		GPIO_SetBits(GPIOB, GPIO_Pin_0);
		/* —— 设定休眠闹钟. 休眠时间为sleeptime秒 —— */
		RTC_SetAlarmInSeconds(sleeptime);
		

		

		/* —— 进入 Stop 模式，等待 RTC 中断自动唤醒 —— */
		PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFI);

		/* —— 唤醒后要重配置系统时钟 —— */
		
		SystemInit();
		/*除了RTC外的初始化******************************************************************/
		USART_Config();  /*初始化USART 配置模式为 115200 8-N-1，中断接收*/
		ADCx_Init();	//初始化adc
		LED_GPIO_Config();	//初始化LED
		BasicTIM_Init();		//初始化TIM
		
		//亮灯表示休眠结束
		/*****************red闪烁******************************/
		int i=5;
		while(i--){
		GPIO_ResetBits(GPIOB, GPIO_Pin_5);				Delay(0x05FFFF);
		GPIO_SetBits(GPIOB, GPIO_Pin_5);					Delay(0x05FFFF);
		}
		/*****************red闪烁******************************/
	}	
}


/*********************************************END OF FILE**********************/


