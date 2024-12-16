/*
    Main program
*/


#include "main.h"


int main(int argc, char* argv[]) {
    if(argc < 2) {
        exit_with_message("ERROR: invalid number of parameters.", ERROR_PIPE);
    }

    // Récuperer le type de conso. et de station à traiter
    int stationType = getStationType(argv[1]);

    // Lire les données triées par le shell dans input.c
    readData(stationType);

    // Créer le fichier de sortie
    outputProcess(argv[1], argv[2]);

    printf("\nBoumiz\n");
  
    return 0;
}