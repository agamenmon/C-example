#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void abc(char *ab)
{
	strcpy(&ab, "21")
	//abc2(&ab);
}
void abc2(char *ab)
{
	abc3(&ab);
}
void abc3(char *ab)
{
	ab = "12";
}
int main(int argc, char const *argv[])
{
	char *a = 0;
	abc(a);
	printf("a: %s\n", a);
	return 0;
}