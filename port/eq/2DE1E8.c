#include "common.h"

s32 func_002E0750(u8 *arg0, s32 *arg1, s32 *arg2, s32 *arg3);
s32 func_002DDD70(s32 arg0, s32 arg1, s32 arg2);

s32 func_002DE1E8(u8 *arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    s32 temp_a0;
    s32 var_v0;

    if (func_002E0750(arg0, arg1, arg2, arg3) != 0) {
        return func_002DDD70(0, 0xFF03020F, 0x3FFFF);
    }
    *arg1 = (s32)((u32)*(s32 *)(arg0 + 0x2AC) << 11);
    *arg2 = *(s32 *)(arg0 + 0x2BC);
    temp_a0 = *(s32 *)(arg0 + 0x2A8);
    if (temp_a0 != 0x3FFFF) {
        var_v0 = (s32)((u32)*(s32 *)(arg0 + 0x2BC) * (u32)temp_a0) / 1800;
    } else {
        var_v0 = -1;
    }
    *arg3 = var_v0;
    return 0;
}
