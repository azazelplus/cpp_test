#include <stdio.h>
#include <ctype.h>//用来访问isalpha()和isblank().
		  // 这两个int返回值函数判定一个字符是不是英文字母/是不是空白字符或制表符.

//forward declarations前向声明
//
//这个函数判定一个单字符能否被打印. 可打印的定义为字母或空字符.
int can_print_it(char ch);

//这个函数将一个字符串中所有可打印字符打印出来.
void print_letters(char arg[]);

//这个函数将一个字符串数组的每个字符串用上述方法打印.
void print_arguments(int argc, char* argv[])
{
	for(int i=0;i<argc;i++){
		print_letters(argv[i]);
	}
}

void print_letters(char arg[])
{
	for(int i=0;arg[i]!= '\0';i++){
		char ch = arg[i];
		if(can_print_it(ch))
			printf("'%c'== %d", ch, ch);

	}
}


int can_print_it(char ch)
{
	//如果是字母或空字符/制表符, 则输出1表示这是可打印的.
	return isalpha(ch) || isblank(ch);
}

//主函数的作用是将第二个开始的参数列表的每个可打印字母打印出来.
int main(int argc, char* argv[]){
	print_arguments(argc-1, argv+1);
	return 0;
}
