/*
    Contains the basic structures and libraries
*/

#ifndef BASIC_H
#define BASIC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "parameters.h"


// Structures
typedef struct Station {
    uint32_t id;
    unsigned long consumption_sum;
    unsigned long capacity;
    char type[MAX_STATION_TYPE]; // HVA, HVB or LV
} Station;

typedef struct {
    long id;
    unsigned long consumption;
} Consumer;

typedef struct {
    Station station;
    struct AVL *left;
    struct AVL *right;
    int balance; //  on verra
} AVL;

typedef AVL* pAVL;

void exit_with_message(const char *message, int error_code);

pAVL createAVL(Station s);
pAVL insertionAVL(pAVL a, Station s, int *h);
/* A coder

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