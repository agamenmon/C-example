#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define MIN -76.0
#define MAX -50.0

#define MAX_PERCENT 100
#define MIN_PERCENT 0

int main(int argc, char const *argv[])
{
	int rssi = -80;
	int i;
	int percent;
	
	double firstNumber = (MAX_PERCENT - MIN_PERCENT) / (MAX - MIN);
	double secondNumber = MIN_PERCENT - MIN * firstNumber;
	
	printf("%0.4lf, %0.4lf\n", firstNumber, secondNumber);

	for(i = rssi; i <= -40; i++)
	{
		percent = firstNumber * i + secondNumber;
		printf("i: %d, percent: %d\n",i, percent);
	}

	if(percent >= MAX_PERCENT)
		percent = MAX_PERCENT;
	else if(percent <= MIN_PERCENT)
		percent = MIN_PERCENT;

	//printf("first: %ld, second: %ld, percent: %ld\n", firstNumber, secondNumber, percent);
	return 0;
}