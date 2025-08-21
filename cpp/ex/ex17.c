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




//Connection结构体用于表示文件和数据库的连接. 它包含两个成员变量: 一个FILE结构体指针file, 一个Database结构体指针db
struct Connection{
	FILE *file;	//FILE是一个内置的结构体类型, C语言文件管理实现方式. 查阅`C语言文件管理`..
	struct Database *db;
};




//die()的作用是在遇到错误时终止程序并输出相关错误信息. 参数massage一般是你自己写,用于标记为啥要die. 你也可以直接塞个die()终结当前函数.
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
void Address_print(struct Address *addr)
{
	printf("%d %s %s\n", addr->id, addr->name, addr->email);
}



//这个函数负责将本地文件加载到Connection结构中. 接收一个Connection类. 
//这意味着我们需要先建立好Connection类,初始化好这个Connection类中的FILE指针(即初始化好指定哪个本地文件)和database指针(即初始化好指定哪个database类来存数据)
//size_t是无符号整数 数据类型. 类似unsigned. 它的定义在stdio.h中. 常用于与内存大小有关的地方.
void Database_load(struct Connection *conn)
{
	int rc = fread(conn->db, sizeof(struct Database), 1, conn->file);//rc即return code. 这条指令将文件指针file所指向的文w件内容到指针db里去, 它读取1个struct Database大小的块.	如果成功, fread函数的返回值rc即为1.
	
	if(rc != 1)
		die("将本地文件读进数据库时失败了.");
}



//声明一个返回值为Connection结构体指针的函数 Database_open, 它的作用是打开一个数据库文件, 然后在内存中分配空间存放.
//数据库文件指的是一个本地的文件, 这个文件储存了一个Database结构体的数据.当然它是一个二进制文件, 而不是人类可读的文本如123 123 joe example@gmail.com这样子. 
struct Connection *Database_open(const char *filename, char mode)
{
	struct Connection* conn = malloc(
					1 * sizeof(struct Connection)
					);
	if(!conn)
		die("分配Connectioin内存出错");


	conn->db = malloc(
			sizeof(struct Database)
			);
	if(!conn->db)
		die("分配Database内存出错");


	//创建模式. 创建一个新的数据库文件
	if(mode == 'c')
	{
		conn->file = fopen(filename, "w");//w模式下, fopen会清空原有文件, 如果存在的话.
	}
	else
	{
		conn->file = fopen(filename, "r+");	
	}
	if(!conn->file)
		die("打开文件失败");

	return conn;
}



//注意, 如果指针结构体的成员还有指针, 要从内到外一个个free.
void Database_close(struct Connection *conn)
{
	if(conn->file)
		fclose(conn->file);
	if(conn->db)
		free(conn->db);
	free(conn);
}


void Database_write(struct Connection* conn)
{
	rewind(conn->file);//把本地文件指针放到文件开头
	
	//把conn->file的内容写入conn->db中. 我们认为file中有1个struct Database结构体数据.
	int rc = fwrite(conn->db, sizeof(struct Database), 1, conn->file);
	if(rc != 1)
		die("把文件写入数据库内存失败.");

	rc = fflush(conn->file); //fflush一下确保安全.
	if(rc == -1)				//fflush返回-1表示刷新失败了
		die("fflush刷新失败了!");
}



//这是在创建新数据库时使用的函数, 它初始化数据库中所有记录.
void Database_create(struct Connection *conn)
{
	for(int i=0;i<MAX_ROWS;i++)//遍历数据库结构体中的每一个Address
	{
		//创建一个Address结构体, 初始化其成员变量id和set.
		struct Address addr = {.id = i, .set = 0};
		
		//将初始化好的Address结构体赋给数据库.
		conn->db->rows[i] = addr;	
	}
}




//这个函数设置数据库中第`id`个Address成员的名称啊电子邮件啊. 注意Address的set变量是用来检查是否已经被设置. 如果set==0, 
void Database_set(struct Connection* conn, int id, const char* name, const char* email)
{
	//取出第`id`个Address的地址.
	struct Address *addr = &conn->db->rows[id];
	if(addr->set)//如果set==1说明这个Address的内容已经被写过了, 此时防止误覆写(如果想要覆写需要先delete掉Address的id呀email呀然后把set重设置为0表示现在可以覆写.)
		die("这个Address已经写入内容了, 你需要先删除内容来覆写.");
	

	addr->set = 1;//说明这个Address已被修改,
	char* res = strncpy(addr->name, name, MAX_DATA);//res即result, 保存strnpy的拷贝结果. strnpy从`name`中将`MAX_DATA`个字符拷贝到`addr->name`中, 返回拷贝的字符串.  此处用res接收, 目的是检查返回值保证拷贝操作没问题.
	if(!res)
		die("拷贝名称出错");
	addr->name[MAX_DATA - 1] = '\0';//防止当name长度太长时, 导致addr->name的结尾不是'\0'. 下面的email也是这样处理的.
	
	res = strncpy(addr->email, email, MAX_DATA);//二次利用res来检查email有没有拷贝成功.
	if(!res)
		die("拷贝邮箱出错");
	addr->email[MAX_DATA - 1] = '\0';
}



//这个函数打印出数据库中第`id`个Address结构体的信息.
void Database_get(struct Connection *conn, int id)
{
	//取出第`id`个Address结构体指针.
	struct Address *addr = &conn->db->rows[id];
	
	if(addr->set)
	{
		Address_print(addr);
	}
	else
	{
		die("这个Address还没有set.");
	}	

}



//删除Database的第`id`个Address的内容.
void Database_delete(struct Connection *conn, int id)
{
	//新建一个Address然后覆盖原来的, 实现修改效果.
	struct Address addr = {.id=id, .set=0};
	conn->db->rows[id] = addr;
}






//这个函数列出数据库所有`已设置的Address`记录.即遍历数据库每一行, 筛出来set==1的Address, 将其信息打印出来.	
void Database_list(struct Connection *conn)
{
	//取出Database的指针
	struct Database *db = conn->db;

	//遍历每个Address
	for(int i =0;i<MAX_ROWS;i++)
	{
		//取出第i个Address的指针
		struct Address *cur = &db->rows[i];

		if(cur->set)//如果set=1, 即已被设置
			    Address_print(cur);
	}
}





int main(int argc, char* argv[])
{
	//接收参数
	if(argc < 3)
		die("参数格式错误. Usage: ./ex17 <database_filename> <action> [action params]");	

	char* filename = argv[1];
	char action = argv[2][0];
	struct  Connection *conn = Database_open(filename, action);
	int id = 0;
	if (argc > 3)//如果包含了[action params]
		id = atoi(argv[3]);//atoi()函数全称是ASCII to Integer. 将字符串转换为整数. 处理算法: 跳过空白字符. 处理正负号, 影响最终结果的符号. 把数字字符转换为数字,把它们拼接起来. 遇到非数字字符时,停止. 例如,对字符串"  -  125 7哈哈123", 输出整数-1257. 当然本例中argv[3]只是简单的一个数字char, 所以直接就转换了.
	if(id >= MAX_ROWS)
		die("id太大了.");

	switch(action)
	{
		case 'c'://创建操作
			Database_create(conn);//创建一个新数据库, 初始化所有记录.
			Database_write(conn);//将文件写入数据库.
			break;

		case 'g'://get操作
			 if(argc != 4)
				die("需要填写id");
			Database_get(conn, id);
			break;

		case 's'://set设置操作
			if(argc != 6)
				die("需要填写id, name, email");

			//接收name和email参数
			char* name = argv[4];
			char* email = argv[5];

			Database_set(conn, id, name, email);//将数据库修改
			Database_write(conn);//将修改后的数据库覆写本地数据库文件
			break;

		case 'd'://删除操作
			 if(argc !=4)
				 die("需要填写id");
			 Database_delete(conn, id);//将数据库对应id的数据删除(初始化)
			 Database_write(conn);//将修改后的数据库覆写本地数据库文件
			 break;

		case 'l'://列表操作
			 Database_list(conn);
			 break;

		default:
			 die("错误action选项. only: c=create, g=get, s=sset, d=del, l=list");
				
	}
	
	Database_close(conn);

	return 0;
}
