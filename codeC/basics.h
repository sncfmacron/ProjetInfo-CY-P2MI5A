/*
    basics.h : contains the basic structures and libraries
*/


#ifndef BASIC_HEADER
#define BASIC_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


// Early declaration of the Station type for use across the program
typedef struct Station_struct Station;
typedef Station* pStation;


#include "input.h"
#include "output.h"
#include "settings.h"
#include "tree.h"


// Functions declaration
void exit_with_message(const char *message, int error_code);
void verifyArguments(int argc, char* stationType, char* consumerType, char* powerPlantID, uint32_t nbStations);
int getStationType(const char *station);
void displayTime(clock_t start, clock_t end, char* message);
pStation createStation(int station_id, long capacity);

int string_to_int(const char* string);

int max3(int a, int b, int c);
int min3(int a, int b, int c);
int max(int a, int b);
int min(int a, int b);

void merge(pStation* stations, uint32_t start, uint32_t middle, uint32_t end);
void mergeSortRecursive(pStation* stations, uint32_t start, uint32_t end);
void mergeSort(pStation* stations, uint32_t nb_stations);

pStation* allocMinMax(char* consumerType, pStation* mmArray, uint32_t nbStations);
void sortMinMax(char* consumerType, pStation* mmArray, pStation* stationArray, uint32_t nbStations);

#endif