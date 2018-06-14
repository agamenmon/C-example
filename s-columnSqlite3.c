/*
 * Author: Nguyen Thanh Son
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <stdbool.h>

#define SIZE_1024B 1024
#define DIRECTORY_DB "/home/thanhson/Desktop/1-thanhson/2-git/pluto/db-sqlite/db-file/test.db"

int main(void)
{
	sqlite3 *db;
	int i = 0;
	int rc = 0;
	int sizeOfCol = 0;
	char *col[] = {
		"col1",
		"col2",
		"col3",
		"col4",
	};
	char sql[SIZE_1024B] = {0};
	char *typeCol = "TEXT";
	char *table = "testSQL";
	char column[SIZE_1024B] = {0};
	char tmp[SIZE_1024B] = {0};
	char *zErrMsg;

	rc = sqlite3_open(DIRECTORY_DB, &db);
	sizeOfCol = sizeof(col)/sizeof(*col);
	for(;i < sizeOfCol; i++)
	{
		if(i)
			strncat(column, ",", strlen(","));
		sprintf(tmp,"%s %s", col[i], typeCol);
		strncat(column, tmp, strlen(tmp));
	}
	sprintf(sql, "CREATE TABLE %s(%s)", table, column);
	rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
	if(strstr(zErrMsg, "already exists"))
	{
		// check column in the old SQL/ if column not exist, add it
		for (i = 0; i < sizeOfCol; i++)
		{
			sprintf(tmp, "ALTER TABLE %s ADD COLUMN %s %s", table, col[i], typeCol);
			rc = sqlite3_exec(db, tmp, NULL, 0, &zErrMsg);
			if(strstr(zErrMsg, "duplicate column name"))
				printf("Dont add column: %s\n", col[i]);
			else
				printf("Add column: %s\n", col[i]);
		}
	}
	sqlite3_close(db);
	return 0;
}

// gcc s-columnSqlite3.c -o sql -lsqlite3 D90nikon.