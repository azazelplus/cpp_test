#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>


//我们将ex16程序改为不适用指针和malloc的版本, 在栈上创建结构体.
struct Person{
	char *name;
	int age;
	int height;
	int weight;
};

//栈上的工厂函数.
struct Person Person_create(char* name, int age, int height, int weight)
{
	struct Person who;
	//assert(who != NULL);

	//对结构体, 使用`.`来访问成员. 对于结构体指针, 使用`->`来访问成员. 假设有一个结构体指针strptr, 那麽显然`*(strptr).member`和`struptr->member`等价.
	who.name =  strdup(name);
	who.age = age;
	who.height = height;
	who.weight = weight;

	return who;
}



int main(int argc, char* argv[]){

	//struct Person joe("Joe",18,180,50);这里不小心使用cpp风格的初始化了...
	struct Person joe = Person_create("Joe", 18, 180, 50);
	printf("Joe's name is %s.\n", joe.name);

	return 0;
}
