#include "m2c_macros.h"

s32 func_002E1A38();                                /* extern */
s32 func_002E1C98(M2C_UNK, M2C_UNK);                /* extern */
M2C_UNK func_002E2230(s32);                         /* extern */
s32 func_002E23A0(s32, M2C_UNK);                    /* extern */

s32 func_002E21B0(s32 arg0, M2C_UNK arg1) {
    s32 temp_v0;

    if (func_002E1A38(arg0) != 0) {
        return func_002E1C98(0, 0xFF03020C);
    }
    temp_v0 = func_002E23A0(arg0, arg1);
    if (temp_v0 == 0) {
        func_002E2230(arg0);
    }
    return temp_v0;
}
