/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  demo using an in-memory database
 *
 *        Version:  1.0
 *        Created:  01.09.2013 18:21:45
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Georg Wassen (gw) (), 
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>


int main()
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    char *errmsg;

    /*
     * open SQLite database file test.db
     * use ":memory:" to use an in-memory database
     */
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        printf("ERROR opening SQLite DB in memory: %s\n", sqlite3_errmsg(db));
        goto out;
    }


    rc = sqlite3_exec(db, "create table demo (name text, age, integer);", NULL, NULL, &errmsg);
    if (rc != SQLITE_OK) {
        printf("Error: %s\n", errmsg);
        goto out;
    }

    rc = sqlite3_exec(db, "insert into demo (name, age) values('Tom', 21); insert into demo (name, age) values ('Chris', 25);", NULL, NULL, &errmsg);
    if (rc != SQLITE_OK) {
        printf("Error: %s\n", errmsg);
        goto out;
    }

    /*
     * select using the convencience wrapper sqlite3_exec() (exec uses a callback function)
     */
    int callback(void *arg, int argc, char **argv, char **colName) {
        int i;
        for(i=0; i<argc; i++){
            printf("%s = %s\t", colName[i], argv[i] ?  : "NULL");
        }
        printf("\n");
        return 0;
    }
    rc = sqlite3_exec(db, "select count(*), avg(age) from demo; select distinct name, age from demo order by 1,2;", callback, NULL, &errmsg);
    if (errmsg != NULL) {
        printf("Error in sqlite3_exec: %s\n", errmsg);
        sqlite3_free(errmsg);
    }



out:
    sqlite3_close(db);
}
