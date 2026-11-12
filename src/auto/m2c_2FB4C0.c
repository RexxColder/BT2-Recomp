#include "m2c_macros.h"

M2C_UNK func_002F9300(M2C_UNK *);                   /* extern */
extern M2C_UNK D_0037DDA8 __attribute__((section(".data")));

s32 func_002FB4C0(void *arg0) {
    s32 (*temp_v0)(s32, M2C_UNK, M2C_UNK, M2C_UNK);
    s32 var_v1;

    var_v1 = 0;
    if (arg0 == NULL) {
        func_002F9300(&D_0037DDA8);
        return 0;
    }
    temp_v0 = M2C_FIELD(M2C_FIELD(arg0, void **, 0), s32 (**)(s32, M2C_UNK, M2C_UNK, M2C_UNK), 0x60);
    if (temp_v0 != NULL) {
        var_v1 = temp_v0(M2C_FIELD(arg0, s32 *, 4), 0x12B, 0, 0);
    }
    return var_v1;
}
