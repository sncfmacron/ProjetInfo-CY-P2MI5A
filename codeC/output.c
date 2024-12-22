/*
    output.c: contains functions for creating output files
*/


#include "output.h"

// Function for cosmetic purpose in the output .csv file first line
const char* typeToPrint(const char* type){
    if (type == NULL) {
        exit_with_message("ERROR: NULL pointer passed as argument", ERR_NULL_POINTER);
    }

    if(strcmp(type, "all") == 0){
        return "all";
    } else if(strcmp(type, "comp") == 0){
        return "company";
    } else if(strcmp(type, "indiv") == 0){
        return "individual";
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

// Create output files with adapted names
void createPath(const char* stationType, const char* consumerType, const char* powerPlantID, char* path, int sizePath) {
    if(stationType == NULL || consumerType == NULL || powerPlantID == NULL){
        exit_with_message("ERROR: NULL pointer passed as argument", ERR_NULL_POINTER);
    }
    
    if(powerPlantID != NULL && strcmp(powerPlantID, "EMPTY") !=  0) {   // If power plant ID is specified adds it the the file names
        snprintf(path, sizePath, "%s%s_%s_%s.csv", DIR_OUTPUT, stationType, consumerType, powerPlantID);
    }
    else {  // Normal file name with station type, consumer type in /output
        snprintf(path, sizePath, "%s%s_%s.csv", DIR_OUTPUT, stationType, consumerType);
    }
}


// Initializes a file, generates its name and header
FILE* initOutputFile(const char* stationType, const char* consumerType, const char* powerPlantID) {
    if(stationType == NULL || consumerType == NULL || powerPlantID == NULL){
        exit_with_message("ERROR: NULL pointer passed as argument", ERR_NULL_POINTER);
    }
    char path[64];
    // Create the right file name (e.g. “hva_comp_2.csv”)
    int sizePath = sizeof(path);
    createPath(stationType, consumerType, powerPlantID, path, sizePath);
        
    FILE* file = NULL;
    
    // 'fopen' with “w” option automatically creates the file
    file = fopen(path, "w");

    // Cosmetic purpose
    const char* consumerTypeToPrint = typeToPrint(consumerType);
    const char* stationTypeToPrint = typeToPrint(stationType);
    if(file == NULL) {
        exit_with_message("ERROR: Output file creation failed.", ERR_FILE_CREATION);
    }
    else{   // Write the first line of the output file
        fprintf(file, "Station %s:Capacity:Load(%s)\n", stationTypeToPrint, consumerTypeToPrint);
    }

    return file;
}

// Writing calculated data in the output file
void writeOutputFile(pStation* stationArray, FILE* file, uint32_t nbStations){
    if(file == NULL){
        exit_with_message("ERROR: NULL pointer passed as argument", ERR_NULL_POINTER);
    }
    if(stationArray == NULL){
        exit_with_message("ERROR: Stations array is NULL", ERR_NULL_ARRAY);
    }
    if(nbStations < 1){
        exit_with_message("ERROR: Invalid argument", ERR_INVALID_ARGS);
    }
    // Write id:capacity:load_sum for each stations in the output file in capacity order
    for(int i=0; i<nbStations; i++){
        fprintf(file, "%d:%ld:%ld\n", stationArray[i]->id, stationArray[i]->capacity, stationArray[i]->load_sum);
    }
}

// In case of LV all, create 'lv_all_minmax.csv'
FILE* initLvMinMax(FILE* file){
    file = fopen(DIR_LV_MINMAX, "w");
    if(file == NULL) {
        exit_with_message("ERROR: Output file creation failed.", ERR_FILE_CREATION);
    }
    return file;
}

// Write in 'lv_all_minmax.csv'
void writeOutputLvMinMax(FILE* file, pStation* stationArray, pStation* mmArray, uint32_t nbStations){
    if(mmArray == NULL || stationArray == NULL){
        exit_with_message("ERROR: Station array is NULL", ERR_NULL_ARRAY);
    }
    if(file == NULL){
        exit_with_message("ERROR: NULL pointer passed as argument", ERR_NULL_POINTER);
    }
    if(nbStations < 1){
        exit_with_message("ERROR: Invalid arguments", ERR_INVALID_ARGS);
    }
    // First line the 'lv_all_minmax.csv'
    fprintf(file, "Station LV:Capacity:Load(all)\n");
    uint32_t i = 0, y = 0;
    uint32_t index[NB_MINMAX_STATIONS]; // Temporary tab to get the stations positions to print from Station Array
    // After mmArray is sorted by overload of stations, we search the ID through the main Station Array and print in the file the 10 overloaded and underloaded stations
    for(i = 0; i < nbStations; i++){
        for(y = 0; y < 10; y++){ // 10 = NB_MINMAX_STATIONS/2, for safety reason we put 10 because 'y' is an int 
            // If the station ID match copy it into the index
            if(mmArray[y]->id == stationArray[i]->id){
                index[y] = i;
            }
            if(mmArray[nbStations-1-y]->id == stationArray[i]->id){
                index[NB_MINMAX_STATIONS-1-y] = i;
            }
        }
    }
    // When the index is complete, print the 20 stations in overload order in the 'lv_all_minmax.csv' file.
    for(i = 0; i < NB_MINMAX_STATIONS; i++){
        fprintf(file, "%d:%ld:%ld\n", stationArray[index[i]]->id, stationArray[index[i]]->capacity, stationArray[index[i]]->load_sum);
    }
}

// Calls output fonctions
void outputProcess(const char* stationType, const char* consumerType, const char* powerPlantID, pStation* stationArray, pStation* mmArray, uint32_t nbStations) {
    if(stationType == NULL || consumerType == NULL || powerPlantID == NULL){
       exit_with_message("ERROR: NULL pointer passed as argument", ERR_NULL_POINTER); 
    }
    if(stationArray == NULL){
        exit_with_message("ERROR: Stations array is NULL", ERR_NULL_ARRAY);
    }
    if(nbStations < 1){
        exit_with_message("ERROR: Invalid arguments", ERR_INVALID_ARGS);
    }
    FILE* file = NULL;
    file = initOutputFile(stationType, consumerType, powerPlantID);
    if (file != NULL) {
        writeOutputFile(stationArray, file, nbStations);
        fclose(file);
    } else {
        exit_with_message("ERROR: Output file writing failed.", ERR_FILE_CREATION);
    }

    // lv_min_max process
    if(strcmp(consumerType, "all") == 0){
        FILE* lvMinMax = NULL;
        lvMinMax = initLvMinMax(lvMinMax);
        if (lvMinMax != NULL) {
            writeOutputLvMinMax(lvMinMax, stationArray, mmArray, nbStations);
            fclose(lvMinMax);
        } else {
            exit_with_message("ERROR: Output file writing failed.", ERR_FILE_CREATION);
        }
    }
}