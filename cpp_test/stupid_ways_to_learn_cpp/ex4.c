#include <stdio.h>

/*这是一个故意出错的程序.*/

int main()
{
	int age=10;
	int height;
	printf("i am %d years old.\n");//缺少更多变量.
	printf("i am %d inches tall.", height);//use uninitialised var `height`.
	return 0;

}
