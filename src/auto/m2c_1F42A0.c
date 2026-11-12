#include "m2c_macros.h"

extern void *D_00387920;

s32 func_001F42A0(void) {
    s32 var_v0;

    var_v0 = 0;
    if (D_00387920 != NULL) {
        var_v0 = M2C_FIELD(D_00387920, s32 *, 0x2C);
    }
    return var_v0;
}
