#include "m2c_macros.h"

extern M2C_UNK D_003A0320 __attribute__((section(".data")));

void func_00307758(s32 arg0) {
    M2C_UNK (*temp_v0)(s32);
    s32 temp_a0;

    temp_a0 = arg0 * 2;
    temp_v0 = *(temp_a0 + &D_003A0320);
    if (temp_v0 != NULL) {
        temp_v0(M2C_FIELD((&D_003A0320 + temp_a0), s32 *, 4));
    }
}
