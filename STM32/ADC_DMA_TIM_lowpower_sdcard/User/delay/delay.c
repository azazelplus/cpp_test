
#include "delay.h"
#include "stm32f10x.h"


void Delay(__IO uint32_t nCount)
{
  for(; nCount != 0; nCount--);
} 


