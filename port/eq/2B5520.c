#include "common.h"

s32 Rand_Range(s32 arg0);
s32 func_002B64F0(s32 arg0);
s32 func_002D82C0(s32 arg0, s32 arg1);
extern s32 D_003784C8 __attribute__((section(".data")));

s32 func_002B5520(s32 arg0, s32 *arg1, s32 arg2, s32 arg3) {
    s32 temp_s0;
    s32 var_s1;
    u32 temp_v1;

    var_s1 = 0;
    temp_v1 = (u32)arg1[0x58 / 4];
    if (temp_v1 < 3U) {
        if (temp_v1 != 0) {
            var_s1 = 2;
        } else {
            Rand_Range((s32)&D_003784C8);
        }
    } else if (temp_v1 == 3) {
        if (*(s8 *)((u8 *)arg1 + 0x6C) == 0) {
            var_s1 = 2;
        }
    } else {
        Rand_Range((s32)&D_003784C8);
    }
    temp_s0 = func_002B64F0(arg0);
    if (temp_s0 == 1) {
        var_s1 = ((func_002D82C0(arg2, arg3) ^ temp_s0) == 0) ? 2 : var_s1;
    }
    return var_s1;
}
