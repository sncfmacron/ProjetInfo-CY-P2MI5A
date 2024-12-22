/*
    main.c : main program
*/


#include "main.h"

pAVL globalTree = NULL;
pStation* stationArray = NULL;
pStation* mmArray = NULL;
uint32_t nbStations = 0;

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
        cleanAVL(globalTree);
    }
}

void allocMinMax(char* consumerType){
    if(strcmp(consumerType, "all") == 0){
        mmArray = malloc(nbStations * sizeof(pStation));
        if(mmArray == NULL){
            exit_with_message("ERROR: Dynamic min max array allocation failed", ERR_PTR_ALLOC);
        }
    }
}

void sortMinMax(char* consumerType){
    if(strcmp(consumerType, "all") == 0){
        if(mmArray == NULL){
            exit_with_message("ERROR: Station min max array is NULL", 123);
        }
        for(uint32_t i = 0; i < nbStations; i++){
            mmArray[i]->capacity = mmArray[i]->capacity - stationArray[i]->load_sum;
        }
    }
}

int main(int argc, char* argv[]) {
    if (atexit(cleanup) != 0) {
        fprintf(stderr, "Cannot register cleanup function\n");
        return 1;
    }
    
    nbStations = string_to_int(argv[3]);
    char* stationType = argv[1];
    char* consumerType = argv[2];
    
    // Managing the case where no power plant id is given
    argv[4] = (argv[4] != NULL) ? argv[4] : "EMPTY";
    char* powerPlantID = argv[4];
    
    verifyArguments(argc, stationType, consumerType, powerPlantID, nbStations);
    
    stationArray = malloc(nbStations * sizeof(pStation));
    if(stationArray == NULL) {
        exit_with_message("ERROR: Dynamic station array allocation failed", ERR_PTR_ALLOC);
    }
    
    if(strcmp(consumerType, "all") == 0){
        allocMinMax(consumerType);
    }
    
    globalTree = NULL;
    globalTree = processStation(DIR_STATION_SORTED, globalTree, stationArray, mmArray, consumerType);
    
    processConsumer(DIR_CONSUMER_SORTED, globalTree);
    
    if(strcmp(consumerType, "all") == 0){
        sortMinMax(consumerType);
    }
    
    mergeSort(stationArray, nbStations);
    
    outputProcess(stationType, consumerType, powerPlantID, stationArray, nbStations, mmArray);
    
    return 0;
}