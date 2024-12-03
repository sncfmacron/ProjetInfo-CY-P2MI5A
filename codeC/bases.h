/*
    Contient les tructures et bibliothèques de base
*/


#ifndef BASIC_H
#define BASIC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


#include "paramètres.h"

// Structures
typedef struct Station {
    uint64_t id;
    long somme_consommation;
    long capacite;
    char type[10];
} Station;

typedef struct {
    uint64_t id;
    long consommation;
    char type[20];
} Consommateur;

typedef struct {

    struct AVL *fg;
    struct AVL *fd;
    int equilibre;
} AVL;

typedef AVL* pAVL;







#endif