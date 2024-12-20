/*
    main.h : main program library
*/


#ifndef MAIN_HEADER
#define MAIN_HEADER

// Early declaration of the Station type for use across the program
typedef struct Station_struct Station;
typedef Station* pStation;

#include "basics.h"

extern pAVL globalTree;
extern pStation* stationArray;
extern uint32_t nbStations;

void cleanup(void);
void sortMinMax(char* stationType, char* consumerType);

#endif