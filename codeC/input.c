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
        char *power_plant_str = strtok(buffer, " ");
        char *station_id_str = strtok(NULL, " ");
        //char *consumer_id = strtok(NULL, " ");
        char *capacity_str = strtok(NULL, " ");
        // char *load = strtok(NULL, "\n");

        // Convertir les chaines récupérées en haut en entier ou long
        int power_plant_id = atoi(power_plant_str);
        int station_id = atoi(station_id_str);
        long capacity = atol(capacity_str);

        if (power_plant_id && station_id && capacity) {
            pStation s = createStation(power_plant_id, station_id, capacity, stationType);
            printStation(s);
            //insertAVL(s);

        }
    }

    printf("Affichage des données réussi");
}


// Je mets ça ici pour test, on pourra l'enlever
void printStation(pStation s) {

    switch (s->type) {
        case 2:
            printf("Station type : HVB\n");
            break;
        case 1:
            printf("Station type : HVA\n");
            break;
        case 0:
            printf("Station type : LV\n");
            break;
        default:
            exit_with_message("ERROR: Printed station doesn't exist", 3);
            break;
    }

    printf("Central ID: %d\n", s->linked_power_plant);
    printf("Station ID: %d\n", s->id);
    printf("Capacity: %ld kV\n", s->capacity);
    printf("----------------------\n");
}