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
            if (stationArray[i] != NULL){
                free(stationArray[i]);
            }
            stationArray[i] = NULL;
        }
        free(stationArray);
        stationArray = NULL;
    }
    if(mmArray != NULL){
        for (uint32_t i = 0; i < nbStations; i++){
            mmArray[i] = NULL;
        }
        free(mmArray);
        mmArray = NULL;
    }
    if(globalTree != NULL){
        cleanAVL(globalTree);
    }
}

void sortMinMax(char* stationType, char* consumerType){
    if((strcmp(stationType, "lv") == 0) && (strcmp(consumerType, "all") == 0)){
        mmArray = malloc(nbStations * sizeof(pStation));
        if(mmArray == NULL){
            exit_with_message("ERROR: Dynamic min max array allocation failed", ERR_PTR_ALLOC);
        }
        for(uint32_t i = 0; i < nbStations; i++){
            mmArray[i] = stationArray[i];
            mmArray[i]->capacity = mmArray[i]->capacity - mmArray[i]->load_sum;
        }
        mergeSort(mmArray, nbStations);
    }
}

int main(int argc, char* argv[]) {

    clock_t start = clock();

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
    // if(strcmp(stationType, "lv") == 0){
        
    // }

    verifyArguments(argc, stationType, consumerType, powerPlantID, nbStations);

    stationArray = malloc(nbStations * sizeof(pStation));
    if(stationArray == NULL) {
        exit_with_message("ERROR: Dynamic station array allocation failed", ERR_PTR_ALLOC);
    }

    globalTree = NULL;
    globalTree = processStation(DIR_STATION_SORTED, globalTree, stationArray);
    
    mergeSort(stationArray, nbStations);
    
    processConsumer(DIR_CONSUMER_SORTED, globalTree);
    
    if((strcmp(stationType, "lv") == 0) && (strcmp(consumerType, "all") == 0)){
        sortMinMax(stationType, consumerType);
    }

    outputProcess(stationType, consumerType, powerPlantID, stationArray, nbStations, mmArray);

    clock_t end = clock();
    displayTime(start, end, "...2. Processing data completed");

    return 0;
}