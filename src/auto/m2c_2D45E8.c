#include "m2c_macros.h"

s32 func_002D4630();                                /* extern */

s32 func_002D45E8(void *arg0) {
    s32 temp_v0;
    s32 var_v0;

    var_v0 = func_002D4630(arg0);
    if ((var_v0 != 0) && ((temp_v0 = M2C_FIELD(arg0, s32 *, 0xC), (temp_v0 == 0x6B)) || (var_v0 = 0, ((temp_v0 < 0x6E) == 0)))) {
        var_v0 = 1;
    }
    return var_v0;
}
