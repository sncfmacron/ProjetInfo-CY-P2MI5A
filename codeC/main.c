/*
    main.c : main program
*/


#include "main.h"


void printAVL(pAVL a) {
    if (a) {
        printAVL(a->left);
        printf("DEBUG AVL : ID: %d, Capacity: %ldkV, Consumption Sum: %ldkV\n", a->station->id, a->station->capacity, a->station->consumption_sum);
        printAVL(a->right);
    }
}


int main(int argc, char* argv[]) {

    if (argc < 3) {
        exit_with_message("ERROR: Not enough parameters provided.", ERR_COMPILATION);
    }
    uint32_t nb_stations = string_to_int(argv[4]);
    pStation* stations = malloc(nb_stations * sizeof(pStation));
    pAVL tree = NULL;
    printf("\nNB LIGNES: %s\n", argv[4]);
    tree = processStation(DIR_STATION_SORTED, tree, stations);
    mergeSort(stations, nb_stations);
    //tree = processConsumer(DIR_CONSUMER_SORTED, tree);

    //printf("\n");
    //printAVL(tree);

    outputProcess(argv[1], argv[2], argv[3], tree);

    printf("\nMain : exec réussie\n");
  
    return 0;
}