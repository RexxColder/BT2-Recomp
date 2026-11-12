#include "m2c_macros.h"

s32 BtlChar_GetPos(s32);                            /* extern */
s32 func_00211288(M2C_UNK);                         /* extern */
M2C_UNK func_003126C8(M2C_UNK, s32);                /* extern */

void func_002109C8(void *arg0, M2C_UNK arg1) {
    s32 var_v0;

    if (M2C_FIELD(arg0, s32 *, 0x1534) == 0) {
        var_v0 = func_00211288(1);
    } else {
        var_v0 = func_00211288(0);
    }
    func_003126C8(arg1, BtlChar_GetPos(var_v0) + 0x50);
}
