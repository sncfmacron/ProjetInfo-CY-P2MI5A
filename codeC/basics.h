/*
    Contains the basic structures and libraries
*/


#ifndef BASIC_HEADER
#define BASIC_HEADER

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "settings.h"
#include "input.h"
#include "output.h"
#include "calculations.h"


// Structures
typedef struct Station {
    uint8_t linked_central;
    uint32_t id;
    long consumption_sum;
    long capacity;
    uint8_t type; // STATION_HVB, STATION_HVA or STATION_LV
} Station;

typedef struct {
    uint32_t linked_station;
    long id;
    unsigned long consumption;
} Consumer;

typedef struct {
    pStation station;
    struct AVL *left;
    struct AVL *right;
    int balance;
} AVL;

typedef AVL* pAVL;
typedef Station* pStation;

// Functions declaration
void exit_with_message(const char *message, int error_code);
int getStationType(const char *station);
pStation createStation(int centrale_id, int station_id, long capacity, int stationType);

// pAVL createAVL(Station s);
// pAVL insertionAVL(pAVL a, Station s, int *h);
/* A coder, Nathan :DDDDDDDD

pAVL deleteAVL(pAVL a, int *h, int *pe);
pAVL deleteMinAVL(pAVL a, int *h, int *pe);
pAVL deleteAVL(pAVL a, Station s, int *h);
pAVL equilibrateAVL(pAVL a);
pAVL rotateLeft(pAVL a);
pAVL rotateRight(pAVL a);
pAVL rotateDoubleLeft(pAVL a);
pAVL rotateDoubleRight(pAVL a);

*/
void cleanAVL(pAVL a);

int max(int a, int b);
int max3(int a, int b, int c);
int min(int a, int b);
int min3(int a, int b, int c);


#endif