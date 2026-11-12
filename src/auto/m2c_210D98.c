#include "m2c_macros.h"

s32 func_00211288(M2C_UNK);                         /* extern */
M2C_UNK func_0023F430(s32);                         /* extern */

void func_00210D98(void *arg0) {
    s32 var_v0;

    if (M2C_FIELD(arg0, s32 *, 0x1534) == 0) {
        var_v0 = func_00211288(1);
    } else {
        var_v0 = func_00211288(0);
    }
    func_0023F430(var_v0);
}
