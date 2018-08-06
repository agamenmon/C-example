#include <stdio.h>
#include <stdlib.h>


#define MIN_RSSI -100
#define MAX_RSSI -50

int main(void)
{
	int rssi = -10;
	int quality;

	quality = 2 * (rssi + 100);

	printf("quality: (%d)\n",quality ); // percent

	return 0;
}