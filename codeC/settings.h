/*
    settings.h: contains constants for security and optimization
*/


#ifndef SETTINGS_HEADER
#define SETTINGS_HEADER

#define ERR_ATEXIT 1

#define ERR_PTR_ALLOC 2
#define ERR_AVL_ALLOC 3
#define ERR_ARRAY_ALLOC 4

#define ERR_TIME_CLOCK 5

#define ERR_FILE_PATH 6
#define ERR_MISSING_FILE 7
#define ERR_FILE_CREATION 8

#define ERR_INPUT_FORMAT 9

#define ERR_INVALID_STATION 10
#define ERR_INVALID_ARGS 11
#define ERR_NULL_AVL 12
#define ERR_NULL_POINTER 13
#define ERR_NULL_ARRAY 14

#define MAX_BUFFER_SIZE 8192  // (8 Ko)

#define DIR_STATION_FILTERED "tmp/extracted_station.csv"
#define DIR_CONSUMER_FILTERED "tmp/extracted_consumer.csv"
#define DIR_OUTPUT "output/"
#define DIR_LV_MINMAX "output/lv_all_minmax.csv"

#define NB_MINMAX_STATIONS 20

#endif