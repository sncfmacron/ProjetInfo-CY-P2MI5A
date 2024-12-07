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
    uint64_t id;
    long consumption_sum;
    long capacity;
    char type[10];
} Station;

typedef struct {
    uint64_t id;
    long consumption;
    char type[20];
} Consumer;

typedef struct {
    struct AVL *left;
    struct AVL *right;
    int balance;
} AVL;

typedef AVL* pAVL;

#endif