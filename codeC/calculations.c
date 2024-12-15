/*
    Contains calculation functions
*/


#include "calculations.h"


// Update the sum of a station's consumption
pStation updateSum(pStation s, long load) {

    if(s == NULL) {
        exit_with_message("ERROR: station doesn't exist.", ERROR_INVALID_STATION);
        return NULL;
    } else {
        s->consumption_sum += load;
        return s;
    }
}