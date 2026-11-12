#include "m2c_macros.h"

s32 func_002CD108(void *arg0) {
    s32 temp_v1;
    s32 var_a1;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0x4C);
    var_a1 = M2C_FIELD(arg0, s32 *, 0x48);
    if ((temp_v1 >= 2) && ((temp_v1 < 5) || (temp_v1 == 6))) {
        var_a1 = 2;
    }
    return var_a1;
}
