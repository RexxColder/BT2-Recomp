#include "m2c_macros.h"

M2C_UNK func_002CFE88(s32, M2C_UNK, M2C_UNK, M2C_UNK);                         /* extern */
s32 func_002E0A98(s32, M2C_UNK, M2C_UNK);                             /* extern */

void func_002CFE38(void *arg0, s32 arg1, s32 arg2, s32 *arg3) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0xDC0);
    if (temp_v0 != 0) {
        func_002CFE88(temp_v0, arg1, arg2, arg3);
        return;
    }
    *arg3 = func_002E0A98(M2C_FIELD(arg0, s32 *, 0xDA8), arg1, arg2);
}
