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

static int callback(void *data, int argc, char **argv, char **azColName)
{
	int i = 0;
	char tmp[1024] = {0};

	for (i = 0; i < argc; i++) {
		if(i)
			strncat(tmp, ",", strlen(","));
		strncat(tmp, azColName[i], strlen(azColName[i]));
	}
	strcpy(data, tmp);
	return 0;
}

int main(void)
{
	sqlite3 *db;
	int i = 0;
	int rc = 0;
	int j = 0;
	bool ckColCurr = false;
	bool colExist = false;
	int sizeOfCol = 0;
	char *col[] = {
		"col1",
		"col2",
		"col3",
	};
	char sql[SIZE_1024B] = {0};
	char *typeCol = "TEXT";
	char *table = "testSQL";
	char column[SIZE_1024B] = {0};
	char tmp[SIZE_1024B] = {0};
	char *zErrMsg = 0;
	char colCurr[SIZE_1024B] = {0};

	rc = sqlite3_open(DIRECTORY_DB, &db);
	sizeOfCol = sizeof(col)/sizeof(*col);
	for(;i < sizeOfCol; i++)
	{
		if(i)
			strncat(column, ",", strlen(","));
		sprintf(tmp,"%s %s", col[i], typeCol);
		strncat(column, tmp, strlen(tmp));
	}
	sprintf(sql, "CREATE TABLE %s(%s) PRIMARY KEY (%s)", table, column, col[0]);
	rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
	if(strstr(zErrMsg, "already exists"))
	{
		// read column exist on the table with the column on source code, 
		// if its not the same name with the column on source code
		// we delete that column.
		// problem: cant read the column name if the table doesnt have any the data.
		// solve: insert a tmp data into any column.
		// INSERT INTO "table" VALUES
		for (i = 0; i < sizeOfCol; i++)
		{
			sprintf(tmp, "INSERT INTO %s(%s) VALUES (\"tmp\")",table, col[i]);
			rc = sqlite3_exec(db, tmp, NULL, 0 , &zErrMsg);

			if(zErrMsg == NULL)
			{
				// select * from testSQL where col1="tmp"
				// check name col isnt belong to the new column. 
				// if not. delete that column
				if(ckColCurr == false)
				{
					sprintf(tmp, "SELECT * FROM %s where %s=\"tmp\"", table, col[i]);
					rc = sqlite3_exec(db, tmp, callback, &colCurr, &zErrMsg);
					if(rc != SQLITE_OK)
						printf("Error Query callback\n");
					char * lstColCurr = colCurr;
					char *colCurrTmp;

					while(colCurrTmp = strtok_r(lstColCurr, ",", &lstColCurr)) {
						if(colCurrTmp != NULL)
						{
							for(j = 0; j < sizeOfCol; j++)
							{
								if(!strcmp(colCurrTmp, col[j])){
									colExist  = true;
									j = sizeOfCol;
								}
							}
							if(colExist == false)
							{
								printf("delete col: %s\n", colCurrTmp);
								// https://www.sqlite.org/faq.html (11)
								// the solution on sqlite is so much thing do do next and I just need to delete that column. 
								// so i write another solution. 
								
								// if the column isnt exit, delete the column.
								/* sprintf(tmp, "ALTER TABLE %s DROP COLUMN %s", table, colCurrTmp);
								rc = sqlite3_exec(db, tmp, NULL, 0, &zErrMsg);
								if(rc != SQLITE_OK)
									printf("zErrMsg: %s\n", zErrMsg); */
							}
							else
								colExist = false;
						}
					}
					ckColCurr = true;
				}
				// check colCurr with the new col. Check just one times
				// delete value
				sprintf(tmp, "DELETE FROM %s WHERE %s=\"tmp\"", table, col[i]);
				rc = sqlite3_exec(db, tmp, NULL, 0 , &zErrMsg);
				if(rc != SQLITE_OK)
					printf("zErrMsg: %s\n", zErrMsg);

			} else {
				if(strstr(zErrMsg, "has no column")) {
					sprintf(tmp, "ALTER TABLE %s ADD COLUMN %s %s", table, col[i], typeCol);
					rc = sqlite3_exec(db, tmp, NULL, 0, &zErrMsg);
					if(rc != SQLITE_OK)
						printf("zErrMsg: %s\n", zErrMsg);
				}
			}
		}

		// check column in the old SQL/ if column not exist, add it
		/*for (i = 0; i < sizeOfCol; i++)
		{
			sprintf(tmp, "ALTER TABLE %s ADD COLUMN %s %s", table, col[i], typeCol);
			rc = sqlite3_exec(db, tmp, NULL, 0, &zErrMsg);
			if(strstr(zErrMsg, "duplicate column name"))
				printf("Dont add column: %s\n", col[i]);
			else
				printf("Add column: %s\n", col[i]);
		} */
	}
	sqlite3_close(db);
	return 0;
}

// gcc s-columnSqlite3.c -o sql -lsqlite3