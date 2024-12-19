/*
    tree.h : library for tree.h
*/


#ifndef TREE_HEADER
#define TREE_HEADER

#include "basics.h"

// Structures
typedef struct Station_struct {
    uint32_t id;
    long consumption_sum;
    long capacity;
} Station;

typedef struct AVL_struct {
    Station* station;
    struct AVL_struct *left;
    struct AVL_struct *right;
    int balance;
} AVL;

typedef AVL* pAVL;
typedef Station* pStation;

void updateSum(pAVL a, uint32_t stationID, long load);
pAVL insertAVL(pAVL a, pStation s, int* h);
pAVL createAVL(pStation s);
pAVL leftRotation(pAVL a);
pAVL rightRotation(pAVL a);
pAVL balanceAVL(pAVL a);
void cleanAVL(pAVL a);

#endif