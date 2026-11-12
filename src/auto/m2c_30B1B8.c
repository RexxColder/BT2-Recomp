#include "m2c_macros.h"

M2C_UNK func_002FC550(M2C_UNK);                     /* extern */
s32 func_002FC7E8(s32, M2C_UNK, s32);               /* extern */

s32 func_0030B1B8(void *arg0) {
    s32 temp_s0;
    s32 var_v0;

    func_002FC550(0x4000);
    temp_s0 = func_002FC7E8(M2C_FIELD(arg0, s32 *, 0x18), 1, arg0 + 0x14);
    func_002FC550(0x4001);
    var_v0 = 0;
    if (temp_s0 >= 0) {
        var_v0 = M2C_FIELD(arg0, s32 *, 0x14) != 1;
    }
    return var_v0;
}
