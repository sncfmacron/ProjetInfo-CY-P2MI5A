/*
    Basic functions
*/


#include "basics.h"


// Exit program with an error message
void exit_with_message(const char *message, int error_code) {
    printf("%s\n", message);
    exit(error_code);
}


// Function to get the type of station
// We use "const char *" to prevent modifying the string
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
       exit_with_message("ERROR: unrecognised station.", ERROR_INVALID_STATION_TYPE);
       return 1;
    }
}

// Function to get the type of consumer
int getConsumerType(const char *consumer) {
    if(strcmp(consumer, "indiv") == 0) {
        return CONSUMER_INDIV;
    }
    else if(strcmp(consumer, "comp") == 0) {
        return CONSUMER_COMP;
    }
    else if(strcmp(consumer, "all") == 0) {
        return CONSUMER_ALL;
    }
    else {
       exit_with_message("ERROR: unrecognised consumer.", ERROR_INVALID_CONSUMER_TYPE);
       return 1;
    }
}


pStation createStation(int station_id, long capacity, int stationType) {

    pStation s = malloc(sizeof(Station));
    if(s == NULL){
        exit_with_message("ERROR: station allocation failed.", ERROR_PTR_ALLOC);
    }
    s->id = station_id;
    s->capacity = capacity;
    s->type = stationType;
    s->consumption_sum = 0;

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