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
	int rc;
	int i = 0;
	int sizeOfCol = 0;
	char *col[] = {
		"col1",
		"col2",
		"col3",
	};
	char *typeCol = "TEXT";
	char *table = "testSQL";
	char *zErrMsg = 0;
	char column[SIZE_1024B] = {0};
	char tmp[SIZE_1024B] = {0};
	char sql[SIZE_1024B] = {0};

	bool insrtSQL = false;
	rc = sqlite3_open(DIRECTORY_DB, &db);
		sizeOfCol = sizeof(col)/sizeof(*col);
	for(;i < sizeOfCol; i++)
	{
		if(i)hui 
			strncat(column, ",", strlen(","));
		sprintf(tmp,"%s %s", col[i], typeCol);
		strncat(column, tmp, strlen(tmp));
	}
	sprintf(sql, "CREATE TABLE %s(%s) PRIMARY KEY (%s)", table, column, col[0]);
	rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
	if(rc != SQLITE_OK){
		if(strstr(zErrMsg, "already exists")) {
			sprintf(tmp, "CREATE TEMPORARY TABLE tmp(%s)", column);
			rc = sqlite3_exec(db, tmp, NULL, 0, &zErrMsg);
			if(rc != SQLITE_OK)
				printf("zErrMsg: %s\n", zErrMsg);
			sprintf(tmp, "")
		}
	}
	sqlite3_close(db);
	return 0;
}

// gcc j-columnSqlite2.c -o sql -lsqlite3