#include "m2c_macros.h"

void *func_00211288(M2C_UNK);                       /* extern */

f32 func_00210EA0(void *arg0) {
    void *var_v0;

    if (M2C_FIELD(arg0, s32 *, 0x1534) == 0) {
        var_v0 = func_00211288(1);
    } else {
        var_v0 = func_00211288(0);
    }
    return M2C_FIELD(var_v0, f32 *, 0x930);
}
