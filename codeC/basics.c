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


void verifyArguments(int argc, char* stationType, char* consumerType, char* powerPlantID, uint32_t nbStations) {
    if (argc < 3) {
        exit_with_message("ERROR: Not enough parameters provided.", ERR_INVALID_ARGS);
    }

    if(stationType == NULL) {
        exit_with_message("ERROR: Invalid station type.", ERR_INVALID_ARGS);
    }

    if(consumerType == NULL) {
        exit_with_message("ERROR: Invalid consumer type.", ERR_INVALID_ARGS);
    }

    if(powerPlantID == NULL) {
        exit_with_message("ERROR: Invalid power plant ID.", ERR_INVALID_ARGS);
    }
    if(nbStations < 1) {
        exit_with_message("ERROR: Number of stations is invalid.", ERR_INVALID_ARGS);
    }
}


// Transforms string to int
int string_to_int(const char* string) {
    if(string == NULL) {
        return 0;
    } else {
        return atoi(string);
    }
}

// Displays execution time of a function
void displayTime(clock_t start, clock_t end, char* message) {
    if(message == NULL){
        exit_with_message("ERROR: NULL message pointer", 2);
    }
    if(end < start){
        exit_with_message("ERROR: Invalid clock", 12);
    }
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;

    // To avoid displaying a negative number when processing too fast
    if(seconds < 0) {
        seconds = 0;
    }

    printf("\n%s in %.2fs.\n", message, seconds);
}

// Creates a station pointer
pStation createStation(int station_id, long capacity) {
    if(station_id < 1 || capacity < 1){
        exit_with_message("ERROR: Invalid station init arguments", 233);
    }

    pStation s = malloc(sizeof(Station));
    if(s == NULL){
        exit_with_message("ERROR: Station allocation failed.", ERR_PTR_ALLOC);
    }

    s->id = station_id;
    s->capacity = capacity;
    s->load_sum = 0;

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

void merge(pStation* stationArray, uint32_t start, uint32_t middle, uint32_t end){
    if(stationArray == NULL){
        exit_with_message("ERROR: Stations array is NULL", 32);
    }

    uint32_t temp_size = end - start + 1; // Calculate size correctly
    pStation* temp = malloc(temp_size * sizeof(pStation));
    if(temp == NULL){
        exit_with_message("ERROR: Temporary station array allocation failed", ERR_PTR_ALLOC);
    }

    uint32_t i, indexA = start, indexB = middle + 1;

    // Copy the first half of the array into temp
    for(i = start; i <= middle; i++){
        temp[i - start] = stationArray[i];  // Use a local index in temp
    }

    // Copy the second half of the array into temp
    for(i = middle + 1; i <= end; i++){
        temp[i - start] = stationArray[i];  // Use a local index in temp
    }

    // Merge the two halves back into the original array
    i = start;  // Start index for the merge process
    while(indexA <= middle && indexB <= end){
        if(temp[indexA - start]->capacity <= temp[indexB - start]->capacity){
            stationArray[i] = temp[indexA - start];
            indexA++;
        } else{
            stationArray[i] = temp[indexB - start];
            indexB++;
        }
        i++;
    }

    // Copy any remaining elements in the first half
    while(indexA <= middle){
        stationArray[i] = temp[indexA - start];
        indexA++;
        i++;
    }

    // Copy any remaining elements in the second half
    while(indexB <= end){
        stationArray[i] = temp[indexB - start];
        indexB++;
        i++;
    }

    free(temp);
}


void mergeSortRecursive(pStation* stationArray, uint32_t start, uint32_t end){
    if(stationArray == NULL){
        exit_with_message("ERROR: Stations array is NULL", 9999);
    }
    uint32_t middle;
    if(start < end){
        middle = (start + end) / 2;
        mergeSortRecursive(stationArray, start, middle);
        mergeSortRecursive(stationArray, middle+1, end);
        merge(stationArray, start, middle, end);
    }
}


void mergeSort(pStation* stationArray, uint32_t nbStations){
    if(stationArray == NULL){
        exit_with_message("ERROR: Stations array is NULL", 99999);
    }
    if(nbStations < 1){
        exit_with_message("ERROR: Number of stations is invalid.", ERR_INVALID_ARGS);
    }

    mergeSortRecursive(stationArray, 0, nbStations-1);
}

pStation* allocMinMax(char* consumerType, pStation* mmArray, uint32_t nbStations){
    if(nbStations < 1){
        exit_with_message("ERROR: Number of stations is invalid.", ERR_INVALID_ARGS);
    }

    if(strcmp(consumerType, "all") == 0){
        mmArray = malloc(nbStations * sizeof(pStation));
        if(mmArray == NULL){
            exit_with_message("ERROR: Dynamic min max array allocation failed", ERR_PTR_ALLOC);
        }
    }
    return mmArray;
}

void sortMinMax(char* consumerType, pStation* mmArray, pStation* stationArray, uint32_t nbStations){
    if(mmArray == NULL){
        exit_with_message("ERROR: Stations min max array is NULL", 99999);
    }
    if(stationArray == NULL){
        exit_with_message("ERROR: Stations array is NULL", 99999);
    }
    if(nbStations < 1){
        exit_with_message("ERROR: Number of stations is invalid.", ERR_INVALID_ARGS);
    }
    
    if(strcmp(consumerType, "all") == 0){
        if(mmArray == NULL){
            exit_with_message("ERROR: Station min max array is NULL", 123);
        }
        for(uint32_t i = 0; i < nbStations; i++){
            mmArray[i]->capacity = mmArray[i]->capacity - stationArray[i]->load_sum;
        }
    }
    mergeSort(mmArray, nbStations);
}