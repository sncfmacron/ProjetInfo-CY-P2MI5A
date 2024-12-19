/*
    main.c : main program
*/


#include "main.h"


int main(int argc, char* argv[]) {

    if (argc < 3) {
        exit_with_message("ERROR: Not enough parameters provided.", ERR_COMPILATION);
    }

    pAVL tree = NULL;

    uint32_t nb_stations = string_to_int(argv[3]);
    char* stationType = argv[1];
    char* consumerType = argv[2];

    // Gestion du cas où on donne pas d'id de centrale
    argv[4] = (argv[4] != NULL) ? argv[4] : "EMPTY";
    char* powerPlantID = argv[4];


    pStation* stations = malloc(nb_stations * sizeof(pStation));

    tree = processStation(DIR_STATION_SORTED, tree, stations);

    mergeSort(stations, nb_stations);


    processConsumer(DIR_CONSUMER_SORTED, tree);


    outputProcess(stationType, consumerType, powerPlantID, stations, nb_stations);
    // for(int y=0; y<118; y++){
    //     printf("ID : %d | Capacity : %ld | Somme : %ld\n", stations[y]->id, stations[y]->capacity, stations[y]->consumption_sum);
    // }
    printf("\nMain : exec réussie\n");
  
    return 0;
}