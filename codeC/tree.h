/*
    Library for tree.h
*/


#ifndef TREE_HEADER
#define TREE_HEADER

#include "basics.h"

// Structures
typedef struct Station {
    uint32_t id;
    long consumption_sum;
    long capacity;
    uint8_t type; // STATION_HVB, STATION_HVA or STATION_LV
} Station;

typedef struct {
    pStation station;
    struct AVL *left;
    struct AVL *right;
    int balance;
} AVL;

typedef AVL* pAVL;
typedef Station* pStation;

pAVL insertAVL(pAVL a, pStation s, int* h);
pAVL createAVL(pStation s);
void cleanAVL(pAVL a);

/* A coder, Nathan :DDDDDDDD @_@ >.< *-*

Ouais tkt je fais bébou UwU (*＞ω＜*)♡ 👉👈

pAVL createAVL(Station s);
pAVL insertAVL(Station s);
pAVL deleteAVL(pAVL a, int *h, int *pe);
pAVL deleteMinAVL(pAVL a, int *h, int *pe);
pAVL deleteAVL(pAVL a, Station s, int *h);
pAVL equilibrateAVL(pAVL a);
pAVL rotateLeft(pAVL a);
pAVL rotateRight(pAVL a);
pAVL rotateDoubleLeft(pAVL a);
pAVL rotateDoubleRight(pAVL a);
void cleanAVL(pAVL a)

*/



#endif