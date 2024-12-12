/*
    Functions to get data from c-wire.sh
*/


#include "input.h"


// Lire les données depuis stdin (pipe)
void readData(int stationType) {
    char buffer[MAX_BUFFER_SIZE];

    // On passe pour une pipe pour transmettre les données du shell vers program_c
    while (fgets(buffer, MAX_BUFFER_SIZE, stdin) != NULL) {
        // strok(str, delim) pour séparer l'entrée du shell en différentes chaines de caractères
        char *centrale_id_str = strtok(buffer, " ");
        char *station_id_str = strtok(NULL, " ");
        //char *consumer_id = strtok(NULL, " ");
        char *capacity_str = strtok(NULL, " ");
        // char *load = strtok(NULL, "\n");

        // Convertir les chaines récupérées en haut en entier ou long
        int centrale_id = atoi(centrale_id_str);
        int station_id = atoi(station_id_str);
        long capacity = atol(capacity_str);

        if (centrale_id && station_id && capacity) {
            Station s = createStation(centrale_id, station_id, capacity, stationType);
            printStation(s);
            //insertAVL(s);

        }
    }

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