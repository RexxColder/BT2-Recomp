#include "m2c_macros.h"

s32 Queue_Count(void *arg0) {
    M2C_UNK *temp_v0;
    M2C_UNK *var_v1;
    s32 var_a0;

    var_v1 = M2C_FIELD(arg0, M2C_UNK **, 0xC);
    var_a0 = 0;
    if (var_v1 != NULL) {
        do {
            temp_v0 = *var_v1;
            var_a0 += 1;
            var_v1 = temp_v0;
        } while (temp_v0 != NULL);
    }
    return var_a0;
}
