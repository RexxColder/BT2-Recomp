#include "m2c_macros.h"

s32 func_002E1A38();                                /* extern */
M2C_UNK func_002E1C98(M2C_UNK, M2C_UNK);            /* extern */

void func_002E1F30(s32 arg0, s32 *arg1) {
    s32 *var_s1;
    void *var_s0;

    var_s0 = arg0 + 0x160;
    var_s1 = arg1;
    if (func_002E1A38(arg0) != 0) {
        func_002E1C98(0, 0xFF03020D);
        return;
    }
    *var_s1 = M2C_FIELD(var_s0, s32 *, 0x2D4);
}
