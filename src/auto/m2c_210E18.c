#include "m2c_macros.h"

void *func_00211288(M2C_UNK);                       /* extern */
s32 func_00211310(void *, M2C_UNK, M2C_UNK);        /* extern */
s32 func_00217488(void *);                          /* extern */

s32 func_00210E18(void *arg0) {
    void *var_v0;

    if (M2C_FIELD(arg0, s32 *, 0x1534) == 0) {
        var_v0 = func_00211288(1);
    } else {
        var_v0 = func_00211288(0);
    }
    if (func_00211310(arg0, 9, 2) != 0) {
        return M2C_FIELD(var_v0, s32 *, 0xC04);
    }
    return func_00217488(var_v0);
}
