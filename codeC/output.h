/*
    output.c : library for output.c
*/


#ifndef OUTPUT_HEADER
#define OUTPUT_HEADER

typedef struct AVL_struct AVL;
typedef AVL* pAVL;

#include "basics.h"

const char* typeToPrint(const char* type);
void createPath(const char* stationType, const char* consumerType, const char* powerPlantID, char* path, int sizePath);
FILE* initOutputFile(const char* stationType, const char* consumerType, const char* powerPlantID);
void writeOutputFile(pStation* stations, FILE* file, uint32_t nbStations);
FILE* initLvMinMax(FILE* file);
void writeOutputLvMinMax(FILE* file, pStation* stationArray, pStation* mmArray, uint32_t nbStations);
void outputProcess(const char* stationType, const char* consumerType, const char* powerPlantID, pStation* stations, uint32_t nb_stations, pStation* mmArray);

#endif