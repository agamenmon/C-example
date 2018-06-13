#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char * stringOne = "123";
	char * stringTwo = "1233";
	char * stringThree = NULL;

	printf("stringOne: %s, stringTwo: %s \n", stringOne, stringTwo);
	if(stringTwo == stringOne)
		printf("The string is equal \n");
	else{
		printf("the two string isnt equal \n");
		stringThree = stringTwo;
		printf("stringThree: %s\n", stringThree);
	}
	
	return 0;
}