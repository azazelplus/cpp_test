#include <stdio.h>


int main(int argc, char* argv[])
{
	int i=0;

	//从argv[1]开始,是因为第一个参数是函数本身的名称或者路径, 从第二个开始是用户实际传递给程序的参数.
	for(i=1;i<argc;i++){
		printf("arg %d: %s\n", i, argv[i]);
	}


	//构造一个数组.
	char* states[]={
		"California", "Oregon", "Washington", "Texas"
	};
	int num_states=4;
	for(i=0;i<num_states;i++){
		printf("states %d: %s\n", i , states[i]);
	}
	return 0;
}






