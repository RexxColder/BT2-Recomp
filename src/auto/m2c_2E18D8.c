#include "m2c_macros.h"

s32 func_002E1A38();                                /* extern */
M2C_UNK func_002E1C98(M2C_UNK, M2C_UNK);            /* extern */

void func_002E18D8(s32 *arg0) {
    if (func_002E1A38(arg0) != 0) {
        func_002E1C98(0, 0xFF030201);
        return;
    }
    *arg0 = 1;
}
