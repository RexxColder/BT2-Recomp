#include "m2c_macros.h"

s32 func_002CF648(s32 arg0, s32 arg1) {
    u8 *q = (u8 *)arg0 + arg1 * 0x74 + 0x1348;
    s32 var_v0 = 0;

    if (*(s32 *)q != 0) {
        var_v0 = *(s32 *)(q + 8) >= *(s32 *)(q + 4);
    }
    return var_v0;
}
