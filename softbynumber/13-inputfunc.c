#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* define struct variable */
struct variable
{
	int a;
	int b;
	int c;
	int d;
	int e;
};
/* global variable */
struct variable _variable;

/*input function is big */
void printf_Variable(int a, int b, int c, int d, int e)
{
	printf("a: %d,%d,%d,%d,%d \n", a, b, c, d, e);
}

/* input variable is small */
void printf_VariableB(struct variable _variable)
{
	printf("a: %d,%d,%d,%d,%d \n", _variable.a, _variable.b, _variable.c, _variable.d, _variable.e);
}

int main(int argc, char const *argv[])
{
	_variable.a = 1;
	_variable.b = 1;
	_variable.c = 1;
	_variable.d = 1;
	_variable.e = 1;

	clock_t begin = clock();
	printf_Variable(_variable.a, _variable.b, _variable.c, _variable.d, _variable.e);
	clock_t end = clock();

	clock_t beginB = clock();
	printf_VariableB(_variable);
	clock_t endB = clock();

	printf("time excute function: %f, %f \n", (double)(end - begin) / CLOCKS_PER_SEC, (double)(endB - beginB) / CLOCKS_PER_SEC);

	return 0;
}