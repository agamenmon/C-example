#include <stdio.h>
#include <stdio.h>
#include <string.h>

#define check(a,b) \
		int a = 0; \
		a = b; \
		printf("aa: %d\n", a); \

int main(int argc, char const *argv[])
{
	int b = 1;
	check(a,b);
	//printf("a: %d\n", a);
	if(a = b)
	{
		printf("asd\n");
	}
	return 0;
}