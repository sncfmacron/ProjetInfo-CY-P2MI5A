/*
    Library for input.c
*/


#ifndef INPUT_HEADER
#define INPUT_HEADER

#include "basics.h"

typedef struct Station Station;
typedef struct Station* pStation;

void readData(int stationType);
void printStation(pStation s);


#endif