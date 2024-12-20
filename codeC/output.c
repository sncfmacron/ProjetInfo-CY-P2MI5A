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
        exit_with_message("ERROR: 'consumerType' or 'stationType' is invalid.", ERR_INVALID_ARGS);
    }

    return NULL;
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
        exit_with_message("ERROR: Output file creation failed.", ERR_FILE_CREATION);
        return NULL;
    } else {
        fprintf(file, "Station %s:Capacity:%s\n", stationTypeToPrint, consumerTypeToPrint);
        
    }

    return file;
}


// Writing calculated data in the output file
void writeOutputFile(pStation* stations, FILE* file, uint32_t nbStations){
    for(int i=0; i<nbStations; i++){
        fprintf(file, "%d:%ld:%ld\n", stations[i]->id, stations[i]->capacity, stations[i]->load_sum);
    }
}

//
FILE* initLvMinMax(FILE* file, pStation* stations, uint32_t nbStations) {
    // Verif stationArray
    file = fopen(DIR_LV_MINMAX, "w");
    // vérif les droits d'écriture
    fprintf(file, "Station LV:Capacity:Used capacity\n");
    return file;
}

void writeOutputLvMinMax(FILE* file, pStation* stations, pStation* mmArray) {
    for(int i=0; i<NB_MINMAX_STATIONS; i++){
        fprintf(file, "%d:%ld\n", mmArray[i]->id, mmArray[i]->capacity);
    }

}

// Calls output fonctions

// CMT : remplacer stations par stationsArray ?

void outputProcess(const char* stationType, const char* consumerType, const char* powerPlantID, pStation* stations, uint32_t nbStations, pStation* mmArray) {
    FILE* file = NULL;
    file = initOutputFile(stationType, consumerType, powerPlantID);
    if (file != NULL) {
        writeOutputFile(stations, file, nbStations);
        fclose(file);
    } else {
        exit_with_message("ERROR: Output file writing failed.", ERR_FILE_CREATION);
    }

    // lv_min_max process
    if(strcmp(consumerType, "all") == 0) {
        FILE* lvMinMax = NULL;
        lvMinMax = initLvMinMax(lvMinMax, stations, nbStations);
        if (file != NULL) {
            writeOutputLvMinMax(lvMinMax, stations, mmArray);
            fclose(lvMinMax);
        } else {
            exit_with_message("ERROR: Output file writing failed.", ERR_FILE_CREATION);
        }
    }
}