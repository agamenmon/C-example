#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int excute_one(int a, int b)
{
	printf("one: a:(%d), b:(%d)\n", a, b);
	return 0;
}

int excute_two(int a, int b)
{
	printf("two: a:(%d), b:(%d)\n", a, b);
	return 0;
}

struct t_command
{
	char *command;
	int (*func)	(int, int);
};

static const struct t_command command[] = {
	[0] = {.command = "1", .func = excute_one},
	[1] = {.command = "2", .func = excute_two},
};

int main(void)
{
	int i = 0, ret;
	for(i = 0; i < sizeof(command) / sizeof(struct t_command); i++)
	{
		ret = command[i].func(5,6);
	}
	return 0;
}