/*
    Contains calculation functions
*/


#include "calculations.h"


// Updates station consumption sum
void updateSum(pAVL a, int stationID, long load) {
    if(a == NULL) {
        exit_with_message("ERROR: station doesn't exist.", ERROR_INVALID_STATION);
    }

    if(a->station->id == stationID) {
        a->station->consumption_sum += load;
    } else if(a->station->id > stationID) {
        updateSum(a->left, stationID, load);
    } else {
        updateSum(a->right, stationID, load);
    }
}