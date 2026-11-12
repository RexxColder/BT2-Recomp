#include "m2c_macros.h"

s32 func_00203C58(s32, M2C_UNK);                    /* extern */
s32 func_00211288(s16);                             /* extern */
void *func_0023FF80();                              /* extern */

s32 func_002403E0(void *arg0) {
    u32 var_s0;

    var_s0 = M2C_FIELD(func_0023FF80(arg0), u32 *, 0xC);
    if (func_00203C58(func_00211288(M2C_FIELD(M2C_FIELD(arg0, void **, 0x68), s16 *, 0x10)), 0x200) != 0) {
        var_s0 = (u32) ((s32) (var_s0 + (var_s0 >> 0x1F)) >> 1);
    }
    return (s32) var_s0;
}
