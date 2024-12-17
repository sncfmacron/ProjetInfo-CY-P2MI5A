/*
    Main program
*/


#include "main.h"


int main(int argc, char* argv[]) {

    if (argc < 3) {
        exit_with_message("ERROR: Not enough parameters provided.", ERR_PIPE);
    }

    processData();

    outputProcess(argv[1], argv[2], argv[3]);
  
    return 0;
}