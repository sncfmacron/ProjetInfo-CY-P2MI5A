/*
    Library for tree.h
*/


#ifndef TREE_HEADER
#define TREE_HEADER

#include "basics.h"

// Structures
typedef struct Station_struct {
    uint32_t id;
    long consumption_sum;
    long capacity;
    uint8_t type; // STATION_HVB, STATION_HVA or STATION_LV
}Station;

typedef struct AVL_struct {
    Station* station;
    struct AVL_struct *left;
    struct AVL_struct *right;
    int balance;
}AVL;

typedef AVL* pAVL;
typedef Station* pStation;

pAVL insertAVL(pAVL a, pStation s, int* h);
pAVL createAVL(pStation s);
void cleanAVL(pAVL a);
pAVL leftRotation(pAVL a);
pAVL rightRotation(pAVL a);
pAVL balanceAVL(pAVL a);

#endif

/*
pAVL deleteAVL(pAVL a, int *h, int *pe);
pAVL deleteMinAVL(pAVL a, int *h, int *pe);
pAVL rotateDoubleLeft(pAVL a);
pAVL rotateDoubleRight(pAVL a);
*/

