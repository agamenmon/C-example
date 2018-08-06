#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	char * abc;
	char * tmp;
	char abcd[256] = {0};
	
	sprintf(abcd, "1 2 3 4 5 6");
	abc = abcd;
	printf("a: %s\n",abc);
	for(;;)
	{
		tmp = strtok_r(abc, " ", &abc);	
		if(tmp == NULL)
		{
			printf("tmp: %s\n", tmp);
			break;
		}
	}

	// get the last value
	char *s = "1 2 3 4 5 6";
	char *last = strrchr(s, ' ');
		if(last != NULL)
			printf("last %s\n",last +1);	
	
	return 0;
}