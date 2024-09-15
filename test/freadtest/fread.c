#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
//这个C程序从当前目录读取名为file的文件, 把其中存储的数字作为字符串打印出来.
int main(int argc, char* argv[])
{

	//打开文件
	FILE *file = fopen("file","r");
	assert(file);
	
	//找到文件大小
	fseek(file, 0, SEEK_END);//指针移动到文件末尾
	long file_size = ftell(file);//ftell得到当前位置, 即文档的字节大小
	rewind(file);//文件指针返回文件开头.

	
	//分配内存和
	char *buffer = (char*)malloc(
			(file_size + 1)*sizeof(char)
				);//分配一个动态内存buffer来存读取的文件内容.这个动态内存快的大小比读取文件多一个字节, 用来装'\0', 将buffer组装为标准C风格字符串.
	
	//读取文件内容到buffer
	size_t read_size = fread(buffer, sizeof(char), file_size, file);
	if(read_size != file_size)//如果读取成功， fread函数返回值即为成功读取的元素个数file_size.
		{
			perror("Failed to read the COMPLETE file!!");
			free(buffer);
			fclose(file);
			return 1;
		}

	//打印读取的内容
	printf("File content: %s\n", buffer);
	
	//清理动态内存, 关闭打开的文件
	free(buffer);
	fclose(file);
	

	return 0;
}
