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

#include <stdio.h>      // printf
#include <sqlite3.h>    // SQLite header (from /usr/include)

int main()
{
    sqlite3 *db;        // database connection
    int rc;             // return code
    char *errmsg;       // pointer to an error string

    /*
     * open SQLite database file test.db
     * use ":memory:" to use an in-memory database
     */
    rc = sqlite3_open(":memory:", &db);
    if (rc != SQLITE_OK) {
        printf("ERROR opening SQLite DB in memory: %s\n", sqlite3_errmsg(db));
        goto out;
    }
    printf("opened SQLite handle successfully.\n");

    /* use the database... */

out:
    /*
     * close SQLite database
     */
    sqlite3_close(db);
    printf("database closed.\n");
}
