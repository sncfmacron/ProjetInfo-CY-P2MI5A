/*
    basic.c: basic functions
*/


#include "basics.h"


// Exit program with an error message
// We use 'const char *' to prevent modifying the string
void exit_with_message(const char *message, int error_code) {
    printf("%s\n", message);
    exit(error_code);
}

// Verify all main() arguments 
void verifyArguments(int argc, char* stationType, char* consumerType, uint32_t nbStations, char* powerPlantID) {
    if (argc < 3) {
        exit_with_message("ERROR: Not enough parameters provided.", ERR_INVALID_ARGS);
    }

    if(stationType == NULL) {
        exit_with_message("ERROR: Invalid station type.", ERR_INVALID_ARGS);
    }

    if(consumerType == NULL) {
        exit_with_message("ERROR: Invalid consumer type.", ERR_INVALID_ARGS);
    }

    if(nbStations < 1) {
        exit_with_message("ERROR: Number of stations is invalid.", ERR_INVALID_ARGS);
    }

    if(powerPlantID == NULL) {
        exit_with_message("ERROR: Invalid power plant ID.", ERR_INVALID_ARGS);
    }
}


// Transforms string to int
int string_to_int(const char* string) {
    if(string == NULL) {
        return 0;
    } else {
        return atoi(string);    // ASCII to integer (atoi)
    }
}

// Displays execution time of a function
void displayTime(clock_t start, clock_t end, char* message) {
    if(message == NULL){
        exit_with_message("ERROR: NULL message pointer", ERR_NULL_POINTER);
    }
    if(end < start){
        exit_with_message("ERROR: Invalid clock", ERR_TIME_CLOCK);
    }
    
    // 'double' for more decimal precision and 'CLOCKS_PER_SEC' to convert time to seconds
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;

    // To avoid displaying a negative number when processing too fast
    if(seconds < 0) {
        seconds = 0;
    }

    printf("\n%s in %.2fs.\n", message, seconds);
}

// Creates a station and return it as a pointer
pStation createStation(int station_id, long capacity) {
    if(station_id < 1 || capacity < 1){
        exit_with_message("ERROR: Invalid station init arguments", ERR_INVALID_ARGS);
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

// Maximum of 3 variables
int max3(int a, int b, int c) {
    int max = (a > b) ? a : b;
    return (max > c) ? max : c;
}

// Minimum of 3 variables
int min3(int a, int b, int c) {
    int min = (a < b) ? a : b;
    return (min < c) ? min : c;
}

// Max of 2 variables
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Min of 2 variables
int min(int a, int b) {
    return (a < b) ? a : b;
}

// sort and merge the tabs into the array, in order of capacity
void merge(pStation* stationArray, uint32_t start, uint32_t middle, uint32_t end){
    if(stationArray == NULL){
        exit_with_message("ERROR: Stations array is NULL", ERR_NULL_ARRAY);
    }

    uint32_t temp_size = end - start + 1; // Calculate size of the temporary array correctly
    pStation* temp = malloc(temp_size * sizeof(pStation));
    if(temp == NULL){
        exit_with_message("ERROR: Temporary station array allocation failed", ERR_PTR_ALLOC);
    }
    // init of the variables: 
    // i for the loop, indexA to search through the first part of the array and indexB the second part
    uint32_t i, indexA = start, indexB = middle + 1;

    // Copy the first half of the array into temp
    for(i = start; i <= middle; i++){
        temp[i - start] = stationArray[i];  // Local indexA
    }

    // Copy the second half of the array into temp
    for(i = middle + 1; i <= end; i++){
        temp[i - start] = stationArray[i];  // Local indexB
    }

    // Sort and merge the two halves back into the original array in order of capacity
    i = start;  // Start index for the merge process
    while(indexA <= middle && indexB <= end){
        // if the first half capacity is inferior or equal to the second half: copy first half into the original array
        if(temp[indexA - start]->capacity <= temp[indexB - start]->capacity){
            stationArray[i] = temp[indexA - start];
            indexA++;
        }
        // if not, copy second half into the original array
        else{
            stationArray[i] = temp[indexB - start];
            indexB++;
        }
        i++;
    }

    // Copy the remaining elements in the first half
    while(indexA <= middle){
        stationArray[i] = temp[indexA - start];
        indexA++;
        i++;
    }

    // Copy the remaining elements in the second half
    while(indexB <= end){
        stationArray[i] = temp[indexB - start];
        indexB++;
        i++;
    }

    free(temp);
}

// Recursive part of the merge sort function (isolate array into small one before merging and sorting them)
void mergeSortRecursive(pStation* stationArray, uint32_t start, uint32_t end){
    if(stationArray == NULL){
        exit_with_message("ERROR: Stations array is NULL", ERR_NULL_ARRAY);
    }
    uint32_t middle;
    if(start < end){
        middle = (start + end) / 2;
        // divide the array in two part:
        mergeSortRecursive(stationArray, start, middle);    // left part (doing it recursively)
        mergeSortRecursive(stationArray, middle+1, end);    // right part (doing it recursively)
        
        // when divided into single instances -> sort and merge into bigger instances until the array is complete
        merge(stationArray, start, middle, end);
    }
}

// Init of the merge Sort function
void mergeSort(pStation* stationArray, uint32_t nbStations){
    if(stationArray == NULL){
        exit_with_message("ERROR: Stations array is NULL", ERR_NULL_ARRAY);
    }
    if(nbStations < 1){
        exit_with_message("ERROR: Number of stations is invalid.", ERR_INVALID_ARGS);
    }
    // first call of the recursive function after the init
    mergeSortRecursive(stationArray, 0, nbStations-1);
}

// Allocation of the Min Max Array (mmArray) for 'lv all'
pStation* allocMinMax(char* consumerType, pStation* mmArray, uint32_t nbStations){
    if(nbStations < 1){
        exit_with_message("ERROR: Number of stations is invalid.", ERR_INVALID_ARGS);
    }
    // no need to verify if 'lv' == TRUE since only LV station can have the consumer type of 'all'
    if(strcmp(consumerType, "all") == 0){
        mmArray = malloc(nbStations * sizeof(pStation));
        if(mmArray == NULL){
            exit_with_message("ERROR: Dynamic min max array allocation failed", ERR_ARRAY_ALLOC);
        }
    }
    return mmArray;
}

// Init and sort Min Max Array to get the increasing order of the stations sorted by overload (capacity - load_sum)
void sortMinMax(char* consumerType, pStation* mmArray, pStation* stationArray, uint32_t nbStations){
    if(mmArray == NULL){
        exit_with_message("ERROR: Stations min max array is NULL", ERR_NULL_ARRAY);
    }
    if(stationArray == NULL){
        exit_with_message("ERROR: Stations array is NULL", ERR_NULL_ARRAY);
    }
    if(nbStations < 1){
        exit_with_message("ERROR: Number of stations is invalid.", ERR_INVALID_ARGS);
    }
    
    if(strcmp(consumerType, "all") == 0){
        // Init of the mmArray capacity
        for(uint32_t i = 0; i < nbStations; i++){
            mmArray[i]->capacity = mmArray[i]->capacity - stationArray[i]->load_sum;
        }
        // Merge of the mmArray to the stations sorted order of overload 
        mergeSort(mmArray, nbStations);
    }
}