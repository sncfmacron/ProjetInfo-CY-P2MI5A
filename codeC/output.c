/*
    Contains functions for creating output files
*/


#include "output.h"


void outputProcess(const char* stationType, const char* consumerType) {

    createOutputFile(stationType, consumerType);

}


void createPath(const char* stationType, const char* consumerType, char* path) {

    // Concaténer les chaines de caractères pour avoir le bon nom de fichier
    strcat(path, DIR_OUTPUT);
    strcat(path, stationType);
    strcat(path, "_");
    strcat(path, consumerType);
    strcat(path, ".csv");

}


void createOutputFile(const char* stationType, const char* consumerType) {

    FILE* file = NULL;

    // Avoir le bon nom de fichier crée (ex : "hva_comp.csv")
    char path[30];

    if(path == NULL) {
        exit_with_message("ERROR: path string allocation failed.", ERROR_PTR_ALLOC);
    } else {
        createPath(stationType, consumerType, path);
    }

    // fopen avec l'option "w" crée automatiquement le fichier
    file = fopen(path, "w");
    fprintf(file, "Station %s:Capacity:Consumer %s", stationType, consumerType);

    if(file == NULL) {
        exit_with_message("ERROR: output file allocation failed.", 3);
    }

    fclose(file);
}