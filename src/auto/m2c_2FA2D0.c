#include "m2c_macros.h"

s32 func_002FA2D0(void *arg0) {
    s32 (*temp_v0)(s32, M2C_UNK, M2C_UNK, M2C_UNK);
    s32 var_v0;
    s32 var_v1;

    var_v0 = 0;
    if (arg0 != NULL) {
        temp_v0 = M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 (**)(s32, M2C_UNK, M2C_UNK, M2C_UNK), 0x60);
        var_v1 = 0;
        if (temp_v0 != NULL) {
            var_v1 = temp_v0(M2C_FIELD(arg0, s32 *, 4), 0x192, 0, 0);
        }
        var_v0 = var_v1;
    }
    return var_v0;
}
