/*
    input.c: functions to get data from c-wire.sh
*/


#include "input.h"


// Reading sorted station data from './tmp' directory
pAVL processStation(const char *filePath, pAVL tree, pStation* stationArray, pStation* mmArray, char* consumerType) {
    if(filePath == NULL){
        exit_with_message("ERROR: Invalid file path", ERR_FILE_PATH);
    }
    if(stationArray == NULL){
        exit_with_message("ERROR: Stations array is NULL", ERR_NULL_ARRAY);
    }
    if(consumerType == NULL){
        exit_with_message("ERROR: NULL pointer consumerType passed as argument", ERR_NULL_POINTER);
    }
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        exit_with_message("ERROR : Sorted station file not found.", ERR_MISSING_FILE);
    }
    
    char line[128];     // Buffer for each line of the file
    int id;             // Init of the id
    long capacity;      // Init of the capacity
    uint32_t i = 0;     // Incremental value for the stations

    // Read the strings of each lines of the file and update the values (the while loop for nbStations)
    while (fgets(line, sizeof(line), file)) {
        // Read the current line with 'sscanf'
        if (sscanf(line, "%d %ld", &id, &capacity) == 2) {
            // Init of the height for the good use of the insertAVL function 
            int height = 0;
            // Create a new station and copy it in the station Array
            stationArray[i] = createStation(id, capacity);
            // Insert the newly created station into an AVL tree ruled by the station ID
            tree = insertAVL(tree, stationArray[i], &height);
            // If consumer type is 'all' -> init the values for the Min Max Array by doing a copy of the stations
            if(strcmp(consumerType, "all") == 0){
                mmArray[i] = createStation(id, capacity);
            }
            // Incremental value
            i++;

        } else {
            exit_with_message("ERROR: Invalid sorted input file format", ERR_INPUT_FORMAT);
        }
    }

    // Check that at least one station has been read
    if (i == 0) {
        fclose(file);
        exit_with_message("ERROR: Empty input file", ERR_INPUT_FORMAT);
    }

    fclose(file);
    return tree;
}


// Reading sorted consumer data from './tmp' directory
void processConsumer(const char *filePath, pAVL tree){
    if(filePath == NULL){
        exit_with_message("ERROR: Invalid file path", ERR_FILE_PATH);
    }
    if(tree == NULL){
        exit_with_message("ERROR: NULL AVL pointer", ERR_NULL_AVL);
    }
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        exit_with_message("ERROR : Sorted consumer file not found.", ERR_MISSING_FILE);
    }

    char line[128]; // Max value to read from a line
    int id;         // Init of the id
    long load;      // Init of the load
    // Read the strings of each lines of the file and update the values of load_sum
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d %ld", &id, &load) == 2) {
            if (load > 0) {
                updateSum(tree, id, load);  // update the sum of the load_sum for the stations
            }
        }  else {
            exit_with_message("ERROR: Invalid sorted input file format.", ERR_INPUT_FORMAT);
        }
    }

    fclose(file);
}