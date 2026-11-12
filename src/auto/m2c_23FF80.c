#include "m2c_macros.h"

void *func_00211288(s16);                           /* extern */

s32 func_0023FF80(void *arg0) {
    s32 var_v0;
    void *temp_v1;

    temp_v1 = M2C_FIELD(arg0, void **, 0x68);
    var_v0 = 0;
    if (temp_v1 != NULL) {
        var_v0 = M2C_FIELD(M2C_FIELD(func_00211288(M2C_FIELD(temp_v1, s16 *, 0x10)), void **, 0x1530), s32 *, 0x978) + (M2C_FIELD(M2C_FIELD(arg0, void **, 0x68), s16 *, 0x18) * 0x38);
    }
    return var_v0;
}
