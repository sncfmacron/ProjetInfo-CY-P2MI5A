/*
    Library for input.c
*/


#ifndef INPUT_HEADER
#define INPUT_HEADER

#include "basics.h"

void processData();
void processStation(pAVL tree, int station_id, int capacity);
void processConsumer(pAVL tree, int station_id, int load);

#endif