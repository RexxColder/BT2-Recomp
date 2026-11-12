#include "m2c_macros.h"

extern void *D_00387930;

s32 func_00211270(void) {
    s32 var_v0;

    var_v0 = 0;
    if (D_00387930 != NULL) {
        var_v0 = M2C_FIELD(D_00387930, s32 *, 4);
    }
    return var_v0;
}
