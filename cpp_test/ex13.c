#include <stdio.h>

int main(int argc, char* argv[]){
	if(argc!=2){
		printf("ERROR. You need one argument.\n");
		return 1;
	}

	//arg[1]是用户传入的那个字符串命令。
	for(i=0;argv[1][i])!='\0';i++){
		char letter=argv[1][i];//取出命令的第i角标字母
	//switch的贯穿; 当某个case标签匹配成功后, 如果没有遇到break语句, 程序会继续执行下一个case的代码, 而不会判断下一个case标签是否匹配.		
		switch(letter){
			case 'a':
			case 'A':
				printf("%d: 'A'\n",i);
				break;

			case 'e':
			case 'E':
				printf("%d: 'E'\n",i);
				break;

			case 'i':
			case 'I':
				printf("%d: 'I'\n",i);
				break;

			case 'o':
			case 'O':
				printf("%d: 'O'\n",i);
				break;

			case 'u':
			case 'U':
				printf("%d: 'U'\n",i);
				break;

			default:
				printf("%d: %c is not a vowel\n",i,letter);
		}	
	}
	return 0;
}
