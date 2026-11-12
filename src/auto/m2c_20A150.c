#include "m2c_macros.h"

extern void *D_00387930;

f32 func_0020A150(void) {
    f32 var_f0;

    var_f0 = 0.0f;
    if (D_00387930 != NULL) {
        var_f0 = M2C_FIELD(D_00387930, f32 *, 0x4C);
    }
    return var_f0;
}
