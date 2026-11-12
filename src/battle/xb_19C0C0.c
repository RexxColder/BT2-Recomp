#include "m2c_macros.h"

s32 func_001CCA88(s32);                             /* extern */

s32 func_0019C0C0(void *arg0) {
    s32 *var_s0;
    s32 var_s1;
    s32 var_s2;

    var_s1 = 1;
    var_s2 = 0;
    var_s0 = (s32 *) ((char *) M2C_FIELD(arg0, s32 *, 0x38) + 0x34);
    do {
        if (func_001CCA88(*var_s0) != 0) {
            var_s2 = 1;
        } else {
            *var_s0 = 0;
        }
        var_s1 -= 1;
        var_s0 += 1;
    } while (var_s1 >= 0);
    return var_s2;
}
