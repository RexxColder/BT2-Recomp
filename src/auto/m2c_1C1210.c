#include "m2c_macros.h"

s32 func_001C1210(void *arg0) {
    s32 var_v0;
    void *temp_a0;

    var_v0 = 0;
    if (arg0 != NULL) {
        temp_a0 = M2C_FIELD(arg0, void **, 0x38);
        if (temp_a0 != NULL) {
            var_v0 = M2C_FIELD(temp_a0, s32 *, 0xACC) != 3;
        }
    }
    return var_v0;
}
