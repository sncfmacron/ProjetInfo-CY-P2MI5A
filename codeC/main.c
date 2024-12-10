/*
    Main program
*/


#include "basics.h"


int main() {
    char buffer[MAX_BUFFER_SIZE];
    while (fgets(buffer, MAX_BUFFER_SIZE, stdin)) {
        // strok(str, delim) pour séparer l'entrée du shell en différentes chaines de caractères
        // Exemple : le shell envoie "1 2 7 -" ce qui donne une chaine pour "1", une pour "2", pour "7", pour "-"
        char *centrale_id = strtok(buffer, " ");
        char *station_id = strtok(NULL, " ");
        char *company_id = strtok(NULL, " ");
        char *capacity = strtok(NULL, " ");
        char *load = strtok(NULL, "\n");

        if (company_id && strcmp(company_id, "-") == 0) {
            printf("Central ID: %s\n", centrale_id);
            printf("Station ID: %s\n", station_id);
            printf("Capacity: %s\n", capacity);
        } else {
            printf("Central ID: %s\n", centrale_id);
            printf("Station ID: %s\n", station_id);
            printf("Company ID: %s\n", company_id);
            printf("Load: %s\n", load);
        }
        printf("----------------------\n");
    }

    printf("\nBOUMIz\n");

    return 0;
}