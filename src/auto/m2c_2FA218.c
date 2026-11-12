#include "m2c_macros.h"

M2C_UNK func_002F9300(M2C_UNK *);                   /* extern */
extern M2C_UNK D_0037D578 __attribute__((section(".data")));

s32 func_002FA218(void *arg0) {
    s32 (*temp_v0)(s32, M2C_UNK, M2C_UNK, M2C_UNK);
    s32 var_v1;

    if (arg0 == NULL) {
        func_002F9300(&D_0037D578);
        return -1;
    }
    temp_v0 = M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 (**)(s32, M2C_UNK, M2C_UNK, M2C_UNK), 0x60);
    var_v1 = 0x7FFFFFFF;
    if (temp_v0 != NULL) {
        var_v1 = temp_v0(M2C_FIELD(arg0, s32 *, 4), 0x12C, 0, 0);
    }
    return var_v1;
}
