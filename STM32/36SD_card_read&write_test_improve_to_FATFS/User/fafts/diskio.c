/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2014        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/
//disc.c���������������豸ʵ��, ʵ�������¼�������.
//DSTATUS disk_status(�豸���pdrv): �����豸״̬
//disk_initialize(pdrv) �� ��ʼ���豸
//disk_read(pdrv, buff, sector, count) �� ������
//disk_write(pdrv, buff, sector, count) �� д����
//disk_ioctl(pdrv, cmd, buff) �� ��������
//disc.c�� FatFs �ļ�ϵͳ������ʵ��Ӳ���豸������ SD �����򽻵��ĵײ�ӿ�����㣨glue layer����
//FatFs ��ֱ�Ӳ���Ӳ��������ͨ����Щͳһ�Ľӿڼ�ӷ������Լ����������롣
//�����Ҫ��SD��,׼����`bsp_sd_sdcard.c`��`bsp_sd_sdcard.h`, ������include bsp_sd_sdcard.h, Ȼ�������е�״̬��⺯����д�����������������ƺ�������䵽discio.c��.

#include "diskio.h"		/* FatFs lower layer API */
#include "ff.h"
#include "./sdio/bsp_sdio_sdcard.h"

/* Definitions of physical drive number for each drive */
#define ATA			    0     // Ԥ��SD��ʹ��
#define SPI_FLASH		1     // �ⲿSPI Flash
#define USB		2	/* Example: Map USB MSD to physical drive 2 */



//����ʹ�����������0�ĺ���, �������ֿ�ÿһ������һ��stat=result; ʵ������disk_status��ⲿ��, �����豸������.
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


//�������õ��豸
#define SKIP_ATA AND_USB 1


extern SD_CardInfo SDCardInfo;//����bsp_sdio_sdcard.c�ṩ��һ�����ڴ洢����Ϣ�Ľṹ��ȫ�ֱ���.






/*-----------------------------------------------------------------------*/
/* 1. Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/
//�궨����������: DSTATUS=BYTE=unsigned char.
//��������ʾ��ʹ��һ���Լ���ATA/MMC/USB_disk_status()������״̬��Ϣ������result, Ȼ��result�������stat�����Ϊ�����. 
//SD����...Ŷ����������
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
	return STA_NOINIT;//���״���
}



/*-----------------------------------------------------------------------*/
/* 2. Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/
//SD����һ������SD_Init()ʵ��
DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;

	switch (pdrv) {
	case ATA :
/*************************azazel********************/
		if(SD_Init() != SD_OK)
			stat = STA_NOINIT;//��ʼ��ʧ��
		else
			stat &= ~STA_NOINIT;//����
		return stat;
/*********************************************/


	case SPI_FLASH :
		break;
	case USB :
		break;
	}
	return STA_NOINIT;//���״���
}



/*-----------------------------------------------------------------------*/
/* 3. Read Sector(s).��ȡ�������ݵ�ָ���洢��                                                    */
/*-----------------------------------------------------------------------*/
//SD������������ʵ��: SD_ReadMultiBlocks;������SD_WaitReadOperation
DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT status = RES_PARERR;//Ĭ�ϴ���: statusΪRES_PARERR(��������)
	SD_Error sd_state;
	switch (pdrv) {
		case ATA:	/* SD CARD */
		//SDCardInfo.CardBlockSize: SD���Ŀ��С, Ϊ512. 
		//SD_ReadMultiBlocks()�����б�ֱ�Ϊ:��ȡ��ŵ��ڴ��ַ; Ҫ��ȡ�ĵ�ַ; ���С; Ҫ��ȡ�Ŀ���.
		//��ֻ�Ƿ�������+����DMA/SDIO������������
		SD_ReadMultiBlocks(buff, sector*SDCardInfo.CardBlockSize, SDCardInfo.CardBlockSize, count);	
		//�ȴ���д���
		sd_state = SD_WaitReadOperation();
		while(SD_GetStatus() != SD_TRANSFER_OK);//�ȴ��������(��ʵ��û��Ҫ��.)
		if(sd_state == SD_OK)
			status = RES_OK;
		else
			status = RES_ERROR;
			break;
    
		case SPI_FLASH:
      /* ����ƫ��2MB���ⲿFlash�ļ�ϵͳ�ռ����SPI Flash����6MB�ռ� */
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
//SD����
#if _USE_WRITE
DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address in LBA */
	UINT count			/* Number of sectors to write */
)
{
	//uint32_t write_addr; 
	DRESULT status = RES_PARERR;//Ĭ��SD������״̬Ϊ: RES_PARERR(��������)
	if (!count) {
		return RES_PARERR;		/* Check parameter */
	}

	
	SD_Error sd_state;
	switch (pdrv) {
		case ATA:	/* SD CARD */ 
//�˴�buff��Ҫǿ������ת��, ֱ��`SD_WriteMultiBlocks(buff, ...`�ᾯ��. ��Ϊ���ֻ������buff������Ҫ���д�ĺ�������(SD_WriteMultiBlocks�ĵ�һ���β�)��
//����disk_write���β�buff������const BYTE *, ��SD_WriteMultiBlocks()Ҫ����ĵ�һ���β���BYTE *.
//���԰�int����Ҫ��const int�ĺ���: ��ֻ�ǰѡ����Ըĵ����ݡ�����һ������ŵ����ġ��ĺ���.(C ���ں����ڲ�����һ���µľֲ�const����������)
//�����԰�const int����Ҫ��int�ĺ���: ��һ����ֻ�����Ķ�����������һ�������ܻ��޸ġ��ĺ��������ǲ���ȫ�ġ�
//(BYTE *)buff�Ǹ��߱�����: ��Ը��ð�հ���ֻ�����ݴ���һ�����ܻ�����ĺ���.
		SD_WriteMultiBlocks((BYTE *)buff, sector*SDCardInfo.CardBlockSize, SDCardInfo.CardBlockSize, count);	
		//�ȴ���д���
		sd_state = SD_WaitWriteOperation();
		while(SD_GetStatus() != SD_TRANSFER_OK);//�ȴ��������(��ʵ��û��Ҫ��.)
		if(sd_state == SD_OK)
			status = RES_OK;
		else
			status = RES_ERROR;
			break;			

		case SPI_FLASH:
      /* ����ƫ��2MB���ⲿFlash�ļ�ϵͳ�ռ����SPI Flash����6MB�ռ� */
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
	DRESULT status = RES_PARERR;//Ĭ�ϴ���. 
	
	switch (pdrv) {
		case ATA:	/* SD CARD */
			
		//�Դ�������������cmd���ദ��:
			switch (cmd) {
				/* ��ȡ��������: ��������������С */
			case GET_SECTOR_COUNT:
				*(DWORD * )buff = SDCardInfo.CardCapacity/SDCardInfo.CardBlockSize;		
			break;
			/* ������С  */
			case GET_SECTOR_SIZE :
				*(WORD * )buff = SDCardInfo.CardBlockSize;
			break;
			/* ͬʱ������������. һ��SD����һ��һ������������, ��1���� */
			case GET_BLOCK_SIZE :
				*(DWORD * )buff = 1;
			break;        
		}
      status = RES_OK;
			break;
    
		case SPI_FLASH:
			
//			switch (cmd) {
//        /* ����������1536*4096/1024/1024=6(MB) */
//        case GET_SECTOR_COUNT:
//          *(DWORD * )buff = 1536;		
//        break;
//        /* ������С  */
//        case GET_SECTOR_SIZE :
//          *(WORD * )buff = 4096;
//        break;
//        /* ͬʱ������������ */
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

//__weak��Keil MDK (armcc)��ARM GCC������ STM32CubeIDE���ı������ڽ�����չ�ؼ��֣�attribute��. ��ʾ��������������ţ�Weak Symbol��
//���������û�������ط������������, �Ǿ����������. ����������������! get_fattime()����������ܺ������������ط��ظ�����, ���ǲ�ϣ��Ӱ�쵽��Щ�ط�.
__weak DWORD get_fattime(void) {
	/* ���ص�ǰʱ��� */
	return	  ((DWORD)(2015 - 1980) << 25)	/* Year 2015 */
			| ((DWORD)1 << 21)				/* Month 1 */
			| ((DWORD)1 << 16)				/* Mday 1 */
			| ((DWORD)0 << 11)				/* Hour 0 */
			| ((DWORD)0 << 5)				  /* Min 0 */
			| ((DWORD)0 >> 1);				/* Sec 0 */
}

