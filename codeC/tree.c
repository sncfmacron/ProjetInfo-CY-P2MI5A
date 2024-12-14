/*
    Tree management
*/


#include "tree.h"

pAVL createAVL(pStation s) {
    if(s == NULL){
        exit_with_message("ERROR: NULL pointer", 3);
    }
    pAVL a = malloc(sizeof(AVL));
    if(a == NULL)
    {
        exit_with_message("ERROR: AVL allocation failed.", 4);
    }

    a->station = s;
    a->left = NULL;
    a->right = NULL;
    a->balance = 0;
    return a;
}

pAVL insertAVL(pAVL a, pStation s, int* h){
    if(s == NULL){
        exit_with_message("ERROR: Station doesn't exist", 5);
    }

    if(a == NULL){
        *h = 1; // new node increase the height of his parent node
        return createAVL;
    }
    else if(s->id < a->station->id){
        a->left=insertAVL(a->left, s, h);
        *h = -1; // make the height negative
    }
    else if(s->id > a->station->id){
        a->right=insertAVL(a->right, s, h);
        *h = 1; // make the height positive
    }
    else{
        *h = 0;
        return s;
    }

    if(*h != 0){
        switch (*h){
        case -1:
            a->balance += *h; // balances the node for a left child
            break;
        case 1:
            a->balance += *h; // balances the node for a right child
            break;
        default:
            exit_with_message("ERROR: InsertAVL balance error", 7);
            break;
        }
        if((*h == -1 && a->balance >= 0) || (*h == 1 && a->balance <= 0)){ // if the node is balanced
            *h = 0;
        }
        else{
            // rotation/balance function
        }
    }
}

void cleanAVL(pAVL a) {
    if(a == NULL)
    {
        return;
    }

    free(a->left);
    free(a->right); // EDIT : faire une fonction recursive je pense free(a-left) -> cleanAVL(a->left)

    free(a);
}