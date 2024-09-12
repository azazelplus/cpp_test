#include <stdio.h>

//用while重写一遍ex10.
int main(int argc, char* argv[])
{
	
	int i=0;
	while(i<argc){
		printf("arg %d: %s\n",i,argv[i]);
		i++;
	}
	
	//第二个独立任务
	char* provinces[]={
	"河南","陕西","香港","上海"
	};

	int num_province=4;

	
	i=0;
	while(i<num_province){
		printf("province %d: %s\n", i, provinces[i]);
		i++;
	}
	return 0;

}
