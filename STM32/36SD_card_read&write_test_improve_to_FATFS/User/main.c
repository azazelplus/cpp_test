/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   SDIO sd������ʵ�飨�����ļ�ϵͳ��
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��  STM32 F103-ָ���� ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
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

FATFS fs;													/* FatFs�ļ�ϵͳ���� */
FIL fnew;													/* �ļ����� */
FRESULT res_state;                /* �ļ�������� */
UINT fnum;            					  /* �ļ��ɹ���д���� */
BYTE ReadBuffer[1024]={0};        /* �������� */
BYTE WriteBuffer[] =              /* д������*/
"summer is ending...\r\n"; 

extern  SD_CardInfo SDCardInfo;//?????????






int main(void)
{
	/* ��ʼ��LED */
	LED_GPIO_Config();	
	LED_BLUE;
	
	/* ��ʼ�����Դ��ڣ�һ��Ϊ����1 */
	USART_Config();	
  printf("\r\n\r\n\r\n****** ����һ��SD���ļ�ϵͳʵ�� ******\r\n");

	
	//���γ��Թ���. ����ɹ�(res_state == FR_NO_FILESYSTEM), ˵���Ѿ����ļ�ϵͳ, ����Ҫ��ʽ��
	//���ⲿSPI Flash�����ļ�ϵͳ���ļ�ϵͳ����ʱ���SPI�豸��ʼ��.
	//��ʼ������������������
	//f_mount()->find_volume()->disk_initialize->SPI_FLASH_Init()
	res_state = f_mount(&fs,"0:",1);//�ڶ������������������,��ʽ���ַ���"x:" ,��Χ��ffconf.h���`_VOLUMES`. ����������`1`��ʾ���̹���
	
	
	
/*----------------------- 1.��ʽ������ -----------------*/  
	
	if(res_state == FR_NO_FILESYSTEM)/* ������ι���ʧ��, ���ش�����FR_NO_FILESYSTEMû���ļ�ϵͳ, ���᳢�Ը�ʽ��+���¹��� */
	{
		printf(">>>FLASH��û���ļ�ϵͳ���������и�ʽ��...\r\n");
		res_state=f_mkfs("0:",0,0);/* ��ʽ��.��һ���������̷�.�ڶ�������: �ָ����ѡ`0`, FDISK����. �����������Ǵش�С, 0��ʾ�Զ�����*/					
		
		if(res_state == FR_OK)//������ι�����Ϊû���ļ�ϵͳʧ��->��ʽ���ɹ�
		{
			printf(">>>FLASH�ѳɹ���ʽ���ļ�ϵͳ��\r\n");
		
			
			/*****************���¹��ع���: ж��f_mount(NULL,"0:",1);+����f_mount(&fs,"0:",1);******************************/
      /*  f_mkfs() ��ʽ����ɺ�FatFs���ڲ��ṹ��FATFS���Ͷ���fs����ʧЧ����Ҫ���¹��ز�����ȷ������ȡ��ԭ���Ĺ��� */
			res_state = f_mount(NULL,"0:",1);	//NULL��ʾж��. 	
      /* ���¹���	*/			
			res_state = f_mount(&fs,"0:",1);
			/**************************************************************************************************************/
			
		}
		else//������ι�����Ϊû���ļ�ϵͳʧ��->��ʽ��ʧ��
		{
			LED_RED;//red led��. ����.
			printf(">>>��ʽ��ʧ�ܡ�\r\n");
			while(1);//������ѭ��
		}
	}
  else if(res_state!=FR_OK)//������ι���ʧ��, ���Ƿ��ش����벻��FR_NO_FILESYSTEMû���ļ�ϵͳ��������δ֪ԭ��
  {
    printf("�����ⲿFlash�����ļ�ϵͳʧ�ܡ�(%d)\r\n",res_state);
    printf("��������ԭ��SPI Flash��ʼ�����ɹ���\r\n");
	printf("������ SPI����д����FLASH ���̲��ԣ�����������ڸ�����f_mount�����if���ǰ��ʱ�����һ�� res_state = FR_NO_FILESYSTEM; ������ֱ��ִ�и�ʽ������\r\n");
		while(1);
  }
  else//���res_state==FR_OK, ���ι��ؾͳɹ���
  {
    printf(">>>�ļ�ϵͳ���سɹ������Խ��ж�д����\r\n");
  }
  
	
	
	
	
/*----------------------- 2.�ļ�ϵͳ���ԣ�д���� -------------------*/
	/* ���ļ���ÿ�ζ����½�����ʽ�򿪣�����Ϊ��д */
	printf("\r\n>>>Ready to conduct file write test... ******\r\n");	
	res_state = f_open(&fnew, "0:test.txt",FA_CREATE_ALWAYS | FA_WRITE );//�򿪹������̷�`0`���ļ�`FatFs_test.txt`. ��д��ʽ: ����ļ�������, �½��ļ�. ����ļ�����, **ɾ�����ļ�����.**
	if ( res_state == FR_OK )
	{
		printf(">>>fopen(write mode) create/open `0:FatFs_test.txt`: SUCCESS, now ���ļ�д�����ݡ�\r\n");
    /* ��ָ���洢������д�뵽�ļ��� */
		res_state=f_write(&fnew,WriteBuffer,sizeof(WriteBuffer),&fnum);
    if(res_state==FR_OK)
    {
      printf(">>>f_write(): SUCCESS, д���ֽ� data��%d\n",fnum);
      printf(">>>���ļ�д�������Ϊ��\r\n%s\r\n",WriteBuffer);
    }
    else
    {
      printf("!!! f_write(): FAILED: (%d)\r\n",res_state);
    }    
		/* ���ٶ�д���ر��ļ� */
    f_close(&fnew);
	}
	else
	{	
		LED_RED;
		printf("!!! fopen(): FAILED: (%d)\r\n",res_state);
	}
	
	
	
	
	
/*------------------- 3.�ļ�ϵͳ���ԣ������� --------------------------*/
	printf(">>>Ready to conduct file read test... ******\r\n");
	res_state = f_open(&fnew, "0:test.txt",FA_OPEN_EXISTING | FA_READ);// �򿪹������̷�`0`���ļ�`FatFs_test.txt`. ��ֻ����ʽ(������Ҳ�����)
	if(res_state == FR_OK)
	{
		LED_GREEN;
		printf(">>>���ļ��ɹ���\r\n");
		res_state = f_read(&fnew, ReadBuffer, sizeof(ReadBuffer), &fnum); //
    if(res_state==FR_OK)
    {
      printf(">>>�ļ���ȡ�ɹ�,�����ֽ����ݣ�%d\r\n",fnum);
      printf(">>>��ȡ�õ��ļ�����Ϊ��\r\n%s \r\n", ReadBuffer);	
    }
    else
    {
      printf("!!! �ļ���ȡʧ�ܣ�(%d)\n",res_state);
    }		
	}
	else
	{
		LED_RED;
		printf(">>>!!! Opening the file: FAILED: (%d)\r\n",res_state);
	}
	/* ���ٶ�д���ر��ļ� */
	f_close(&fnew);	
  
	/* ����ʹ���ļ�ϵͳ��ȡ�������ļ�ϵͳ */
	f_mount(NULL,"0:",1);
  
  /* ������ɣ�ͣ�� */
	while(1)
	{
	}
}

/*********************************************END OF FILE**********************/
