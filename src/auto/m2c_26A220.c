#include "m2c_macros.h"

f32 func_0026A220(void *arg0) {
    f32 var_f0;
    void *temp_v0;

    temp_v0 = M2C_FIELD(arg0, void **, 0xE90);
    var_f0 = 1.0f;
    if (temp_v0 != NULL) {
        var_f0 = M2C_FIELD(temp_v0, f32 *, 0x14);
    }
    return var_f0;
}
