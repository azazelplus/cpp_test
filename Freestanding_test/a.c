#include <stdint.h>

void _start(){
  //向QEMU的串口地址的第一个8字节写一个"A". 注意到该模拟串口是8bit位宽的设备(只支持8bit的ASCII码).
  volatile uint8_t *p = (uint8_t *)(uintptr_t)0x10000000;
  *p = 'A';

  //向虚拟退出设备对应内存写一个0x5555. 该虚拟机是32位的, 
  volatile uint32_t *exit = (uint32_t *)(uintptr_t)0x100000;
  *exit = 0x5555; //对该地址写入魔法数字0x5555

  _start();//正常情况下, 不会执行到这一句. 因为上一条指令已经导致 QEMU 退出了。如果因为某种原因退出失败，这会导致程序无限递归，重新尝试退出。
}







