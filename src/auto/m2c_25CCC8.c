#include "m2c_macros.h"

extern void *D_00387A40;

s32 func_0025CCC8(s32 arg0) {
    s32 temp_v0;
    s32 temp_v1;

    temp_v1 = 1 << arg0;
    temp_v0 = M2C_FIELD(D_00387A40, s32 *, 0x38020);
    if (!(temp_v0 & temp_v1)) {
        M2C_FIELD(D_00387A40, s32 *, 0x38020) = (s32) (temp_v0 | temp_v1);
        return 1;
    }
    return 0;
}
