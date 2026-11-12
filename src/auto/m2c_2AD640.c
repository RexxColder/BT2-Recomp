#include "m2c_macros.h"

extern s32 D_003B2690 __attribute__((section(".data")));

f32 func_002AD640(void) {
    f32 var_f0;

    var_f0 = -120.0f;
    if (D_003B2690 != 0) {
        var_f0 = -150.0f;
    }
    return var_f0;
}
