#include "m2c_macros.h"

s32 func_002BEC88();                                /* extern */
s32 func_002CE750();                                /* extern */
s32 func_002F39D8(s32, s32, s32);                   /* extern */
M2C_UNK func_002F5C10(s32, M2C_UNK);                /* extern */

s32 func_002BEC18(void *arg0) {
    s32 var_v0;
    s32 var_v0_2;

    if (func_002CE750() != 1) {
        var_v0_2 = func_002F39D8(M2C_FIELD(arg0, s32 *, 0xC), M2C_FIELD(arg0, s32 *, 0x18), M2C_FIELD(arg0, s32 *, 0x14));
    } else {
        var_v0_2 = func_002BEC88();
    }
    var_v0 = 0;
    if (var_v0_2 != 0) {
        func_002F5C10(var_v0_2, 0);
        var_v0 = var_v0_2;
    }
    return var_v0;
}
