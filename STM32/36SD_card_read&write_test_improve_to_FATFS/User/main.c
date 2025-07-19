/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   SDIO sd卡测试实验（不含文件系统）
  ******************************************************************************
  * @attention
  *
  * 实验平台:野火  STM32 F103-指南者 开发板 
  * 论坛    :http://www.firebbs.cn
  * 淘宝    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
#include "stm32f10x.h"
#include "./sdio/bsp_sdio_sdcard.h"
#include "./sdio/sdio_test.h"
#include "./usart/bsp_usart.h"	
#include "./led/bsp_led.h"
//#include "./key/bsp_key.h" 
#include "ff.h"

FATFS fs;													/* FatFs文件系统对象 */
FIL fnew;													/* 文件对象 */
FRESULT res_state;                /* 文件操作结果 */
UINT fnum;            					  /* 文件成功读写数量 */
BYTE ReadBuffer[1024]={0};        /* 读缓冲区 */
BYTE WriteBuffer[] =              /* 写缓冲区*/
"summer is ending...\r\n"; 

extern  SD_CardInfo SDCardInfo;//?????????






int main(void)
{
	/* 初始化LED */
	LED_GPIO_Config();	
	LED_BLUE;
	
	/* 初始化调试串口，一般为串口1 */
	USART_Config();	
  printf("\r\n\r\n\r\n****** 这是一个SD卡文件系统实验 ******\r\n");

	
	//初次尝试挂载. 如果成功(res_state == FR_NO_FILESYSTEM), 说明已经有文件系统, 不需要格式化
	//在外部SPI Flash挂载文件系统，文件系统挂载时会对SPI设备初始化.
	//初始化函数调用流程如下
	//f_mount()->find_volume()->disk_initialize->SPI_FLASH_Init()
	res_state = f_mount(&fs,"0:",1);//第二个参数是驱动器编号,格式是字符串"x:" ,范围是ffconf.h里的`_VOLUMES`. 第三个参数`1`表示立刻挂载
	
	
	
/*----------------------- 1.格式化测试 -----------------*/  
	
	if(res_state == FR_NO_FILESYSTEM)/* 如果初次挂载失败, 返回错误码FR_NO_FILESYSTEM没有文件系统, 那麽尝试格式化+重新挂载 */
	{
		printf(">>>FLASH还没有文件系统，即将进行格式化...\r\n");
		res_state=f_mkfs("0:",0,0);/* 格式化.第一个参数是盘符.第二个参数: 分割规则选`0`, FDISK规则. 第三个参数是簇大小, 0表示自动分配*/					
		
		if(res_state == FR_OK)//如果初次挂载因为没有文件系统失败->格式化成功
		{
			printf(">>>FLASH已成功格式化文件系统。\r\n");
		
			
			/*****************重新挂载过程: 卸载f_mount(NULL,"0:",1);+挂载f_mount(&fs,"0:",1);******************************/
      /*  f_mkfs() 格式化完成后，FatFs的内部结构（FATFS类型对象fs）已失效，需要重新挂载才能正确工作。取消原来的挂载 */
			res_state = f_mount(NULL,"0:",1);	//NULL表示卸载. 	
      /* 重新挂载	*/			
			res_state = f_mount(&fs,"0:",1);
			/**************************************************************************************************************/
			
		}
		else//如果初次挂载因为没有文件系统失败->格式化失败
		{
			LED_RED;//red led亮. 报错.
			printf(">>>格式化失败。\r\n");
			while(1);//进入死循环
		}
	}
  else if(res_state!=FR_OK)//如果初次挂载失败, 但是返回错误码不是FR_NO_FILESYSTEM没有文件系统而是其他未知原因
  {
    printf("！！外部Flash挂载文件系统失败。(%d)\r\n",res_state);
    printf("！！可能原因：SPI Flash初始化不成功。\r\n");
	printf("请下载 SPI—读写串行FLASH 例程测试，如果正常，在该例程f_mount语句下if语句前临时多添加一句 res_state = FR_NO_FILESYSTEM; 让重新直接执行格式化流程\r\n");
		while(1);
  }
  else//如果res_state==FR_OK, 初次挂载就成功了
  {
    printf(">>>文件系统挂载成功，可以进行读写测试\r\n");
  }
  
	
	
	
	
/*----------------------- 2.文件系统测试：写测试 -------------------*/
	/* 打开文件，每次都以新建的形式打开，属性为可写 */
	printf("\r\n>>>Ready to conduct file write test... ******\r\n");	
	res_state = f_open(&fnew, "0:test.txt",FA_CREATE_ALWAYS | FA_WRITE );//打开挂载在盘符`0`的文件`FatFs_test.txt`. 以写方式: 如果文件不存在, 新建文件. 如果文件存在, **删除旧文件内容.**
	if ( res_state == FR_OK )
	{
		printf(">>>fopen(write mode) create/open `0:FatFs_test.txt`: SUCCESS, now 向文件写入数据。\r\n");
    /* 将指定存储区内容写入到文件内 */
		res_state=f_write(&fnew,WriteBuffer,sizeof(WriteBuffer),&fnum);
    if(res_state==FR_OK)
    {
      printf(">>>f_write(): SUCCESS, 写入字节 data：%d\n",fnum);
      printf(">>>向文件写入的数据为：\r\n%s\r\n",WriteBuffer);
    }
    else
    {
      printf("!!! f_write(): FAILED: (%d)\r\n",res_state);
    }    
		/* 不再读写，关闭文件 */
    f_close(&fnew);
	}
	else
	{	
		LED_RED;
		printf("!!! fopen(): FAILED: (%d)\r\n",res_state);
	}
	
	
	
	
	
/*------------------- 3.文件系统测试：读测试 --------------------------*/
	printf(">>>Ready to conduct file read test... ******\r\n");
	res_state = f_open(&fnew, "0:test.txt",FA_OPEN_EXISTING | FA_READ);// 打开挂载在盘符`0`的文件`FatFs_test.txt`. 以只读方式(不创建也不清空)
	if(res_state == FR_OK)
	{
		LED_GREEN;
		printf(">>>打开文件成功。\r\n");
		res_state = f_read(&fnew, ReadBuffer, sizeof(ReadBuffer), &fnum); //
    if(res_state==FR_OK)
    {
      printf(">>>文件读取成功,读到字节数据：%d\r\n",fnum);
      printf(">>>读取得的文件数据为：\r\n%s \r\n", ReadBuffer);	
    }
    else
    {
      printf("!!! 文件读取失败：(%d)\n",res_state);
    }		
	}
	else
	{
		LED_RED;
		printf(">>>!!! Opening the file: FAILED: (%d)\r\n",res_state);
	}
	/* 不再读写，关闭文件 */
	f_close(&fnew);	
  
	/* 不再使用文件系统，取消挂载文件系统 */
	f_mount(NULL,"0:",1);
  
  /* 操作完成，停机 */
	while(1)
	{
	}
}

/*********************************************END OF FILE**********************/
