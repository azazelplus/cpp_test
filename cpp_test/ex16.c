#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
//结构体
//
// 结构体定义
struct Person{
	char* name;
	int age;
	int height;
	int weight;
};

//Person_create是返回值为struct Person*的工厂函数. 这是工厂函数定义.(对应cpp中的构造函数,只是cpp中可以写道结构体定义里, 而c中要单独写出来.)
struct Person* Person_create(char* name, int age, int height, int weight)
{
	struct Person *who = malloc(sizeof(struct Person));//who是惯例取名.此句分配了一块内存给一个结构体指针who.
	assert(who != NULL);//assert()函数用于检查malloc是否分配成功. assert()是调试函数, 如果条件为假(即布尔值0或NULL), 则终止程序, 输出错误信息.
	
	//初始化字段.
	who->name = strdup(name);//strdup是C标准库函数. 用于复制一个字符串并返回新字符串地址. 这句话把name字符串复制出来给who的成员变量name. ->是访问结构体成员的运算符, 类似python中访问成员或方法的`.`. who->name等价于(*who.name).
	who->age = age;
	who->height = height;
	who->weight = weight;
	return who;
}


//析构函数的声明. 同样的, 在cpp中析构函数可以写到class里面.
void Person_destory(struct Person* who)//who也是一个惯例取名. 析构函数传入一个结构体指针.
{
	assert(who != NULL);//如果指针已经被清理, 则推出析构函数
	free(who->name);//这个字符串是动态分配的内存, 所以需要销毁.
	free(who);//然后销毁整个指针.
}


//c中没有类的概念, 结构体只有成员变量没有成员函数. 只能单独写一个函数了.
void Person_print(struct Person* who)
{
	printf("Name: %s\n", who->name);
	printf("\tAge: %d\n", who->age);
	printf("\tHeight: %d\n", who->height);
	printf("\tWeight: %d\n", who->weight);
}



//下面调用主函数.
int main(int argc, char* argv[]){
	struct Person *joe = Person_create("Joe Alex",32, 64, 140);
	//在c中, 工厂函数可以直接返回一个对象(栈分配), 也可以像本例一样返回一个动态分配好的对象指针(堆分配). 而在cpp中直接调用构造函数, 是等同于c中直接返回一个对象(栈分配). 如果在cpp中也想用动态分配, 可以`Person* Joe = new Person("Joe Alex",32, 64, 140);`来实现.
	struct Person *frank = Person_create("Frank Blank", 20, 72, 180);

	//打印他们的名字和在内存中的位置. %p是打印指针地址.
	printf("Joe is at memory location %p\n",joe);
	Person_print(joe);

	printf("Frank is at meory location %p\n",frank);
	Person_print(frank);

	//把他们的年龄改为20岁, 然后再打印一次.
	joe->age = 20;
	frank->age = 20;
	Person_print(joe);
	Person_print(frank);
	
	//清楚他们.
	Person_destory(joe);
	Person_destory(frank);

	return 0;	
}
