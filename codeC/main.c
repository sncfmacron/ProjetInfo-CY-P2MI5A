/*
    Main program
*/


#include "main.h"


int main(int argc, char* argv[]) {

    if(argc < 2) {
        exit_with_message("ERROR: invalid number of parameters", 1);
    }

    readData(getStationType(argv[1]));

    printf("\nBoumiz\n");
  
    return 0;
}