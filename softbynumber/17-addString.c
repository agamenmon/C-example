#include <stdio.h>
#include <stdlib.h>

#define ABC "12"

int main(int argc, char const *argv[])
{
	char *sql = NULL;

	sql = "CREATE aksdkjahd" \
			"1 ....." + ABC;
	printf("SQL: %s\n", sql);
	return 0;
}