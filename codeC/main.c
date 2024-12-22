/*
    main.c: main program
*/


#include "main.h"

// Give global main arguments to use them across the main function (mainly used for the cleanup function)
pAVL globalTree = NULL;
pStation* stationArray = NULL;
pStation* mmArray = NULL;
uint32_t nbStations = 0;

// Cleanup function to free all allocated memory
void cleanup(void){
    if(stationArray != NULL){
        for (uint32_t i = 0; i < nbStations; i++){
            if(stationArray[i] != NULL){
                free(stationArray[i]);
            }
            stationArray[i] = NULL;
        }
        free(stationArray);
        stationArray = NULL;
    }
    if(mmArray != NULL){
        for (uint32_t i = 0; i < nbStations; i++){
            if(mmArray[i] != NULL){
                free(mmArray[i]);    
            }
            mmArray[i] = NULL;
        }
        free(mmArray);
        mmArray = NULL;
    }
    if(globalTree != NULL){
        cleanAVL(globalTree);   // call of the AVL free function
    }
}

int main(int argc, char* argv[]) {
    // start of the clock
    clock_t start = clock();

    // atexit call a function at an exit (even when main return 0). There is an exception when a forced exit (_exit) or a seg fault appear
    if (atexit(cleanup) != 0) {
        exit_with_message("Cannot register cleanup function", ERR_ATEXIT);
    }
    // Init variables for the given arguments
    nbStations = string_to_int(argv[3]);
    char* stationType = argv[1];
    char* consumerType = argv[2];
    
    // Managing the case where no power plant id is given
    argv[4] = (argv[4] != NULL) ? argv[4] : "EMPTY";
    char* powerPlantID = argv[4];
    
    verifyArguments(argc, stationType, consumerType, nbStations, powerPlantID);
    
    stationArray = malloc(nbStations * sizeof(pStation));
    if(stationArray == NULL) {
        exit_with_message("ERROR: Dynamic station array allocation failed", ERR_ARRAY_ALLOC);
    }
    
    // In case of LV all, create Min Max Array
    if(strcmp(consumerType, "all") == 0){
        mmArray = allocMinMax(consumerType, mmArray, nbStations);
    }
    
    // Create the AVL
    globalTree = NULL;
    globalTree = processStation(DIR_STATION_FILTERED, globalTree, stationArray, mmArray, consumerType);
    
    // Update load_sum
    processConsumer(DIR_CONSUMER_FILTERED, globalTree);
    
    // In case of LV all, sort the Min Max Array by overload
    if(strcmp(consumerType, "all") == 0){
        sortMinMax(consumerType, mmArray, stationArray, nbStations);
    }
    
    // Sort the stations by increasing capacity
    mergeSort(stationArray, nbStations);
    
    // Create the output files
    outputProcess(stationType, consumerType, powerPlantID, stationArray, mmArray, nbStations);

    // Display the time of the C program
    clock_t end = clock();
    displayTime(start, end, "...2. Writing the output data completed successfully");
    
    return 0;
}