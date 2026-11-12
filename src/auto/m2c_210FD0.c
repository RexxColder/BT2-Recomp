#include "m2c_macros.h"

void *func_00211288(M2C_UNK);                       /* extern */
M2C_UNK func_003126C8(M2C_UNK, s32);                /* extern */

void func_00210FD0(void *arg0, M2C_UNK arg1) {
    void *var_v0;

    if (M2C_FIELD(arg0, s32 *, 0x1534) == 0) {
        var_v0 = func_00211288(1);
    } else {
        var_v0 = func_00211288(0);
    }
    func_003126C8(arg1, M2C_FIELD(M2C_FIELD(var_v0, void **, 0x1530), s32 *, 0xF40));
}
