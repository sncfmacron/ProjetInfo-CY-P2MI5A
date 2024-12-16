/*
    Contains constants for security and optimization
*/


#ifndef SETTINGS_HEADER
#define SETTINGS_HEADER

#define ERROR_PIPE 1
#define ERROR_PTR_ALLOC 2
#define ERROR_FILE_ALLOC 3
#define ERROR_INVALID_STATION 4
#define ERROR_DUPLICATE_ID 5
#define ERROR_MISSING_DATA 6
#define ERROR_PERMISSION_DENIED 7

#define MAX_BUFFER_SIZE 2048

#define STATION_HVB 2
#define STATION_HVA 1
#define STATION_LV 0

#define CONSUMER_INDIV 0
#define CONSUMER_COMP 1
#define CONSUMER_ALL 2

#define DIR_OUTPUT "./output/"

#endif