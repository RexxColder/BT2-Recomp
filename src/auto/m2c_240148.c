#include "m2c_macros.h"

s32 func_001F9908(s32);                             /* extern */
s32 func_00211288(s16);                             /* extern */
void *func_0023FF80();                              /* extern */

s32 func_00240148(void *arg0) {
    s32 temp_v0;
    s32 var_v0;
    void *var_s0;
    void *var_s1;

    var_s0 = arg0;
    var_s1 = func_0023FF80(arg0);
    temp_v0 = func_00211288(M2C_FIELD(M2C_FIELD(var_s0, void **, 0x68), s16 *, 0x10));
    var_s0 = (void *) M2C_FIELD(var_s1, s8 *, 0x32);
    var_v0 = (s32) (M2C_FIELD(var_s1, s32 *, 4) * func_001F9908(temp_v0)) / 100;
    if ((s32) var_s0 > 0) {
        var_v0 = var_v0 / (s32) var_s0;
    }
    return var_v0;
}
