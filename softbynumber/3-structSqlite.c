#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>

#define SQL "/home/thanhson/Desktop/1-thanhson/2-git/pluto/db-sqlite/db-file/test.db"
#define TABLE "DEVICES"

struct pluto
{
	char id[32];
	char playLED[21];
	char motion[32];
	struct pluto *next;
};

struct pluto *head = NULL;

static int callback_sqlite(void *data, int argc, char **argv, char **azColName)
{
	int i = 0;
	char *playLED;
	char *motionDetect;
	for (i = 0; i < argc; i++)
	{
		if(!strcmp(azColName[i], "playLED"))
		{
			playLED = argv[i]
		}
		else if(!strcmp(azColName[i], "motionDetect"))
		{
			motionDetect = argv[i];
		}
	}
	pluto *pluto = _insert_setting_pluto(id, playLED, motionDetect);
	printf("\n");
	return 0;
}
int main(int argc, char const *argv[])
{
	sqlite3 *db;
	int rc;
	char *zMsgErr;
	char sql[2048] = {0};
	rc = sqlite3_open(SQL, &db);

	sprintf(sql, "SELECT * FROM %s WHERE version IS NOT NULL", TABLE);
	rc = sqlite3_exec(db, sql, callback_sqlite, 0, &zMsgErr);
	return 0;
}

// gcc .. -o sql -lsqlite3