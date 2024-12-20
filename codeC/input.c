/*
    input.c : functions to get data from c-wire.sh
*/


#include "input.h"


// Reading sorted station data from './tmp' directory
pAVL processStation(const char *filePath, pAVL tree, pStation* stationArray, pStation* mmArray, char* consumerType) {
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
            mmArray[i] = NULL;  // to properly free in case consumer type isn't "all"
            if(strcmp(consumerType, "all") == 0){
                mmArray[i] = createStation(id, capacity);
            }
            i++;

        } else {
            exit_with_message("ERROR: Invalid sorted input file format", ERR_INPUT_FORMAT);
        }
    }

    fclose(file);
    return tree;
}


// Reading sorted consumer data from './tmp' directory
void processConsumer(const char *filePath, pAVL tree)
{
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
