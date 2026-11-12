#include "m2c_macros.h"

s32 func_002E1A38();                                /* extern */
M2C_UNK func_002E1C98(M2C_UNK, M2C_UNK);            /* extern */

void func_002E1F90(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    void *temp_s0;

    temp_s0 = arg0 + 0x160;
    if (func_002E1A38(arg0) != 0) {
        func_002E1C98(0, 0xFF03020F);
        return;
    }
    *arg1 = M2C_FIELD(temp_s0, s32 *, 0x2D8) << 0xB;
    *arg2 = M2C_FIELD(temp_s0, s32 *, 0xE4);
    *arg3 = -1;
}
