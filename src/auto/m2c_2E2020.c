#include "m2c_macros.h"

s32 func_002E1A38();                                /* extern */
M2C_UNK func_002E1C98(M2C_UNK, M2C_UNK);            /* extern */

void func_002E2020(s32 arg0, s32 *arg1, s32 *arg2) {
    void *temp_s0;

    temp_s0 = arg0 + 0x160;
    if (func_002E1A38(arg0) != 0) {
        func_002E1C98(0, 0xFF03020E);
        return;
    }
    *arg1 = M2C_FIELD(temp_s0, s32 *, 0xD0);
    *arg2 = M2C_FIELD(temp_s0, s32 *, 0xD4);
}
