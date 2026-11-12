#include "m2c_macros.h"

extern void *D_00387930;

f32 func_0020B4E8(void) {
    f32 var_f0;

    if (D_00387930 != NULL) {
        var_f0 = (f32) M2C_FIELD(D_00387930, s32 *, 0x24) / 90.0f;
        if (var_f0 > 1.0f) {
            var_f0 = 1.0f;
        }
        if (var_f0 < 0.0f) {
            return 0.0f;
        }
        /* Duplicate return node #7. Try simplifying control flow for better match */
        return var_f0;
    }
    var_f0 = 1.0f;
    return var_f0;
}
