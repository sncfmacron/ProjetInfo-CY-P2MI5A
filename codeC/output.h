/*
    output.c : library for output.c
*/


#ifndef OUTPUT_HEADER
#define OUTPUT_HEADER

typedef struct AVL_struct AVL;
typedef AVL* pAVL;

#include "basics.h"

void outputProcess(const char* stationType, const char* consumerType, const char* powerPlantID, pAVL tree);
void createPath(const char* stationType, const char* consumerType, const char* powerPlantID, char* path, int sizePath);
FILE* initOutputFile(const char* stationType, const char* consumerType, const char* powerPlantID);
void writeOutputFile(pAVL tree, FILE* file);

#endif