#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <curl/curl.h>

struct t_request_data
{
	char * url;
	char * data;
}