#include "m2c_macros.h"

extern void *D_00387930;

s32 func_0020A138(void) {
    s32 var_v0;

    var_v0 = 0;
    if (D_00387930 != NULL) {
        var_v0 = M2C_FIELD(D_00387930, s32 *, 0x48);
    }
    return var_v0;
}
