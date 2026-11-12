#include "m2c_macros.h"

void func_002D5BA8(void *arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0xC);
    M2C_FIELD(arg0, s32 *, 0xC) = (s32) -temp_v0;
    M2C_FIELD(arg0, s32 *, 0) = (s32) (M2C_FIELD(arg0, s32 *, 0) + (temp_v0 * (M2C_FIELD(arg0, s32 *, 8) - 1)));
}
