#include <stdio.h>
#include <stdlib.h>

#define HELLO "HELLO-WORLD"

int funct(char *hello)
{
	printf("String: %s\n", hello);
	return 0;
}

int main(void)
{
	int ret = funct(HELLO);
	if(ret != 0)
		printf("ERROR funct \n");
	return 0;
}