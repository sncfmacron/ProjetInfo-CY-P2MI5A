/*
    Main program
*/


#include "basics.h"


int main() {

    char buffer[MAX_BUFFER_SIZE];
    while (fgets(buffer, MAX_BUFFER_SIZE, stdin)) {
        printf("Traitement: %s", buffer);
    }


    printf("\nBoumiz\n");

    return 0;
}
