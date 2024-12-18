/*
    input.c : functions to get data from c-wire.sh
*/


#include "input.h"


// Reading data
pAVL processFile(const char *filePath, pAVL tree) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        exit_with_message("ERROR : './temp/station_sorted.csv' not found.", ERR_INVALID_FILE);
    }

    char line[128];  // Buffer for each line of the file
    int id;
    long capacity;
    long load;

    while (fgets(line, sizeof(line), file)) {
        // // Replace the '-' character with '0
        char *p = line;
        while (*p) {
            if (*p == '-') {
                *p = '0';
            }
            p++;
        }

        // Read the current line with 'sscanf'
        if (sscanf(line, "%d %ld %ld", &id, &capacity, &load) == 3) {
            printf("DEBUG : Lues depuis le fichier - ID: %d, Capacité: %ld, Charge: %ld\n", id, capacity, load);

            if (capacity > 0) {
                int height = 0;
                pStation station = createStation(id, capacity);
                tree = insertAVL(tree, station, &height);
                printf("DEBUG : Station ID %d insérée dans l'arbre.\n", id);
            } else if (load > 0) {
                updateSum(tree, id, load);
                printf("DEBUG : MAJ de la conso. pour la station %d avec +%ldkV.\n", id, load);
            }
        } else {
            printf("DEBUG : Ligne incorrecte : %s", line);
        }
    }

    fclose(file);
    return tree;
}
    
    
    
/*clock_t start = clock();
    
 
    clock_t end = clock();
    float seconds = getTime(end, start);

printf("\n--- Data transmitted successfully in %.2f seconds ---\n", seconds);*/