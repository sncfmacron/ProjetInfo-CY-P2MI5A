/*
    input.c : functions to get data from c-wire.sh
*/


#include "input.h"


// Reading sorted station data from './tmp' directory
pAVL processStation(const char *filePath, pAVL tree, pStation* stationArray, pStation* mmArray, char* consumerType) {
    if (filePath == NULL || stationArray == NULL || mmArray == NULL || consumerType == NULL) {
        exit_with_message("ERROR: NULL pointer passed as argument", ERR_NULL_POINTER);
    }
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        exit_with_message("ERROR : Sorted station file not found.", ERR_MISSING_FILE);
    }
    
    char line[128];     // Buffer for each line of the file
    int id;
    long capacity;
    uint32_t i = 0;         // Incremental value for the stations
    while (fgets(line, sizeof(line), file)) {
        // Read the current line with 'sscanf'
        if (sscanf(line, "%d %ld", &id, &capacity) == 2) {

            int height = 0;
            stationArray[i] = createStation(id, capacity);
            tree = insertAVL(tree, stationArray[i], &height);
            if(strcmp(consumerType, "all") == 0){
                mmArray[i] = createStation(id, capacity);
            }
            i++;

        } else {
            exit_with_message("ERROR: Invalid sorted input file format", ERR_INPUT_FORMAT);
        }
    }

    // Vérification qu'au moins une station a été lue
    if (i == 0) {
        fclose(file);
        exit_with_message("ERROR: Empty input file", ERR_INPUT_FORMAT);
    }

    fclose(file);
    return tree;
}


// Reading sorted consumer data from './tmp' directory
void processConsumer(const char *filePath, pAVL tree){
    if(filePath == NULL || tree == NULL){
        exit_with_message("ERROR: NULL pointer passed as argument", ERR_NULL_POINTER);
    }
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        exit_with_message("ERROR : Sorted consumer file not found.", ERR_MISSING_FILE);
    }

    char line[128];
    int id;
    long load;

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d %ld", &id, &load) == 2) {
            if (load > 0) {
                updateSum(tree, id, load);
            }
        }  else {
            exit_with_message("ERROR: Invalid sorted input file format.", ERR_INPUT_FORMAT);
        }
    }

    fclose(file);
}