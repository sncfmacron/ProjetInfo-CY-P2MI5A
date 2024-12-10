/*
    Basic functions and tree management bite
*/


#include "basics.h"


// Exit program with an error message
void exit_with_message(const char *message, int error_code) {
    // Print the message to standard error
    fprintf(stderr, "%s\n", message);
    exit(error_code);
}

int max3(int a, int b, int c) {
    int max = a;

    if (b > max) {
        max = b;
    }
    if (c > max) {
        max = c;
    }
    return max;
}


int min3(int a, int b, int c) {
    int min = a;

    if (b < min) {
        min = b;
    }
    if (c < min) {
        min = c;
    }
    return min;
}


int max(int a, int b) {
    if (a > b) {
        return a;
    } else {
        return b;
    }
}


int min(int a, int b) {
    if(a > b) {
        return b;
    } else {
        return a;
    }
}


pAVL createAVL(Station s) {
    pAVL a = malloc(sizeof(AVL));
    if(a == NULL)
    {
        exit_with_message("ERROR: AVL allocation failed.", -1);
    }

    a->station = s;
    a->left = NULL;
    a->right = NULL;
    a->balance = 0;
    return a;
}


pAVL insertionAVL(pAVL a, Station s, int *h) {
    if (a == NULL) {
        *h = 1;
        return createAVL(s);
    } 
    else if (s.id < a->station.id) {
        a->left = insertionAVL(a->left, s, h);
        *h = -*h;
    } 
    else if (s.id > a->station.id) {
        a->right = insertionAVL(a->right, s, h);
    } 
    else {
        *h = 0;
        return a;
    }

    if (*h != 0) {
        a->balance += *h;
        a = equilibrerAVL(a);
        *h = (a->balance == 0) ? 0 : 1;
    }

    return a;
}


void cleanAVL(pAVL a) {
    if(a == NULL)
    {
        return;
    }

    free(a->left);
    free(a->right);

    free(a);
}