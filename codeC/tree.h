/*
    tree.h: library for tree.h
*/


#ifndef TREE_HEADER
#define TREE_HEADER

#include "basics.h"

// Structures
typedef struct Station_struct {
    uint32_t id;
    long capacity;
    long load_sum;
} Station;

typedef struct AVL_struct {
    Station* station;
    struct AVL_struct *left;
    struct AVL_struct *right;
    int balance;
} AVL;

// Typedef for easier understanding of the code
typedef AVL* pAVL;
typedef Station* pStation;

// Functions declaration
void updateSum(pAVL a, uint32_t stationID, long load);
pAVL createAVL(pStation s);
pAVL leftRotation(pAVL a);
pAVL rightRotation(pAVL a);
pAVL balanceAVL(pAVL a);
pAVL insertAVL(pAVL a, pStation s, int* h);
void cleanAVL(pAVL a);

#endif