#include "m2c_macros.h"

s32 func_002D1800(void *arg0, s32 *arg1, s32 *arg2) {
    s32 temp_v1;

    temp_v1 = M2C_FIELD(arg0, s32 *, 0x48);
    if ((temp_v1 != 4) && (temp_v1 != -4) && (temp_v1 != 6) && (temp_v1 != -6)) {
        *arg1 = -1;
        *arg2 = 1;
        return 0;
    }
    return 1;
}
