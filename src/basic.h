/*
basic.h
Basic structures and functions for the program
*/

#ifndef BASIC_H
#define BASIC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <unistd.h>


#include "settings.h"

// Structures
typedef struct Station {
    uint64_t id;
    long somme_consommation;
    long capacite;              // Quantité d’énergie produite par une centrale ou transférée par une station HV-B, HV-A ou LV (en kWh)
    char type[10];              // HV-B, HVA, LV, CENTRALE
} Station;

typedef struct {
    uint64_t id;
    long consommation;
    char type[20];              // entreprise, particulier
} Consommateur;

typedef struct {
    void* data;                 // Pointeur générique : peut être une station ou un consommateur
    struct AVL *fg;
    struct AVL *fd;
    int equilibre;
} AVL;

typedef AVL* pAVL;







#endif