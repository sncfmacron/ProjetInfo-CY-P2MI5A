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
    if(string == NULL) {
        // If station id is not given, 0 is returned by default because the string is null
        return 0;
    } else {
        return atoi(string);
    }
}


// Transforms string to long
long string_to_long(const char *string) {
    if (string == NULL) {
        exit_with_message("ERROR: string to long conversion failed.", ERR_INVALID_STRING);
    }

    char *endptr;
    long result = strtol(string, &endptr, 10);

    if (*endptr != '\0') {
        exit_with_message("ERROR: string to long conversion failed.", ERR_INVALID_STRING);
    }
    return result;
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


// Function to get the type of station to process
// We use "const char *" to prevent modifying the string

// --- A PEUT ETRE SUPPRIMER ---
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
       exit_with_message("ERROR: unrecognised station.", ERR_INVALID_STATION_TYPE);
       return 1;
    }
}


// --- A PEUT ETRE SUPPRIMER ---
// Function to get the type of consumer to process
int getConsumerType(const char *consumer) {
    if(strcmp(consumer, "comp") == 0) {
        return CONSUMER_COMP;
    }
    else if(strcmp(consumer, "indiv") == 0) {
        return CONSUMER_INDIV;
    }
    else if(strcmp(consumer, "all") == 0) {
        return CONSUMER_ALL;
    }
    else {
       exit_with_message("ERROR: unrecognised consumer.", ERR_INVALID_CONSUMER_TYPE);
       return 1;
    }
}


// Function to create a station
pStation createStation(int station_id, long capacity) {

    pStation s = malloc(sizeof(Station));
    if(s == NULL){
        exit_with_message("ERROR: station allocation failed.", ERR_PTR_ALLOC);
    }
    s->id = station_id;
    s->capacity = capacity;
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