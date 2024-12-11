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
    unsigned long consumption_sum;
    unsigned long capacity;
    char type[MAX_STATION_TYPE]; // HVA, HVB or LV
} Station;

typedef struct {
    uint32_t linked_station;
    long id;
    unsigned long consumption;
} Consumer;

typedef struct {
    Station station;
    struct AVL *left;
    struct AVL *right;
    int balance;
} AVL;

typedef AVL* pAVL;

void exit_with_message(const char *message, int error_code);

pAVL createAVL(Station s);
pAVL insertionAVL(pAVL a, Station s, int *h);
/* A coder Nathan :DDDDD

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

int max3(int a, int b, int c);
int min3(int a, int b, int c);
int max(int a, int b);
int min(int a, int b);


#endif