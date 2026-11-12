#include "m2c_macros.h"

extern void *D_003878F4;

void BtlFacade_SetCtrl10D(void) {
    if (M2C_FIELD(D_003878F4, s32 *, 4) != 0) {
        M2C_FIELD(D_003878F4, s32 *, 4) = 0;
    }
}
