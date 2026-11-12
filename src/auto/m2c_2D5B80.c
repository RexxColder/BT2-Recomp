#include "m2c_macros.h"

void func_002D5B80(void *arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x10);
    M2C_FIELD(arg0, s32 *, 0x10) = (s32) -temp_v0;
    M2C_FIELD(arg0, s32 *, 4) = (s32) (M2C_FIELD(arg0, s32 *, 4) + (temp_v0 * (M2C_FIELD(arg0, s32 *, 0xC) - 1)));
}
