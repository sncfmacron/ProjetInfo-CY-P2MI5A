/*
    output.c : library for output.c
*/


#ifndef OUTPUT_HEADER
#define OUTPUT_HEADER

typedef struct AVL_struct AVL;
typedef AVL* pAVL;

#include "basics.h"

void outputProcess(const char* stationType, const char* consumerType, const char* powerPlantID, pStation* stations, uint32_t nb_stations);
void createPath(const char* stationType, const char* consumerType, const char* powerPlantID, char* path, int sizePath);
void writeOutputFile(pStation* stations, FILE* file, uint32_t nbStations);
FILE* initOutputFile(const char* stationType, const char* consumerType, const char* powerPlantID);
FILE* initLvMinMax(FILE* file, pStation* stations, uint32_t nbStations);

#endif