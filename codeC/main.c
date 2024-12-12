/*
    Main program
*/


#include "main.h"


int main(int argc, char* argv[]) {

    if(argc < 2) {
        exit_with_message("ERROR: invalid number of parameters", 1);
    }

    // Lire les données triées par le shell dans input.c
    // Là getStationType(argv[1]) va permettre de connaitre le type de station qu'on traite ! (voir basics.h)
    readData(getStationType(argv[1]));

    printf("\nBoumiz\n");
  
    return 0;
}