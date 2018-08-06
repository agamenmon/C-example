
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sqlite3.h>
#include <stdbool.h>

#define VERSION_UCI "1.1"
#define DIRECTORY_DB "/home/thanhson/Desktop/1-thanhson/2-git/pluto/db-sqlite/db-file/test.db"

sqlite3 *db;

static int callback_tableA(void *data, int argc, char **argv, char **azColName)
{
	int rc;
	char sqlCmd[512] = {0};
	char tmp[512] = {0};
	char *zErrMsg;

	printf("data: %s \n", data);
	printf("Add column %s \n", data);
	sprintf(sqlCmd, "ALTER TABLE TABLEA ADD COLUMN %s TEXT", data);
	rc = sqlite3_exec(db, sqlCmd, NULL, 0, &zErrMsg);
	if(rc != SQLITE_OK)
		printf("zErrMsg: %s\n", zErrMsg);
	else
		printf("ADD column %s success\n", data);

	return 0;
}

int main(int argc, char const *argv[])
{
	int rc;
	char * sql;
	char *version = "1.2";
	char *zErrMsg;

	char *FtSupport = "C";

	sql = "CREATE TABLE TABLEA( " \
				"A  TEXT, "       \
				"B  TEXT, "       \
				"C  TEXT, "		  \
				"PRIMARY KEY(A) );";

	rc = sqlite3_open(DIRECTORY_DB, &db);
	if(rc != SQLITE_OK)
		printf("Cant open the database \n");

	rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
	if(rc != SQLITE_OK)
	{
		if(strstr(zErrMsg, "already exists"))
		{
			if(strcmp(version, VERSION_UCI)) {
				printf("Version db and version on db is different\n");
				rc = sqlite3_exec(db, "SELECT * FROM TABLEA WHERE NOT A='' LIMIT 1", callback_tableA, FtSupport, &zErrMsg);
				if(rc == SQLITE_OK) {

					printf("Drop table A\n");
					rc = sqlite3_exec(db, "DROP TABLE TABLEA", NULL, 0, &zErrMsg);
					if(rc != SQLITE_OK)
						printf("cant drop tableA\n");

					printf("Create table A\n");
					rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
					if(rc != SQLITE_OK)
						printf("cant create tableA\n");
				}
				printf("Change version_uci the same with version current \n");
			}
			else
				printf("Version SQL is the same.\n");		
		}
	}
	sqlite3_free(zErrMsg);
	sqlite3_close(db);
	return 0;
}

// gcc z-sqliteColumn4.c -o sql -lsqlite3