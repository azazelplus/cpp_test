/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2014        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/
//disc.c它分了三个独立设备实现, 实现了以下几个函数.
//DSTATUS disk_status(设备编号pdrv): 返回设备状态
//disk_initialize(pdrv) — 初始化设备
//disk_read(pdrv, buff, sector, count) — 读扇区
//disk_write(pdrv, buff, sector, count) — 写扇区
//disk_ioctl(pdrv, cmd, buff) — 控制命令
//disc.c是 FatFs 文件系统用来与实际硬件设备（比如 SD 卡）打交道的底层接口适配层（glue layer）。
//FatFs 不直接操作硬件，而是通过这些统一的接口间接访问你自己的驱动代码。
//如果你要用SD卡,准备好`bsp_sd_sdcard.c`和`bsp_sd_sdcard.h`, 在这里include bsp_sd_sdcard.h, 然后用其中的状态检测函数啊写函数啊读函数啊控制函数啊填充到discio.c中.

#include "diskio.h"		/* FatFs lower layer API */
#include "ff.h"
#include "./sdio/bsp_sdio_sdcard.h"

/* Definitions of physical drive number for each drive */
#define ATA			    0     // 预留SD卡使用
#define SPI_FLASH		1     // 外部SPI Flash
#define USB		2	/* Example: Map USB MSD to physical drive 2 */



//我们使用这三个输出0的函数, 加上三种卡每一个都加一句stat=result; 实现跳过disk_status检测部分, 假设设备都正常.
#define SKIP_DISK_STATUS 1

#if SKIP_DISK_STATUS
DSTATUS ATA_disk_status(){
	return 0;
}

DSTATUS MMC_disk_status(){
	return 0;
}

DSTATUS USB_disk_status(){
	return 0;
}
#endif


//跳过不用的设备
#define SKIP_ATA AND_USB 1


extern SD_CardInfo SDCardInfo;//这是bsp_sdio_sdcard.c提供的一个用于存储卡信息的结构体全局变量.






/*-----------------------------------------------------------------------*/
/* 1. Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/
//宏定义数据类型: DSTATUS=BYTE=unsigned char.
//这个框架提示你使用一个自己的ATA/MMC/USB_disk_status()函数将状态信息给变量result, 然后将result调整后给stat输出作为检测结果. 
//SD卡用...哦我们跳过了
DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;
	int result;

	switch (pdrv) {
	case ATA :
		result = ATA_disk_status();

		// translate the reslut code here

/*********************************************/
		#if SKIP_disk_status
		stat=result;
		#endif
/*********************************************/

		return stat;

	case SPI_FLASH :
		result = MMC_disk_status();

		// translate the reslut code here
/*********************************************/
		#if SKIP_disk_status
		stat=result;
		#endif
/*********************************************/
		return stat;

	case USB :
		result = USB_disk_status();

		// translate the reslut code here

/*********************************************/
		#if SKIP_disk_status
		stat=result;
		#endif
/*********************************************/
	
		return stat;
	}
	return STA_NOINIT;//兜底错误
}



/*-----------------------------------------------------------------------*/
/* 2. Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/
//SD卡用一个函数SD_Init()实现
DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;

	switch (pdrv) {
	case ATA :
/*************************azazel********************/
		if(SD_Init() != SD_OK)
			stat = STA_NOINIT;//初始化失败
		else
			stat &= ~STA_NOINIT;//正常
		return stat;
/*********************************************/


	case SPI_FLASH :
		break;
	case USB :
		break;
	}
	return STA_NOINIT;//兜底错误
}



/*-----------------------------------------------------------------------*/
/* 3. Read Sector(s).读取扇区内容到指定存储区                                                    */
/*-----------------------------------------------------------------------*/
//SD卡用两个函数实现: SD_ReadMultiBlocks;紧跟着SD_WaitReadOperation
DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT status = RES_PARERR;//默认错误: status为RES_PARERR(参数错误)
	SD_Error sd_state;
	switch (pdrv) {
		case ATA:	/* SD CARD */
		//SDCardInfo.CardBlockSize: SD卡的块大小, 为512. 
		//SD_ReadMultiBlocks()参数列表分别为:读取存放的内存地址; 要读取的地址; 块大小; 要读取的块数.
		//它只是发出命令+配置DMA/SDIO，不会阻塞。
		SD_ReadMultiBlocks(buff, sector*SDCardInfo.CardBlockSize, SDCardInfo.CardBlockSize, count);	
		//等待读写完成
		sd_state = SD_WaitReadOperation();
		while(SD_GetStatus() != SD_TRANSFER_OK);//等待传输完成(其实是没必要的.)
		if(sd_state == SD_OK)
			status = RES_OK;
		else
			status = RES_ERROR;
			break;
    
		case SPI_FLASH:
      /* 扇区偏移2MB，外部Flash文件系统空间放在SPI Flash后面6MB空间 */
      //sector+=512;      
      //SPI_FLASH_BufferRead(buff, sector <<12, count<<12);  
      //status = RES_OK;
		break;
    
		default:
			status = RES_PARERR;
	}
	return status;
}



/*-----------------------------------------------------------------------*/
/* 4.Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/
//SD卡用
#if _USE_WRITE
DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address in LBA */
	UINT count			/* Number of sectors to write */
)
{
	//uint32_t write_addr; 
	DRESULT status = RES_PARERR;//默认SD卡操作状态为: RES_PARERR(参数错误)
	if (!count) {
		return RES_PARERR;		/* Check parameter */
	}

	
	SD_Error sd_state;
	switch (pdrv) {
		case ATA:	/* SD CARD */ 
//此处buff需要强制类型转换, 直接`SD_WriteMultiBlocks(buff, ...`会警告. 因为你把只读数据buff传给了要求可写的函数参数(SD_WriteMultiBlocks的第一个形参)。
//传入disk_write的形参buff类型是const BYTE *, 而SD_WriteMultiBlocks()要求传入的第一个形参是BYTE *.
//可以把int传给要求const int的函数: 这只是把“可以改的数据”交给一个“承诺不会改”的函数.(C 会在函数内部生成一个新的局部const变量来接收)
//不可以把const int传给要求int的函数: 把一个“只读”的东西，交给了一个“可能会修改”的函数。这是不安全的。
//(BYTE *)buff是告诉编译器: 我愿意冒险把这只读数据传给一个可能会改它的函数.
		SD_WriteMultiBlocks((BYTE *)buff, sector*SDCardInfo.CardBlockSize, SDCardInfo.CardBlockSize, count);	
		//等待读写完成
		sd_state = SD_WaitWriteOperation();
		while(SD_GetStatus() != SD_TRANSFER_OK);//等待传输完成(其实是没必要的.)
		if(sd_state == SD_OK)
			status = RES_OK;
		else
			status = RES_ERROR;
			break;			

		case SPI_FLASH:
      /* 扇区偏移2MB，外部Flash文件系统空间放在SPI Flash后面6MB空间 */
//			sector+=512;
//      write_addr = sector<<12;    
//      SPI_FLASH_SectorErase(write_addr);
//      SPI_FLASH_BufferWrite((u8 *)buff,write_addr,count<<12);
//      status = RES_OK;
		break;
    
		default:
			status = RES_PARERR;
	}
	return status;
}
#endif


/*-----------------------------------------------------------------------*/
/* 5.Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

#if _USE_IOCTL
DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT status = RES_PARERR;//默认错误. 
	
	switch (pdrv) {
		case ATA:	/* SD CARD */
			
		//对传进来的命令码cmd分类处理:
			switch (cmd) {
				/* 获取扇区数量: 总容量÷扇区大小 */
			case GET_SECTOR_COUNT:
				*(DWORD * )buff = SDCardInfo.CardCapacity/SDCardInfo.CardBlockSize;		
			break;
			/* 扇区大小  */
			case GET_SECTOR_SIZE :
				*(WORD * )buff = SDCardInfo.CardBlockSize;
			break;
			/* 同时擦除扇区个数. 一般SD卡是一个一个扇区擦除的, 置1即可 */
			case GET_BLOCK_SIZE :
				*(DWORD * )buff = 1;
			break;        
		}
      status = RES_OK;
			break;
    
		case SPI_FLASH:
			
//			switch (cmd) {
//        /* 扇区数量：1536*4096/1024/1024=6(MB) */
//        case GET_SECTOR_COUNT:
//          *(DWORD * )buff = 1536;		
//        break;
//        /* 扇区大小  */
//        case GET_SECTOR_SIZE :
//          *(WORD * )buff = 4096;
//        break;
//        /* 同时擦除扇区个数 */
//        case GET_BLOCK_SIZE :
//          *(DWORD * )buff = 1;
//        break;        
//      }
//      status = RES_OK;
		
		break;
    
		default:
			status = RES_PARERR;
	}
	return status;
}
#endif

//__weak是Keil MDK (armcc)和ARM GCC（比如 STM32CubeIDE）的编译器内建的扩展关键字（attribute）. 表示这个函数是弱符号（Weak Symbol）
//如果程序中没有其他地方定义这个函数, 那就用这个定义. 否则就无视这个定义! get_fattime()这个函数可能很容易在其他地方重复声明, 我们不希望影响到那些地方.
__weak DWORD get_fattime(void) {
	/* 返回当前时间戳 */
	return	  ((DWORD)(2015 - 1980) << 25)	/* Year 2015 */
			| ((DWORD)1 << 21)				/* Month 1 */
			| ((DWORD)1 << 16)				/* Mday 1 */
			| ((DWORD)0 << 11)				/* Hour 0 */
			| ((DWORD)0 << 5)				  /* Min 0 */
			| ((DWORD)0 >> 1);				/* Sec 0 */
}

