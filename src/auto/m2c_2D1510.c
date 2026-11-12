#include "m2c_macros.h"

s32 func_002D1510(s32 arg0, s32 *arg1, s32 *arg2) {
    void *temp_a0;

    temp_a0 = arg0 + 0xD30;
    *arg1 = M2C_FIELD(temp_a0, s32 *, 0x28C);
    *arg2 = M2C_FIELD(temp_a0, s32 *, 0x290);
    return 0;
}
