/*
    settings.h : contains constants for security and optimization
*/


#ifndef SETTINGS_HEADER
#define SETTINGS_HEADER

#define ERR_COMPILATION 1

#define ERR_PTR_ALLOC 2
#define ERR_AVL_ALLOC 3

#define ERR_MISSING_FILE 4
#define ERR_FILE_CREATION 5

#define ERR_INVALID_STATION_TYPE 6
#define ERR_INVALID_CONSUMER_TYPE 7

#define ERR_FILE_WRITE_FAILED 8

#define ERR_INVALID_STRING 9
#define ERR_INVALID_STATION 10

#define ERR_NULL_AVL 11

#define ERR_INPUT_FORMAT 12

#define ERR_INVALID_ARGS 13


#define MAX_BUFFER_SIZE 8192  // (8 Ko)


#define DIR_STATION_SORTED "tmp/station_sorted.csv"
#define DIR_CONSUMER_SORTED "tmp/consumer_sorted.csv"
#define DIR_OUTPUT "output/"
#define DIR_LV_MINMAX "output/lv_all_minmax.csv"

#endif