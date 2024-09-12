#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


#define MAX_DATA 512
#define MAX_ROWS 100

struct Address{
	int id;
	int set;
	char name[MAX_DATA];
	char email[MAX_DATA];
};

struct Database{
	struct Address rows[MAX_ROWS];//这是一个叫做rows的邮箱地址结构体数组.
};

//一个Connection结构体中包含两个成员变量: 一个FILE结构体指针, 一个Database结构体指针
struct Connection{
	FILE *file;	//FILE是一个内置的结构体类型, C语言文件管理实现方式. 查阅`C语言文件管理`..
	struct Database *db;
};


//die()的作用是在遇到错误时终止程序并输出相关错误信息.
void die(const char *message)
{
	if(errno)//errno是一个全局变量, 来自头文件errno.h, 记录最近一次系统调用/库函数的错误代码. 当系统调用/库函数失败(即发生了系统级别的错误, 如打开文件失败.)时, errno会被设置为一个非零值, 表示对应的错误类型.
		 perror(message);//perror()函数是标准库stdio.h中的一个函数, 用来根据当前的errno输出错误信息. 比如当message为"File open error", 且此时errno变量表示文件不存在. 则perror输出:"File open error: No such file or directory!"
	else
	{
		printf("Error: %s\n", message);//如果errno为0, 说明当前没有系统调用有关的错误. 此时只输出错误消息message.
	}

	exit(1);//表示程序异常退出.
}	


//这是一个Adress类的方法. 简单的打印而已.此处我们用按指传递. 当然也可以按值传递, 只需要把*去掉, ->改为.即可. 但是大多情况下, 如果函数是只读类型的, 传入一个结构体或类的时候按指传递更高效灵活.(当然也有一定危险性, 一定要保证这个函数是只读.)
void Adress_print(struct Adress *addr)
{
	printf("%d %s %s\n", addr->id, addr->name, addr->email);
}



void Database_load(struct Connection *conn)
{
	int rc
}
