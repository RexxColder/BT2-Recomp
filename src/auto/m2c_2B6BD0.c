#include "m2c_macros.h"

M2C_UNK Rand_Range(M2C_UNK *);                      /* extern */
M2C_UNK func_002B6700(M2C_UNK);                     /* extern */
s32 func_002CE5C8(s32);                             /* extern */
extern M2C_UNK D_00378AB8 __attribute__((section(".data")));

s32 func_002B6BD0(void *arg0) {
    s32 var_v0;

    var_v0 = func_002CE5C8(M2C_FIELD(arg0, s32 *, 0x3C));
    if (var_v0 != 0) {
        func_002B6700(-0x133);
        Rand_Range(&D_00378AB8);
        var_v0 = -0x133;
    }
    return var_v0;
}
