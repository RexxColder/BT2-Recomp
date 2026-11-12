#include "common.h"

s32 func_002D2F30(s32 arg0, s32 arg1) {
    s32 temp_v0;
    s32 var_a0;
    s32 var_s1;
    u8 *var_s0;

    var_a0 = 0;
    var_s0 = (u8 *)(arg0 + 0x1F30);
    var_s1 = 0;
    while (var_s1 < 9) {
        var_s1 += 1;
        temp_v0 = *(s32 *)(var_s0 + 0xC);
        var_s0 += 0x44;
        if (temp_v0 == 0) {
            continue;
        }
        var_a0 = ((s32 (*)(s32, s32, s32, s32))(*(s32 *)(temp_v0 + (arg1 << 2))))(arg0, 0, 0, 0);
        if (var_a0 != 0) {
            break;
        }
    }
    return var_a0;
}
