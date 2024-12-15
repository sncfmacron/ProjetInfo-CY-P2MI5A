/*
    Main program
*/


#include "main.h"


int main(int argc, char* argv[]) {
    if(argc < 2) {
        exit_with_message("ERROR: invalid number of parameters.", ERROR_PIPE);
    }

    // Lire les données triées par le shell dans input.c ; getStationType(argv[1]) permet de connaitre le type de station qu'on traite
    readData(getStationType(argv[1]));

    printf("\nBoumiz\n");
  
    return 0;
}