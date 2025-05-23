#include <stdio.h>

int main(int argc, char* argv[]){
	//先创建人名和年龄数组.
	int ages[]={23,43,12,89,2};
	char* names[]={"Alan","Frank","Mary","John","Lisa"};

	//得到age数组长度
	int count = sizeof(ages) / sizeof(int);
	
	//第一种方式打印人名和年龄.
	for(int i=0; i<count; i++){
		printf("%s has %d years alive.\n",
				names[i], ages[i]);
	}

	printf("---\n");

	//第二种方式打印.
	
	int *cur_age = ages;
	char** cur_name = names;//也可以写成char* cur_name[]=names;  总之这两句话制造了两个相同的指针,ages和cur_age此事是相同的指针, names和cur_name也是.
	
	for(int i =0; i<count; i++){
		printf("%s has %d years alive.\n",
				*(cur_name+i), *(cur_age+i));
	}

	printf("---\n");


	//第三种方式打印. 没啥意思, 把那两个新声明的指针当作数组用而已
	for(int i = 0; i<count; i++){
		printf("%s is %d years old again.\n",
				cur_name[i], cur_age[i]);
	}
	printf("---\n");


	//第四种方法打印. 这种方法很蠢
	for(cur_name = names, cur_age = ages;
			(cur_age - ages) < count;
			cur_name++, cur_age++)
	{
			printf("%s is %d years old again.", *cur_name, *cur_age);
	}
	return 0;
}
