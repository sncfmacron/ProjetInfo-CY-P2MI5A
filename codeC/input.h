/*
    input.h : ibrary for input.c
*/


#ifndef INPUT_HEADER
#define INPUT_HEADER

typedef struct AVL_struct AVL;
typedef AVL* pAVL;

#include "basics.h"

pAVL processStation(const char *filePath, pAVL tree);
pAVL processConsumer(const char *filePath, pAVL tree);

#endif