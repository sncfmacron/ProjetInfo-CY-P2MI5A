/*
    basic.c : basic functions
*/


#include "basics.h"


// Exit program with an error message
// We use 'const char *' to prevent modifying the string
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


// Creates a station pointer
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


// These functions are used to retrieve the maximum of variables
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

void merge(pStation* stations, uint32_t start, uint32_t middle, uint32_t end){
    uint32_t temp_size = end - start + 1; // Calculate size correctly
    pStation* temp = malloc(temp_size * sizeof(pStation));
    if(temp == NULL){
        exit_with_message("ERROR: Temporary station array allocation failed", 666);
    }

    uint32_t i, indexA = start, indexB = middle + 1;

    // Copy the first half of the array into temp
    for(i = start; i <= middle; i++){
        temp[i - start] = stations[i];  // Use a local index in temp
    }

    // Copy the second half of the array into temp
    for(i = middle + 1; i <= end; i++){
        temp[i - start] = stations[i];  // Use a local index in temp
    }

    // Merge the two halves back into the original array
    i = start;  // Start index for the merge process
    while(indexA <= middle && indexB <= end){
        if(temp[indexA - start]->capacity <= temp[indexB - start]->capacity){
            stations[i] = temp[indexA - start];
            indexA++;
        } else{
            stations[i] = temp[indexB - start];
            indexB++;
        }
        i++;
    }

    // Copy any remaining elements in the first half
    while(indexA <= middle){
        stations[i] = temp[indexA - start];
        indexA++;
        i++;
    }

    // Copy any remaining elements in the second half
    while(indexB <= end){
        stations[i] = temp[indexB - start];
        indexB++;
        i++;
    }

    free(temp);
}

void mergeSortRecursive(pStation* stations, uint32_t start, uint32_t end){
    if(stations == NULL){
        exit_with_message("ERROR: Stations array is NULL", 9999);
    }
    uint32_t middle;
    if(start < end){
        middle = (start + end) / 2;
        mergeSortRecursive(stations, start, middle);
        mergeSortRecursive(stations, middle+1, end);
        merge(stations, start, middle, end);
    }
}

void mergeSort(pStation* stations, uint32_t nb_stations){
    if(stations == NULL){
        exit_with_message("ERROR: Stations array is NULL", 99999);
    }
    mergeSortRecursive(stations, 0, nb_stations-1);
}