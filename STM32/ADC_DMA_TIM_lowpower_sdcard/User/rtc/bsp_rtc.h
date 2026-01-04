

#ifndef __BSP_RTC_H
#define __BSP_RTC_H

#include "stm32f10x.h"

extern __IO uint8_t rtc_alarm_triggered;

void RTC_NVIC_Config(void);
void RTC_Configuration(void);
void RTC_SetAlarmInSeconds(uint32_t seconds);
void BSP_RTCAlarm_IRQHandler(void);
void BSP_RTCAlarm_IRQHandler_2(void);

#endif
















