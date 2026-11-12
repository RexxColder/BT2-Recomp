#include "m2c_macros.h"

s32 func_00182B10(void *arg0) {
    s32 var_v0;
    void *temp_a0;

    var_v0 = 1;
    if (arg0 != NULL) {
        temp_a0 = M2C_FIELD(arg0, void **, 0x38);
        if (temp_a0 != NULL) {
            var_v0 = ((s32) M2C_FIELD(temp_a0, s32 *, 0xA80) >> 1) & 1;
        }
    }
    return var_v0;
}
