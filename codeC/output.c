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
        exit_with_message("consumerType or stationType is invalid.", ERR_INVALID_ARGS);
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
        fprintf(file, "Station %s:Capacity:Load(%s)\n", stationTypeToPrint, consumerTypeToPrint);
    }

    return file;
}


// Writing calculated data in the output file
void writeOutputFile(pStation* stationArray, FILE* file, uint32_t nbStations){
    printf("Writing output data...\n\n");
    clock_t start = clock();
    
 
    for(int i=0; i<nbStations; i++){
        fprintf(file, "%d:%ld:%ld\n", stationArray[i]->id, stationArray[i]->capacity, stationArray[i]->consumption_sum);
    }

    sleep(2);
    clock_t end = clock();
    displayTime(start, end, "Writing the output data completed successfully");
}


FILE* initLvMinMax(FILE* file, pStation* stationArray, pStation* mmArray, uint32_t nbStations) {
    if(mmArray == NULL || stationArray == NULL){
        exit_with_message("ERROR: Station array is NULL", 31418);
    }
    fprintf(file, "Min and Max 'capacity-load' extreme nodes\n");
    fprintf(file, "Station LV:Capacity:Load(all)\n");
    uint32_t i = 0, y = 0;
    uint32_t index[20]; // mettre un define pour 10 max et 10 min puis faire la somme des deux
    for(i = 0; i < nbStations; i++){
        for(y = 0; y < 10; y++){ // mettre max du define
            if(mmArray[y]->id == stationArray[i]->id){
                index[y] = i;
            }
            if(mmArray[nbStations-y]->id == stationArray[i]->id){
                index[20-y] = i; // mettre la somme des deux define (à la place de 20) - y
            }
        }
    }
    for(i = 0; i < 20; i++){ // somme de 10 + 10 (define)
        fprintf(file, "%d:%ld:%ld\n", stationArray[index[i]]->id, stationArray[index[i]]->capacity, stationArray[index[i]]->consumption_sum);
    }

    return file;
}

// Calls output fonctions
void outputProcess(const char* stationType, const char* consumerType, const char* powerPlantID, pStation* stationArray, uint32_t nbStations, pStation* mmArray) {
    FILE* file = NULL;
    file = initOutputFile(stationType, consumerType, powerPlantID);
    if (file != NULL) {
        writeOutputFile(stationArray, file, nbStations);
        fclose(file);
    } else {
        exit_with_message("ERROR: Output file writing failed.", ERR_FILE_CREATION);
    }

    // // lv_min_max process
    // if((strcmp(stationType, "lv") == 0) && (strcmp(consumerType, "all") == 0)){
    //     FILE* lvMinMax = NULL;
    //     lvMinMax = initLvMinMax(lvMinMax, stationArray, mmArray, nbStations);
    //     if (lvMinMax != NULL) { // CMT: j'ai mit !=, c'est ça normalement non ? It's late so my brain isn't braining anymore
    //         // fonction pour remplir le fichier
    //         fclose(lvMinMax);
    //     } else {
    //         exit_with_message("ERROR: Output file writing failed.", ERR_FILE_CREATION);
    //     }
    // }
}