#include "m2c_macros.h"

extern void *D_00387A30;

f32 func_0025AAD0(void) {
    f32 var_f0;
    void *temp_v0;

    var_f0 = 0.0f;
    temp_v0 = M2C_FIELD(D_00387A30, void **, 0x2B0);
    if (temp_v0 != NULL) {
        var_f0 = M2C_FIELD(temp_v0, f32 *, 0x14);
    }
    return var_f0;
}
