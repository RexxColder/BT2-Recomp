#include "m2c_macros.h"

s32 func_002B95F8(void *, s32);                           /* extern */

s32 func_002B5CB8(void *arg0) {
    s32 var_v1;

    var_v1 = func_002B95F8(arg0, M2C_FIELD(arg0, s32 *, 0xB8));
    if ((var_v1 == 0x51) || (var_v1 == 0x61)) {
        var_v1 = 0x41;
    }
    return var_v1;
}
