/*
    tree.c : contains tree management functions
*/


#include "tree.h"


// Updates a station consumption sum using recursive search in an AVL tree
void updateSum(pAVL a, uint32_t stationID, long load) {
    if(a == NULL || a->station == NULL) {
        exit_with_message("ERROR: station doesn't exist.", ERR_INVALID_STATION);
    }

    if(a->station->id == stationID) {
        a->station->load_sum += load;
    } else if(a->station->id > stationID) {
        updateSum(a->left, stationID, load);
    } else {
        updateSum(a->right, stationID, load);
    }
}


pAVL createAVL(pStation s) {
    if(s == NULL){
        exit_with_message("ERROR: station pointer is NULL.", ERR_PTR_ALLOC);
    }
    pAVL a = malloc(sizeof(AVL));
    if(a == NULL)
    {
        exit_with_message("ERROR: AVL allocation failed.", ERR_AVL_ALLOC);
    }

    a->station = s;
    a->left = NULL;
    a->right = NULL;
    a->balance = 0;
    return a;
}


pAVL leftRotation(pAVL a){
    if(a == NULL || a->right == NULL){
        exit_with_message("ERROR: AVL sub-tree doesn't exist.", ERR_NULL_AVL);
    }

    pAVL pivot = a->right;      // Init the pivot as the right child of 'a'
    int ba_a = a->balance;      // Temporary balance variable of:
    int ba_p = pivot->balance;  // The sub-tree 'a' (ba_a) and the pivot (ba_p)
    if(pivot->left != NULL){
        a->right = pivot->left; // 'a' takes the left child of the pivot as its right child
    } else{
        a->right = NULL;
    }
    pivot->left = a;        // Left rotation: the pivot become the parent of 'a'

    a->balance = ba_a - max(ba_p, 0) - 1;               // Updated 'a' balance
    pivot->balance = min3(ba_a-2, ba_a+ba_p-2, ba_p-1); // Updated pivot balance

    return pivot;
}


pAVL rightRotation(pAVL a){
    if(a == NULL || a->left == NULL){
        exit_with_message("ERROR: AVL sub-tree doesn't exist", ERR_NULL_AVL);
    }

    pAVL pivot = a->left;       // Init the pivot as the left child of 'a'
    int ba_a = a->balance;      // Remporary balance variable of:
    int ba_p = pivot->balance;  // Rhe sub-tree 'a' (ba_a) and the pivot (ba_p)

    if(pivot->right != NULL){
        a->left = pivot->right; // 'a' takes the right child of the pivot as its left child
    } else{
        a->left = NULL;
    }
    pivot->right = a;       // Rght rotation: the pivot become the parent of 'a'

    a->balance = ba_a - min(ba_p, 0) + 1;               // Updated 'a' balance
    pivot->balance = max3(ba_a+2, ba_a+ba_p+2, ba_p+1); // Updated pivot balance

    return pivot;
}


pAVL balanceAVL(pAVL a){
    if(a == NULL){
        exit_with_message("ERROR: AVL sub-tree doesn't exist.", ERR_NULL_AVL);
    }
    if(a->balance >= 2){                // Left rotation
        if(a->right->balance >= 0){     // Single left rotation
            return leftRotation(a);
        }
        else{                           // Double left rotation
            a->right = rightRotation(a->right);
            return leftRotation(a);
        }
    }
    if(a->balance <= -2){               // Right rotation
        if(a->left->balance <= 0){      // Single right rotation
            return rightRotation(a);
        }
        else{                           // Double left rotation
            a->left = leftRotation(a->left);
            return rightRotation(a); 
        }
    }
    return a; // if the AVL is already balanced
}


pAVL insertAVL(pAVL a, pStation s, int* h){
    if(s == NULL){
        exit_with_message("ERROR: Station doesn't exist.", ERR_INVALID_STATION);
    }

    if(a == NULL){
        *h = 1; // new node increase the height of his parent node
        return createAVL(s);
    }
    if(a->station == NULL){
        exit_with_message("ERROR: station doesn't exist.", ERR_INVALID_STATION);
    }
    else if(s->id < a->station->id){
        a->left = insertAVL(a->left, s, h);
        *h = (*h) * (*h) * (-1);    // make the height negative
    }
    else if(s->id > a->station->id){
        a->right = insertAVL(a->right, s, h);
        *h = (*h) * (*h);           // make the height positive
    }
    else{
        *h = 0;
        return a;
    }

    if(*h != 0){
        a->balance += *h;

        if((*h == -1 && a->balance >= 0) || (*h == 1 && a->balance <= 0)){ // if the node is balanced
            *h = 0;
        }
        else{
            a = balanceAVL(a);
            *h = (a->balance == 0) ? 0 : 1;
        }
    }
    return a;
}


void cleanAVL(pAVL a) {
    if(a == NULL)
    {
        return;
    }
    a->station=NULL;
    cleanAVL(a->left);
    cleanAVL(a->right);
    // créer fonction pour cleanArray
    free(a);
    a = NULL;
}