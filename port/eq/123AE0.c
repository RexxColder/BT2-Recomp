#include "common.h"

s32 func_002745F8(s32 arg0, s32 arg1, s32 arg2);

f32 func_00123AE0(s32 arg0, s32 arg1, s32 arg2) {
    f32 var_f0;
    s16 *var_v0;
    s32 temp_a2;
    s32 temp_v0;
    s32 var_a0;
    s8 temp_a1;
    u8 *p;

    p = (u8 *)arg0;
    var_f0 = 0.0f;
    if ((arg1 != 0xFF) && (arg2 >= 0)) {
        temp_v0 = (arg1 * *(s32 *)(p + 0xC)) + arg2;
        temp_a2 = temp_v0 * 2;
        temp_a1 = *(s8 *)(*(u8 **)(p + 0x7C) + temp_v0);
        if (temp_a1 < 0) {
            var_v0 = (s16 *)(*(u8 **)(p + 0x74) + temp_a2);
        } else {
            if (func_002745F8(temp_a1, temp_a1, temp_a2) != 0) {
                var_a0 = *(s32 *)(p + 0x78);
            } else {
                var_a0 = *(s32 *)(p + 0x74);
            }
            var_v0 = (s16 *)((u8 *)var_a0 + ((((arg1 * *(s32 *)(p + 0xC)) + arg2)) * 2));
        }
        var_f0 = (f32)*var_v0;
    }
    return var_f0;
}
