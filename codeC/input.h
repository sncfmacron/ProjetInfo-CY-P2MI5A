/*
    input.h : ibrary for input.c
*/


#ifndef INPUT_HEADER
#define INPUT_HEADER

// Early declaration of the Station type for use across the program
typedef struct Station_struct Station;
typedef Station* pStation;
typedef struct AVL_struct AVL;
typedef AVL* pAVL;

#include "basics.h"

// Functions declaration
pAVL processStation(const char *filePath, pAVL tree, pStation* stationArray, pStation* mmArray, char* consumerType);
void processConsumer(const char *filePath, pAVL tree);

#endif