/*
    Calculation library
*/


#ifndef CALCULATIONS_HEADER
#define CALCULATIONS_HEADER

typedef struct Station_struct Station;
typedef Station* pStation;

typedef struct AVL_struct AVL;
typedef AVL* pAVL;

#include "basics.h"

void updateSum(pAVL a, int stationID, long load);

#endif