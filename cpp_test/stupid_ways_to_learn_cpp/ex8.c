#include <stdio.h>

int main(int argc, char* argv[])
{
	int areas[]={1,12,13,14,20};
	char name[]="Zod";
	char full_name[]={'Z','e','d',' ','A','.',' ','S','h','a','w'};
	printf("The size of an int: %ld\n", sizeof(int));
	printf("The size of areas (int[]): %ld\n", sizeof(areas));
	printf("The number of ints in areas: %ld\n", sizeof(areas)/sizeof(int));
	printf("The first area is %d, the 2nd is %d.\n", areas[0],areas[1]);
	printf("The size of a char: %ld\n", sizeof(char));
	printf("The size of name(char[]): %ld\n", sizeof(name));
	printf("The number of chars: %ld\n", sizeof(full_name)/sizeof(char));

	printf("name=\"%s\" and full name=\"%s\"", name, full_name);
	return 0;
}

