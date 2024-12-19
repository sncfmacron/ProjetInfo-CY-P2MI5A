/*
    main.c : main program
*/


#include "main.h"


int main(int argc, char* argv[]) {

    uint32_t nbStations = string_to_int(argv[3]);
    char* stationType = argv[1];
    char* consumerType = argv[2];

    // Managing the case where no power plant id is given
    argv[4] = (argv[4] != NULL) ? argv[4] : "EMPTY";
    char* powerPlantID = argv[4];

    verifyArguments(argc, stationType, consumerType, powerPlantID, nbStations);

    pStation* stationArray = malloc(nbStations * sizeof(pStation));
    if(stationArray == NULL) {
        exit_with_message("ERROR: Dynamic station array allocation failed", ERR_PTR_ALLOC);
    }

    pAVL tree = NULL;
    tree = processStation(DIR_STATION_SORTED, tree, stationArray);

    mergeSort(stationArray, nbStations);

    processConsumer(DIR_CONSUMER_SORTED, tree);

    outputProcess(stationType, consumerType, powerPlantID, stationArray, nbStations);
  
    return 0;
}