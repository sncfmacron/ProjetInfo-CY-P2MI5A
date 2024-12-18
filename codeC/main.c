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

    if (argc < 2) {
        exit_with_message("ERROR: Not enough parameters provided.", ERR_COMPILATION);
    }

    pAVL tree = NULL;

    tree = processStation(DIR_STATION_SORTED, tree);
    tree = processConsumer(DIR_CONSUMER_SORTED, tree);

    printf("\n");
    printAVL(tree);

    outputProcess(argv[1], argv[2], argv[3], tree);

    printf("\nMain : exec réussie\n");
  
    return 0;
}