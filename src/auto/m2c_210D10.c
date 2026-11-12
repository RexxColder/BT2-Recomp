#include "m2c_macros.h"

f32 func_002086B0(s32);                         /* extern */
void *func_00211288(M2C_UNK);                       /* extern */

void func_00210D10(void *arg0) {
    void *var_v0;

    if (M2C_FIELD(arg0, s32 *, 0x1534) == 0) {
        var_v0 = func_00211288(1);
    } else {
        var_v0 = func_00211288(0);
    }
    func_002086B0(M2C_FIELD(var_v0, s32 *, 0x1534));
}
