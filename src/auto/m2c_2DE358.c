#include "m2c_macros.h"

void func_002DE358(void *arg0, s32 arg1, s32 arg2) {
    void *temp_a0;

    temp_a0 = arg0 + 0x3EC;
    M2C_FIELD(arg0, s32 *, 0x3EC) = arg1;
    M2C_FIELD(temp_a0, s32 *, 4) = arg2;
    M2C_FIELD(temp_a0, s32 *, 8) = 0;
}
