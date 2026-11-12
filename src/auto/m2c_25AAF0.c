#include "m2c_macros.h"

extern void *D_00387A30;

f32 func_0025AAF0(void) {
    f32 var_f0;

    var_f0 = 0.0f;
    if (M2C_FIELD(D_00387A30, s32 *, 0x2B0) != 0) {
        var_f0 = M2C_FIELD(D_00387A30, f32 *, 0x2E0);
    }
    return var_f0;
}
