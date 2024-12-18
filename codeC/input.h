/*
    input.h : ibrary for input.c
*/


#ifndef INPUT_HEADER
#define INPUT_HEADER

typedef struct Station_struct Station;
typedef Station* pStation;
typedef struct AVL_struct AVL;
typedef AVL* pAVL;

#include "basics.h"

pAVL processStation(const char *filePath, pAVL tree, pStation* stations);
pAVL processConsumer(const char *filePath, pAVL tree);

#endif