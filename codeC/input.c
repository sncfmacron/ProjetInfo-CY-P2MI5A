/*
    input.c : functions to get data from c-wire.sh
*/


#include "input.h"


// Reading sorted station data from './temp' directory
pAVL processStation(const char *filePath, pAVL tree) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        exit_with_message("ERROR : sorted station file not found.", ERR_MISSING_FILE);
    }

    char line[128];  // Buffer for each line of the file
    int id;
    long capacity;

    while (fgets(line, sizeof(line), file)) {
        // Read the current line with 'sscanf'
        if (sscanf(line, "%d %ld", &id, &capacity) == 2) {

            //printf("DEBUG : Lues depuis le fichier - ID: %d, Capacité: %ld", id, capacity);

            int height = 0;
            pStation station = createStation(id, capacity);
            tree = insertAVL(tree, station, &height);

            //printf("DEBUG : Station ID %d insérée dans l'arbre.\n", id);

        } else {
            exit_with_message("ERROR: invalid sorted input file format", ERR_INPUT_FORMAT);
            printf("DEBUG : Ligne incorrecte : %s", line);
        }
    }

    fclose(file);
    return tree;
}

// Reading sorted consumer data from './temp' directory
pAVL processConsumer(const char *filePath, pAVL tree)
{
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        exit_with_message("ERROR : sorted consumer file not found.", ERR_MISSING_FILE);
    }

    char line[128];
    int id;
    long load;

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d %ld", &id, &load) == 2) {
            //printf("DEBUG : Lues depuis le fichier - ID: %d, Charge: %ld\n", id, load);
            if (load > 0) {
                updateSum(tree, id, load);
                //printf("DEBUG : MAJ de la conso. pour la station %d avec +%ldkV.\n", id, load);
            }
        }  else {
            exit_with_message("ERROR: invalid sorted input file format.", ERR_INPUT_FORMAT);
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