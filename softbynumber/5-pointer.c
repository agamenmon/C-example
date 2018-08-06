#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ret1(int *ret)
{
	*ret += 1;
}
void ret2(int *ret)
{
	*ret += 2;
}
int main(int argc, char const *argv[])
{
	int ret = 0;
	ret1(&ret);
	ret2(&ret);
	printf("ret: %d\n", ret);
	return 0;
}