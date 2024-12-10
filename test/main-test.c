#include <stdio.h>
#define BUFFER_SIZE 1024


int main() {
    char buffer[BUFFER_SIZE];
    while (fgets(buffer, BUFFER_SIZE, stdin)) {
        printf("\nTraitement : %s", buffer);
    }
    return 0;
}