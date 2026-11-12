#include "m2c_macros.h"

extern void *D_003878F4;

void BtlFacade_ClearCtrl10D(void) {
    void *temp_v1;
    void *temp_v1_2;

    temp_v1 = M2C_FIELD(D_003878F4, void **, 4);
    if (temp_v1 != NULL) {
        temp_v1_2 = M2C_FIELD(temp_v1, void **, 0x38);
        if (!(M2C_FIELD(temp_v1, u8 *, 0) & 1 & 0xFF)) {
            M2C_FIELD(temp_v1_2, s32 *, 0x38) = (s32) (M2C_FIELD(temp_v1_2, s32 *, 0x38) | 0x10);
        }
    }
}
