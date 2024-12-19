/*
    output.c : contains functions for creating output files
*/


#include "output.h"

// function for cosmetic purpose in the output .csv file
const char* typeToPrint(const char* type){
    if (type == NULL) {
        exit_with_message("ConsumerType is NULL.", ERR_INVALID_ARGS);
    }

    if(strcmp(type, "all") == 0){
        return "All";
    } else if(strcmp(type, "comp") == 0){
        return "Company";
    } else if(strcmp(type, "indiv") == 0){
        return "Individual";
    } else if(strcmp(type, "hvb") == 0){
        return "HV-B";
    } else if(strcmp(type, "hva") == 0){
        return "HV-A";
    } else if(strcmp(type, "lv") == 0){
        return "LV";
    }
    else {
        exit_with_message("consumerType or stationType is invalid.", ERR_INVALID_ARGS);
    }

    return NULL;
}
// Calls output fonctions
void outputProcess(const char* stationType, const char* consumerType, const char* powerPlantID, pStation* stations, uint32_t nb_stations) {
    FILE* file = NULL;
    file = initOutputFile(stationType, consumerType, powerPlantID);
    if (file != NULL) {
        writeOutputFile(stations, file, nb_stations);
        fclose(file);
    } else {
        exit_with_message("ERROR: output file writing failed.", ERR_FILE_CREATION);
    }
}

void createPath(const char* stationType, const char* consumerType, const char* powerPlantID, char* path, int sizePath) {
    if(powerPlantID != NULL && strcmp(powerPlantID, "EMPTY") !=  0) {
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

    char path[64];
    // Create the right file name (e.g. “hva_comp_2.csv”)
    int sizePath = sizeof(path);
    createPath(stationType, consumerType, powerPlantID, path, sizePath);
        
    FILE* file = NULL;
    
    // 'fopen' with “w” option automatically creates the file
    file = fopen(path, "w");
    const char* consumerTypeToPrint = typeToPrint(consumerType);
    const char* stationTypeToPrint = typeToPrint(stationType);
    if(file == NULL) {
        exit_with_message("ERROR: output file creation failed.", ERR_FILE_CREATION);
        return NULL;
    } else {
        fprintf(file, "Station %s:Capacity:%s\n", stationTypeToPrint, consumerTypeToPrint);
        
    }

    return file;
}


// Writing calculated data in the output file
void writeOutputFile(pStation* stations, FILE* file, uint32_t nb_stations){
    for(int i=0; i<nb_stations; i++){
        fprintf(file, "%d:%ld:%ld\n", stations[i]->id, stations[i]->capacity, stations[i]->consumption_sum);
    }
}