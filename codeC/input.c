/*
    Functions to get data from c-wire.sh
*/


#include "input.h"


void readData(int stationType)
{
    char buffer[MAX_BUFFER_SIZE];

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

        // Convertir chaine en entier ou long
        int centrale_id_int = atoi(centrale_id);
        int station_id_int = atoi(station_id);
        long capacity_long = atol(capacity);

        if (centrale_id && station_id && capacity) {
            Station s = createStation(centrale_id_int, station_id_int, capacity_long, stationType);
            printStation(s);
            //insertionAVL(s);
        }

    }

    fclose(file);

    printf("Affichage des données réussi");
}


// Je mets ça ici pour test, on pourra l'enlever
void printStation(Station s) {

    switch (s.type) {
        case 0:
            printf("Station type : HVB\n");
            break;
        case 1:
            printf("Station type : HVA\n");
            break;
        case 2:
            printf("Station type : LV\n");
            break;
    }

    printf("Central ID: %d\n", s.linked_central);
    printf("Station ID: %d\n", s.id);
    printf("Capacity: %ld kV\n", s.capacity);
    printf("----------------------\n");
}