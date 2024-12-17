/*
    Calculation library
*/


#ifndef CALCULATIONS_HEADER
#define CALCULATIONS_HEADER

typedef struct Station_struct Station;
typedef Station* pStation;

#include "basics.h"

void updateSum(pStation s, long load);

#endif