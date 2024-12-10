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
    long consumption_sum;
    long capacity;
    char type[10]; // HVA, HVB or LV
} Station;

typedef struct {
    uint32_t id;
    long consumption;
} Consumer;

typedef struct {
    Station station;
    struct AVL *left;
    struct AVL *right;
    int balance;
} AVL;

typedef AVL* pAVL;

#endif