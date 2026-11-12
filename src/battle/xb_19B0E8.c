#include "m2c_macros.h"

s32 EftPtcl3_IsAlive(s32);                          /* extern */

s32 func_0019B0E8(void *arg0) {
    s32 *var_s0;
    s32 var_s1;
    s32 var_s2;

    var_s1 = 2;
    var_s2 = 0;
    var_s0 = (s32 *) ((char *) M2C_FIELD(arg0, s32 *, 0x38) + 0x10);
    do {
        if (EftPtcl3_IsAlive(*var_s0) != 0) {
            var_s2 = 1;
        } else {
            *var_s0 = 0;
        }
        var_s1 -= 1;
        var_s0 += 1;
    } while (var_s1 >= 0);
    return var_s2;
}
