/*
    Contains calculation functions
*/


#include "calculations.h"


// Updates station consumption sum
void updateSum(pStation s, long load) {
    if(s == NULL) {
        exit_with_message("ERROR: station doesn't exist.", ERROR_STINVALID_STATION);
    }

    s->consumption_sum += load;
}