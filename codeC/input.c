/*
    Functions to get data from c-wire.sh
*/


#include "input.h"


// Reading data from stdin with a pipe
void processData() {
    
    char buffer[MAX_BUFFER_SIZE];

    // On passe pour une pipe pour transmettre les données du shell vers program_c
    // strok(str, delim) pour séparer l'entrée du shell en différentes chaines de caractères

    /*
        Il faudra remplacer atol, aoi etc par strol c'est plus safe
    */

    // On utilise clock de time_h pour mesurer le temps
    clock_t start = clock();
    
    pAVL tree = NULL;

    while (fgets(buffer, MAX_BUFFER_SIZE, stdin) != NULL) {
        char *station_id_str = strtok(buffer, " ");
        char *capacity_str = strtok(NULL, " ");
        char *load_str = strtok(NULL, "\n");

        int station_id = string_to_int(station_id_str);

        // Si capacity_str différent de "-" alors on étudie bien la capacité
        if (strcmp(capacity_str, "-") != 0) {

            // processStation(int station_id, int capacity);

            // Convertir les chaines récupérées en haut en entier ou long
            long capacity = string_to_long(capacity_str);

            processStation(tree, station_id, capacity);



        // Sinon on étudie un consommateur
        } else if(strcmp(capacity_str, "-") == 0) {

            long load = string_to_long(load_str);

            processConsumer(tree, station_id, load);

        } else {
            exit_with_message("ERROR: invalid entry in readData() function.", ERR_PIPE);
        }
    }

    clock_t end = clock();
    float seconds = getTime(end, start);

    printf("\n--- Data transmitted successfully in %.2f seconds ---\n", seconds);
}


void processStation(pAVL tree, int station_id, int capacity) {

    pStation s = createStation(station_id, capacity);

    int height = 0;
    tree = insertAVL(tree, s, &height);

    // ajouterListe(s);
}

void processConsumer(pAVL tree, int station_id, int load) {

    // updateSum(tree, station_id, load);
}