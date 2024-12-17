/*
    Contains calculation functions
*/


#include "calculations.h"


// Updates station consumption sum
/*void updateSum(pAVL a, int stationID, long load) {
    if(a == NULL) {
        return;
    }

    if(a->station->id == stationID) {
        a->station->consumption_sum += load;
    }
    if(a->station->id < stationID) {
        updateSum(a->left, s, load);
    } else {
        updateSum(a->right, s, load);
    }
}*/