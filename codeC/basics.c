/*
    Basic functions
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
       return 1;
    }
}


pStation createStation(int power_plant_id, int station_id, long capacity, int stationType) {

    pStation s = malloc(sizeof(Station));
    if(s == NULL){
        exit_with_message("ERROR: Sation allocation failed", 2);
    }
    s->linked_power_plant = power_plant_id;
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