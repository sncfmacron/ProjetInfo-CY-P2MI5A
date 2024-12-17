/*
    Functions to get data from c-wire.sh
*/


#include "input.h"


// Reading data from stdin with a pipe
void processData(int stationType) {
    
    char buffer[MAX_BUFFER_SIZE];

    // On passe pour une pipe pour transmettre les données du shell vers program_c
    // strok(str, delim) pour séparer l'entrée du shell en différentes chaines de caractères

    /*
        Il faudra remplacer atol, aoi etc par strol c'est plus safe
    */

    // On utilise clock de time_h pour mesurer le temps
    clock_t start = clock();
    

    while (fgets(buffer, MAX_BUFFER_SIZE, stdin) != NULL) {
        char *station_id_str = strtok(buffer, " ");
        char *capacity_str = strtok(NULL, " ");
        char *load_str = strtok(NULL, "\n");

        // Si capacity_str différent de "-" alors on étudie bien la capacité
        if (strcmp(capacity_str, "-") != 0) {

            // Convertir les chaines récupérées en haut en entier ou long
            int station_id = string_to_int(station_id_str);
            long capacity = atol(capacity_str);

            pStation s = createStation(station_id, capacity, stationType);
            printStation(s);
            //insertAVL(s);


        // Sinon on étudie un consommateur
        } else if(strcmp(capacity_str, "-") == 0) {
            int station_id = string_to_int(station_id_str);
            long load = atol(load_str);
            printf("\n- Station %d consumer : %ld kV\n\n", station_id, load);
            //calcul(...)
        } else {
            exit_with_message("ERROR: invalid entry in readData() function.", ERROR_PIPE);
        }
    }

    clock_t end = clock();
    float seconds = getTime(end, start);

    printf("\n--- Data transmitted successfully in %.2f seconds ---\n", seconds);
}


// Je mets ça ici pour test
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
            exit_with_message("ERROR: printed station doesn't exist.", ERROR_PTR_ALLOC);
            break;
    }
    printf("Station ID: %d\n", s->id);
    printf("Capacity: %ld kV\n", s->capacity);
}