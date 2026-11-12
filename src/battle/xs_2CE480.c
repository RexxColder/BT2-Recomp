#include "m2c_macros.h"

M2C_UNK (*func_002D07B0(s32, s32))(s32, M2C_UNK, void *); /* extern */

void func_002CE480(s32 arg0, s32 arg1, M2C_UNK arg2) {
    M2C_UNK (*temp_v0)(s32, M2C_UNK, void *);
    void *temp_s0;

    temp_s0 = arg0 + 0x950;
    M2C_FIELD(temp_s0, s32 *, 4) = (s32) (M2C_FIELD(temp_s0, s32 *, 4) + arg1);
    temp_v0 = func_002D07B0(arg0, 0x25);
    if (temp_v0 != NULL) {
        temp_v0(arg0, arg2, temp_s0);
    }
}
