/*
    Contains constants for security and optimization
*/


#ifndef SETTINGS_HEADER
#define SETTINGS_HEADER

#define ERR_PIPE 1

#define ERR_PTR_ALLOC 2
#define ERR_AVL_ALLOC 3
#define ERR_FILE_ALLOC 4

#define ERR_INVALID_STATION_TYPE 5
#define ERR_INVALID_CONSUMER_TYPE 6

#define ERR_FILE_WRITE_FAILED 7

#define ERR_INVALID_STRING 8
#define ERR_INVALID_STATION 9

#define MAX_BUFFER_SIZE 2048

#define STATION_HVB 2
#define STATION_HVA 1
#define STATION_LV 0

#define CONSUMER_INDIV 0
#define CONSUMER_COMP 1
#define CONSUMER_ALL 2

#define DIR_OUTPUT "./output/"

#endif