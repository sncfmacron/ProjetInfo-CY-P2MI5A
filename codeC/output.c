/*
    Contains functions for creating output files
*/


#include "output.h"


void outputProcess(const char* stationType, const char* consumerType, const char* stationID) {

    createOutputFile(stationType, consumerType, stationID);

}


// Concatenate strings to get the right file name (ex: hva_comp_2)
void createPath(const char* stationType, const char* consumerType, const char* stationID, char* path) {

    strcat(path, DIR_OUTPUT);
    strcat(path, stationType);
    strcat(path, "_");
    strcat(path, consumerType);

    if (strcmp(stationID, "\0") != 0) {
        strcat(path, "_");
        strcat(path, stationID);
    }

    strcat(path, ".csv");
}


void createOutputFile(const char* stationType, const char* consumerType, const char* stationID) {

    FILE* file = NULL;

    // Avoir le bon nom de fichier crée (ex : "hva_comp.csv")
    char* path = malloc(sizeof(char)*30);

    if(path == NULL) {
        exit_with_message("ERROR: path string allocation failed.", ERROR_PTR_ALLOC);
    } else {
        createPath(stationType, consumerType, stationID, path);
    }

    // fopen avec l'option "w" crée automatiquement le fichier
    file = fopen(path, "w");
    fprintf(file, "station %s:capacity:%s", stationType, consumerType);

    if(file == NULL) {
        exit_with_message("ERROR: output file allocation failed.", 3);
    }

    fclose(file);
}