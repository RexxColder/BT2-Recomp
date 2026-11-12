#include "m2c_macros.h"

void func_002E0510(s32 arg0, s32 *arg1, s32 *arg2) {
    void *temp_a0;

    temp_a0 = arg0 + 0x78;
    *arg1 = M2C_FIELD(temp_a0, s32 *, 0x18);
    *arg2 = M2C_FIELD(temp_a0, s32 *, 0x1C);
}
