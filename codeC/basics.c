/*
    Basic functions
*/


#include "basics.h"


// Exit program with an error message
void exit_with_message(const char *message, int error_code) {
    printf("%s\n", message);
    exit(error_code);
}


// Transforms string to int
int string_to_int(const char* string) {
    if(string == 0) {
        exit_with_message("ERROR: string to int conversion failed.", ERROR_INVALID_STRING);
    }

    return atoi(string);
}


// Transforms string to long
long string_to_long(const char* string) {
    char *endptr;
    long value = strtol(string, &endptr, 10);

    // An error has occurred if endptr does not point to '\0'.
    if (*endptr != '\0') {
        exit_with_message("ERROR: string to long conversion failed.", ERROR_INVALID_STRING);
    }

    return value;
}


// Gives time elapsed (using 'time.h')
float getTime(clock_t start, clock_t end) {
    float seconds = (float)(end - start) / CLOCKS_PER_SEC;

    // Pour éviter d'afficher un nombre négatif quand traitement instant comme -00.00s
    if(seconds < 0) {
        return 0;
    } else {
        return seconds;
    }
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
    int max = (a > b) ? a : b;
    return (max > c) ? max : c;
}


int min3(int a, int b, int c) {
    int min = (a < b) ? a : b;
    return (min < c) ? min : c;
}


int max(int a, int b) {
    return (a > b) ? a : b;
}


int min(int a, int b) {
    return (a < b) ? a : b;
}