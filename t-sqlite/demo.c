/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:  
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

    /*
     * open SQLite database file test.db
     * use ":memory:" to use an in-memory database
     */
    rc = sqlite3_open("test.db", &db);
    if (rc != SQLITE_OK) {
        printf("ERROR opening SQLite DB 'test.db': %s\n", sqlite3_errmsg(db));
        goto out;
    }

    /*
     * use asprintf() to dynamically handle strings (automatic allocation; don't forget to free() them)
     */
    char *query = NULL;
    
    asprintf(&query, "insert into demo (name, age) values ('%s', %d);", "Tom", 20);

    /*
     * execute commands that do not return results
     */
    sqlite3_prepare_v2(db, query, strlen(query), &stmt, NULL);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        printf("ERROR inserting data: %s\n", sqlite3_errmsg(db));
        goto out;
    }

    sqlite3_finalize(stmt);
    free(query);



    /*
     * use proper variable binding to avoid SQL injection
     */
    sqlite3_prepare_v2(db, "insert into demo (name, age) values (?1, ?2);", -1, &stmt, NULL);

    sqlite3_bind_text(stmt, 1, "Susan", -1, SQLITE_STATIC);     // the string "Susan" is static
    sqlite3_bind_int(stmt, 2, 21);

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        printf("ERROR inserting data: %s\n", sqlite3_errmsg(db));
        goto out;
    }

    sqlite3_finalize(stmt);



    /*
     * select data (multiple rows) using variable binding for the where clause
     */
    sqlite3_prepare_v2(db, "select distinct name, age from demo where age > ? order by 2,1;", -1, &stmt, NULL);

    sqlite3_bind_int(stmt, 1, 16);

    while ( (rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        /* access by column index */
        printf("%s is %d years old\n", sqlite3_column_text(stmt, 0), sqlite3_column_int(stmt, 1));
    }

    sqlite3_finalize(stmt);


    /*
     * select using the convencience wrapper sqlite3_exec() (exec uses a callback function)
     */
    char *errmsg;
    int callback(void *arg, int argc, char **argv, char **colName) {
        int i;
        for(i=0; i<argc; i++){
            printf("%s = %s\t", colName[i], argv[i] ?  : "NULL");
        }
        printf("\n");
        return 0;
    }
    rc = sqlite3_exec(db, "select distinct name, age from demo order by 1,2;", callback, NULL, &errmsg);
    if (errmsg != NULL) {
        printf("Error in sqlite3_exec: %s\n", errmsg);
        sqlite3_free(errmsg);
    }


    /*
     * sqlite3_exec() can be used for multiple queries.
     * If they do not return any data, the callback can be waived.
     */
    rc=sqlite3_exec(db, "delete from demo where age is null; delete from demo where name is null;", NULL, NULL, &errmsg);
    if (errmsg != NULL) {
        printf("Error in sqlite3_exec: %s\n", errmsg);
        sqlite3_free(errmsg);
    }

out:
    sqlite3_close(db);
}
