#include "common.h"

s32 func_002DE398(s32 arg0, s32 arg1);
s32 func_00303D48(s32 arg0, s32 arg1);

s32 func_002DE618(s32 arg0, u8 *arg1, s32 *arg2) {
    s32 temp_s0;
    s32 var_v0;
    s32 temp_v0;
    s32 temp_a1;
    s32 vt;
    s32 r;

    temp_v0 = func_00303D48(*(s32 *)arg1, *(s32 *)(arg1 + 4));
    var_v0 = -1;
    if (temp_v0 != 0) {
        temp_s0 = func_002DE398(arg0, temp_v0);
        vt = *(s32 *)temp_v0;
        r = ((s32 (*)(s32, s32))(*(s32 *)(vt + 0x24)))(temp_v0, 1);
        *arg2 = *(s32 *)(arg1 + 4) - r;
        temp_a1 = *(s32 *)temp_v0;
        ((void (*)(s32, s32))(*(s32 *)(temp_a1 + 0xC)))(temp_v0, temp_a1);
        var_v0 = temp_s0;
    }
    return var_v0;
}
