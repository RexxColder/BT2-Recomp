#include "m2c_macros.h"

M2C_UNK func_0020EAA8(s32, M2C_UNK, M2C_UNK);       /* extern */
s32 func_00211288(M2C_UNK);                         /* extern */

void func_002108C0(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s32 var_v0;

    if (M2C_FIELD(arg0, s32 *, 0x1534) == 0) {
        var_v0 = func_00211288(1);
    } else {
        var_v0 = func_00211288(0);
    }
    func_0020EAA8(var_v0, arg1, arg2);
}
