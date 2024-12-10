/*
    Main program
*/


#include "basics.h"


int main() {
    char station_id[20];
    char company_id[20];
    char centrale_id[20];
    char capacity[20];
    char load[20];

    // Pour le moment ça ne fonctionne qu'avec les HVA-HVB

    while (scanf("%s %s %s %s %s", centrale_id, station_id, company_id, capacity, load) == 5) {
        if (strcmp(company_id, "-") == 0) {
            // Pas d'ID d'entreprise, traiter uniquement la station et sa capacité
            printf("Central ID: %s\n", station_id);
            printf("Station ID: %s\n", station_id);
            printf("Capacity: %s\n", capacity);
        } else {
            // Traiter tous les champ
            printf("Central ID: %s\n", station_id);
            printf("Station ID: %s\n", station_id);
            printf("Company ID: %s\n", company_id);
            printf("Load: %s\n", load);
        }
        printf("----------------------\n");
    }

    printf("\nBOUMIZ\n");

    return 0;
}