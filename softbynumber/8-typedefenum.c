#include <stdio.h>
#include <stdlib.h>

typedef enum
{
	abc1 = 0,
	abc2 = 1,
} abc;

int main(int argc, char const *argv[])
{
	abc value = 1;
	switch (value)
	{
		case abc1:
		case abc2:
			printf("abc1 or abc2\n");
			break;
		default:
			printf("default\n");
			break;
	}
	printf("value: %d\n", value);
	return 0;
}