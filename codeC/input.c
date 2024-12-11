/*
    Functions to get data from c-wire.sh
*/


#include "input.h"


// Ne fonctionne que pour les hvb -> c'est un test
// ./c-wire.sh input/DATA_CWIRE.csv hvb comp
void readDataHVB()
{
    char buffer[MAX_BUFFER_SIZE];

    FILE* file = NULL;
    file = fopen("../temp/sorted_hvb.txt", "r");
    if(file == NULL)
    {
        exit_with_message("ERROR: allocation failed", 1);
    }

    while (fgets(buffer, MAX_BUFFER_SIZE, file)) {
        // strok(str, delim) pour séparer l'entrée du shell en différentes chaines de caractères
        char *centrale_id = strtok(buffer, " ");
        char *station_id = strtok(NULL, " ");
        char *capacity = strtok(NULL, "\n");

        if (centrale_id && station_id && capacity) {
            printf("Central ID: %s\n", centrale_id);
            printf("Station ID: %s\n", station_id);
            printf("Capacity: %s kV\n", capacity);
        }
        
        printf("----------------------\n");
    }

    fclose(file);


    printf("Affichage données réussie");
}
