/*
    Basic functions and tree management
*/


#include "basics.h"


// Exit program with an error message
void exit_with_message(const char *message, int error_code) {
    printf("%s\n", message);
    exit(error_code);
}


int getStationType(const char *station) {
    if(strcmp(station, "hvb") == 0) {
        return STATION_HVB;
    }
    else if(strcmp(station, "hva") == 0) {
        return STATION_HVA;
    }
    else if(strcmp(station, "lv") == 0) {
        return STATION_LV;
    }
    else {
       exit_with_message("ERROR: Unrecognised station", 1);
    }
}


pStation createStation(int centrale_id, int station_id, long capacity, int stationType) {

    pStation s = malloc(sizeof(Station));
    if(s == NULL){
        exit_with_message("ERROR: Sation allocation failed", 2);
    }
    s->linked_central = centrale_id;
    s->id = station_id;
    s->capacity = capacity;
    s->type = stationType;

    return s;
}


int max3(int a, int b, int c) {
    int max = a;

    if (b > max) {
        max = b;
    }
    if (c > max) {
        max = c;
    }
    return max;
}


int min3(int a, int b, int c) {
    int min = a;

    if (b < min) {
        min = b;
    }
    if (c < min) {
        min = c;
    }
    return min;
}


int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}


int min(int a, int b) {
    if(a > b) {
        return b;
    } else {
        return a;
    }
}

pAVL createAVL(pStation s) {
    if(s == NULL){
        exit_with_message("ERROR: NULL pointer", 3);
    }
    pAVL a = malloc(sizeof(AVL));
    if(a == NULL)
    {
        exit_with_message("ERROR: AVL allocation failed.", 4);
    }

    a->station = s;
    a->left = NULL;
    a->right = NULL;
    a->balance = 0;
    return a;
}

pAVL insertAVL(pAVL a, pStation s){
    if(s == NULL){
        exit_with_message("ERROR: Station doesn't exist", 5);
    }

    if(a == NULL){
        return createAVL;
    }
    else if(s->id < a->station->id){
        a->left=insertAVL(a->left, s);
    }
    else if(s->id > a->station->id){
        a->right=insertAVL(a->right, s);
    }
    return s;
}



void cleanAVL(pAVL a) {
    if(a == NULL)
    {
        return;
    }

    free(a->left);
    free(a->right); // EDIT : faire une fonction recursive je pense free(a-left) -> cleanAVL(a->left)

    free(a);
}