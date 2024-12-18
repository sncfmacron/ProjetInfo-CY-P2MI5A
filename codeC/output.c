/*
    output.c : contains functions for creating output files
*/


#include "output.h"


// Calls output fonctions
void outputProcess(const char* stationType, const char* consumerType, const char* powerPlantID, pAVL tree) {
    FILE* file = NULL;
    file = initOutputFile(stationType, consumerType, powerPlantID);
    if (file != NULL) {
        //writeOutputFile(tree, file);
        fclose(file);
    } else {
        ("ERROR: output file writing failed.", ERR_FILE_CREATION);
    }
}

void createPath(const char* stationType, const char* consumerType, const char* powerPlantID, char* path, int sizePath) {
    if(powerPlantID != NULL && strcmp(powerPlantID, "") !=  0) {
        snprintf(path, sizePath, "%s%s_%s_%s.csv", DIR_OUTPUT, stationType, consumerType, powerPlantID);
    } else {
        snprintf(path, sizePath, "%s%s_%s.csv", DIR_OUTPUT, stationType, consumerType);
    }
}

// Initializes a file, generates its name and header
FILE* initOutputFile(const char* stationType, const char* consumerType, const char* powerPlantID) {
    if (stationType == NULL || consumerType == NULL) {
        exit_with_message("ERROR: stationType or consumerType is NULL.", ERR_INVALID_ARGS);
    }

    char path[128];
    // Create the right file name (e.g. “hva_comp_2.csv”)
    int sizePath = sizeof(path);
    createPath(stationType, consumerType, powerPlantID, path, sizePath);
        
    FILE* file = NULL;
    
    // 'fopen' with “w” option automatically creates the file
    file = fopen(path, "w");

    if(file == NULL) {
        exit_with_message("ERROR: output file creation failed.", ERR_FILE_CREATION);
        return NULL;
    } else {
        fprintf(file, "station %s:capacity:%s\n", stationType, consumerType);
    }

    return file;
}


// Writing calculated data in the output file
void writeOutputFile(pAVL tree, FILE* file) {






}