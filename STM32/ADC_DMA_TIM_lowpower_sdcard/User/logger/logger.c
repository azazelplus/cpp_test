// data_logger.c
#include "logger.h"
#include "ff.h"
#include "stdio.h"
#include "stm32f10x.h"
#include "./sdio/bsp_sdio_sdcard.h"
#include "./sdio/sdio_test.h"
#include "./usart/bsp_usart.h"	
#include "./led/bsp_led.h"
#include <string.h>



#define LOG_FILE_NAME "0:adc_data.csv" // CSV格式便于电脑处理
#define BUFFER_SIZE 50                 // 缓冲区大小




//自定义的LOGGER状态机:    
/*
LOGGER_UNINIT = 0,
LOGGER_READY,
LOGGER_WRITING,
LOGGER_ERROR
*/
static LoggerState current_state = LOGGER_UNINIT;

//写缓冲区数组
float data_buffer[BUFFER_SIZE];
//
static uint16_t buffer_index = 0;




// 定义文件系统对象
FATFS fs;													/* FatFs文件系统对象 */
FIL log_file;													/* 文件对象 */
FRESULT res_state;                /* 文件操作结果 */
UINT fnum;            					  /* 文件成功读写数量 */
BYTE ReadBuffer[1024]={0};        /* 读缓冲区 */
float data_buffer[BUFFER_SIZE];   /* 写缓冲区*/







// 使用SysTick作为时间基准
uint32_t Get_Tick(void) {
    return SysTick->VAL;  // 获取SysTick当前值（递减计数器）
}



LoggerState logger_init(void) {
    FRESULT res;//File function return code
    
	
	
		printf("entered logger_init(void)  \r\n");

	
	// 挂载文件系统. 盘符为"0:".
    res = f_mount(&fs, "0:", 1);
	
		printf("f_mount conducted.\r\n");
	
	
    if (res != FR_OK) //挂载失败
		{
			if (res == FR_NO_FILESYSTEM) //初次挂载失败原因: no filesystem, 则进行格式化.
				{
            printf("No filesystem, formatting...\r\n");
            res = f_mkfs("0:", 0, 0);//调用格式化函数f_mkfs
            if (res != FR_OK) 
						{//格式化失败
                printf("Format failed: %d\r\n", res);
                return LOGGER_ERROR;
            }
            // 格式化成功, 重新挂载
            res = f_mount(&fs, "0:", 1);
            if (res != FR_OK) 
						{//重新挂载仍然失败
                printf("Remount after format failed: %d\r\n", res);
                return LOGGER_ERROR;
            }
        } else {//初次失败而且原因不是no filesystem
            printf("Mount failed: %d\r\n", res);
            return LOGGER_ERROR;
        }
    }

    
    // 打开文件（兼容old FatFs版本）
    res = f_open(&log_file, LOG_FILE_NAME, FA_WRITE | FA_OPEN_EXISTING);
    if (res == FR_OK) //打开文件成功
		{
        // 移动指针到文件末尾
        res = f_lseek(&log_file, f_size(&log_file));
        if (res != FR_OK) {
            printf("Seek to end failed: %d\r\n", res);
            f_close(&log_file);
            return LOGGER_ERROR;
        }
    } else if (res == FR_NO_FILE) 						// 打开文件失败, 原因是文件不存在，则创建新文件
				{
						res = f_open(&log_file, LOG_FILE_NAME, FA_CREATE_NEW | FA_WRITE);
						if (res != FR_OK) {//创建新文件失败
								printf("File create failed: %d\r\n", res);
								return LOGGER_ERROR;
						}
						
						// 打开成功. 写入CSV标题. UINIT=unsigned int
						UINT bytes_written;//保存实际写入字节数
						const char *header = "Timestamp,ADC_Value\n";//文件开头写个标题
						res = f_write(&log_file, 		//要写入的文件对象指针
													header, 			//数据缓冲区指针
													strlen(header),//要写入的字节数, 即strlen(your_data) 
													&bytes_written);//实际写入的字节数.(按引用传递). 因为C只有一个返回值, 这个按引用传递的变量其实就是又return一个值. 用户可以用这个值判断一些东西比如有没有写完整..但是其实如果真的确定之后也不需要它, 你可以在最后一个参数直接传一个NULL, 表示你不关心最终写入了多少字节.
						if (res != FR_OK) {//f_write()失败
								printf("Header write failed: %d\r\n", res);
								f_close(&log_file);
								return LOGGER_ERROR;
						}
						//写入结束
				} else//打开文件失败, 其他原因
				{		
						printf("File open failed: %d\r\n", res);
						return LOGGER_ERROR;
				}
    
		//至此写入成功
    buffer_index = 0;
    current_state = LOGGER_READY;//logger state状态改为"READY", 意味着可以写入
    printf("Data logger ready\r\n");
    return LOGGER_READY;
}



//接收一个adc_value, 将其写入缓冲区.  同时判断, 如果缓冲满了, 进行写入(一个BUFFER_SIZE大小的行, 而且每行都打印一次时间戳)并清空缓冲区.
void log_adc_value(float adc_value) {
    if (current_state != LOGGER_READY) return;	//缓冲区没有READY, 丢弃值.
    
    // 缓冲区READY时存储到缓冲区
    data_buffer[buffer_index++] = adc_value;
    
    // 判断此时缓冲区有没有满. 满时写入文件.
    if (buffer_index >= BUFFER_SIZE) {
        UINT bytes_written;//同上.
        char line[32];
        
        for (int i = 0; i < BUFFER_SIZE; i++) {
            // 生成带时间戳的数据行
            int len = sprintf(line, "%lu,%.4f\n", 
                             (unsigned long)Get_Tick(), 
                             data_buffer[i]);
            f_write(&log_file, line, len, &bytes_written);
        }
        
        buffer_index = 0; // 重置缓冲区
        f_sync(&log_file); // 确保数据写入物理设备
    }
}



void logger_close(void) {
    if (current_state != LOGGER_READY) return;
    
    // 写入缓冲区剩余数据
    if (buffer_index > 0) {
        UINT bytes_written;
        char line[32];
        
        for (int i = 0; i < buffer_index; i++) {
            int len = sprintf(line, "%lu,%.4f\n", 
                             (unsigned long)Get_Tick(), 
                             data_buffer[i]);
            f_write(&log_file, line, len, &bytes_written);
        }
        
        buffer_index = 0;
        f_sync(&log_file);
    }
    
    // 关闭文件
    f_close(&log_file);
    f_mount(NULL, "0:", 1); // 卸载文件系统
    current_state = LOGGER_UNINIT;
    printf("Logger closed\r\n");
}
