#include "m2c_macros.h"

void func_002E0F10(void *arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    void *temp_a0;

    temp_a0 = arg0 + 8;
    *arg3 = M2C_FIELD(arg0, s32 *, 8);
    *arg1 = M2C_FIELD(temp_a0, s32 *, 4);
    *arg2 = M2C_FIELD(temp_a0, s32 *, 8);
}
