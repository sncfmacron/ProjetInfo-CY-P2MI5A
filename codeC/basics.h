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

#include "calculations.h"
#include "input.h"
#include "output.h"
#include "settings.h"
#include "tree.h"


// Structures
typedef struct Station {
    uint8_t linked_power_plant;
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
    Station station;
    struct AVL *left;
    struct AVL *right;
    int balance;
} AVL;

typedef AVL* pAVL;
typedef Station* pStation;


// Functions declaration
void exit_with_message(const char *message, int error_code);
int getStationType(const char *station);
pStation createStation(int power_plant_id, int station_id, long capacity, int stationType);

int max(int a, int b);
int max3(int a, int b, int c);
int min(int a, int b);
int min3(int a, int b, int c);


#endif