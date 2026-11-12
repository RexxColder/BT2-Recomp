#include "m2c_macros.h"

void func_002E0EF0(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *temp_v0;

    temp_v0 = arg0 + 8;
    M2C_FIELD(arg0, s32 *, 8) = arg3;
    M2C_FIELD(temp_v0, s32 *, 4) = arg1;
    M2C_FIELD(temp_v0, s32 *, 8) = arg2;
    M2C_FIELD(arg0, s32 *, 4) = 1;
}
