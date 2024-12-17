/*
    Main program
*/


#include "main.h"


int main(int argc, char* argv[]) {

    if(argc < 2) {
        exit_with_message("ERROR: invalid number of parameters.", ERROR_PIPE);
    } else if(argv[1] == NULL || argv[2] == NULL) {
        exit_with_message("ERROR: invalid parameters.", ERROR_PIPE);
    }

    // Récuperer le type de conso. et de station à traiter
    int stationType = getStationType(argv[1]);


    // Lire les données triées par le shell dans input.c
    processData(stationType);


    // Créer le fichier de sortie
    outputProcess(argv[1], argv[2], argv[3]);
    // argv[1] = type de station
    // argv[2] = type de conso
    // argv[3] = id de centrale (si on l'a pas indiqué dans la commande alors chaine vide donc argv[3] = "\0")
  
    return 0;
}