/*
    Main program
*/


#include "basics.h"


int main() {

    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, stdin)) {
        printf("Traitement: %s", buffer);
    }


    printf("\nBoumiz\n");

    return 0;
}
