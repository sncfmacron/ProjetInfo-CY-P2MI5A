/*
    input.h : ibrary for input.c
*/


#ifndef INPUT_HEADER
#define INPUT_HEADER

typedef struct AVL_struct AVL;
typedef AVL* pAVL;

#include "basics.h"

pAVL processFile(const char* filename, pAVL tree);

#endif