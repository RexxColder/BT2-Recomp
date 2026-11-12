#include "m2c_macros.h"

extern void *gEftStruggle;

f32 func_001A7DA8(void) {
    f32 var_f0;

    var_f0 = 0.0f;
    if (gEftStruggle != NULL) {
        var_f0 = M2C_FIELD(gEftStruggle, f32 *, 0x630) + 10.0f;
    }
    return var_f0;
}
