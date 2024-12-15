/*
    Library for tree management
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

#endif

/*
pAVL deleteAVL(pAVL a, int *h, int *pe);
pAVL deleteMinAVL(pAVL a, int *h, int *pe);
pAVL deleteAVL(pAVL a, pStation s, int *h);
pAVL equilibrateAVL(pAVL a);
pAVL rotateLeft(pAVL a);
pAVL rotateRight(pAVL a);
pAVL rotateDoubleLeft(pAVL a);
pAVL rotateDoubleRight(pAVL a);
*/

