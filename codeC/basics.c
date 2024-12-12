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
    else {
       return STATION_LV; 
    }
}


Station createStation(int centrale_id, int station_id, long capacity, int stationType) {

    Station s;
    s.linked_central = centrale_id;
    s.id = station_id;
    s.capacity = capacity;
    s.type = stationType;

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


void cleanAVL(pAVL a) {
    if(a == NULL)
    {
        return;
    }

    free(a->left);
    free(a->right);

    free(a);
}