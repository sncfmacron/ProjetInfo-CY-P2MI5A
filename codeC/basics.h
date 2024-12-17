/*
    Contains the basic structures and libraries
*/


#ifndef BASIC_HEADER
#define BASIC_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


// Early declaration of the Station type for use across the program
typedef struct Station_struct Station;
typedef Station* pStation;


#include "calculations.h"
#include "input.h"
#include "output.h"
#include "settings.h"
#include "tree.h"


// Functions declaration
void exit_with_message(const char *message, int error_code);
int getStationType(const char *station);
float getTime(clock_t start, clock_t end);
pStation createStation(int station_id, long capacity);

int string_to_int(const char* string);
long string_to_long(const char* string);

int max3(int a, int b, int c);
int min3(int a, int b, int c);
int max(int a, int b);
int min(int a, int b);


#endif