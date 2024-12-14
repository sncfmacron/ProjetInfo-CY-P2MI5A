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


// Functions declaration
void exit_with_message(const char *message, int error_code);
int getStationType(const char *station);
pStation createStation(int station_id, long capacity, int stationType);
// pAVL insertionAVL(pAVL a, Station s, int *h);
/* A coder, Nathan :DDDDDDDD

pAVL deleteAVL(pAVL a, int *h, int *pe);
pAVL deleteMinAVL(pAVL a, int *h, int *pe);
pAVL deleteAVL(pAVL a, Station s, int *h);
pAVL equilibrateAVL(pAVL a);
pAVL rotateLeft(pAVL a);
pAVL rotateRight(pAVL a);
pAVL rotateDoubleLeft(pAVL a);
pAVL rotateDoubleRight(pAVL a);

*/
void cleanAVL(pAVL a);

int max(int a, int b);
int max3(int a, int b, int c);
int min(int a, int b);
int min3(int a, int b, int c);


#endif