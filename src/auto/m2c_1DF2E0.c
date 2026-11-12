#include "m2c_macros.h"

extern void *D_003878DC;

s32 func_001DF2E0(void) {
    s32 var_v0;

    var_v0 = 0;
    if (D_003878DC != NULL) {
        var_v0 = M2C_FIELD(D_003878DC, s32 *, 0x218);
    }
    return var_v0;
}
