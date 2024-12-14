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

#include "calculations.h"
#include "input.h"
#include "output.h"
#include "settings.h"
#include "tree.h"


// Structures


// Functions declaration
void exit_with_message(const char *message, int error_code);
int getStationType(const char *station);
pStation createStation(int station_id, long capacity, int stationType);

int max(int a, int b);
int max3(int a, int b, int c);
int min(int a, int b);
int min3(int a, int b, int c);


#endif