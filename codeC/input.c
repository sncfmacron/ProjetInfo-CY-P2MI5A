/*
    Functions to get data from c-wire.sh
*/


#include "input.h"


void readData(int stationType)
{
    char buffer[MAX_BUFFER_SIZE];

    switch (stationType) {
        case STATION_HVB:
            printf("-- Il s'agit de HVB --\n\n");
            break;

        case STATION_HVA:
            printf("-- Il s'agit de HVA --\n\n");
            break;

        case STATION_LV:
            printf("-- Il s'agit de LV --\n\n");
            break;
    }

    FILE* file = NULL;
    file = fopen("../temp/stations_sorted.csv", "r");
    if(file == NULL)
    {
        exit_with_message("ERROR: allocation failed or file 'temp/stations_sorted.csv' is missing", 1);
    }

    while (fgets(buffer, MAX_BUFFER_SIZE, file) != NULL) {
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


    printf("Affichage des données réussi");
}
