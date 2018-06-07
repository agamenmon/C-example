#!/bin/bash
#===============================================================================
#
#          FILE:  sqlinit.sh
# 
#         USAGE:  ./sqlinit.sh 
# 
#   DESCRIPTION:  Example to initialize SQLite database using shell script
# 
#       OPTIONS:  ---
#  REQUIREMENTS:  ---
#          BUGS:  ---
#         NOTES:  ---
#        AUTHOR:   (), 
#       COMPANY:  
#       VERSION:  1.0
#       CREATED:  01.09.2013 18:55:05 CEST
#      REVISION:  ---
#===============================================================================


sqlite3 test.db "CREATE TABLE demo (id INTEGER PRIMARY KEY, name TEXT, age INTEGER);"
sqlite3 test.db "INSERT INTO demo (name, age) VALUES ('Peter', 42);"

