#include "common.h"

s32 func_0019F3B0(void *arg0, s32 arg1);

s32 func_00172530(u8 *arg0) {
    s32 var_s2;
    s32 var_s3;
    u8 *temp_s4;
    u8 *temp_v0;
    u8 *var_s0;
    u8 *var_s1;
    f32 temp_f0;

    var_s2 = 0;
    var_s3 = 0;
    temp_v0 = *(u8 **)(arg0 + 0x38);
    temp_s4 = *(u8 **)(temp_v0 + 0xA0);
    var_s1 = temp_v0 + 0xAF0;
    var_s0 = temp_v0 + 0xAE0;
    do {
        if (*(s32 *)var_s0 != 0) {
            temp_f0 = *(f32 *)(var_s0 + 4);
            if (!(temp_f0 <= 0.0f)) {
                var_s3 = 1;
                *(f32 *)(var_s0 + 4) = temp_f0 - 1.0f;
            } else {
                func_0019F3B0(var_s1, *(s32 *)(*(u8 **)(temp_s4 + 0x20) + 0xC));
                *(s32 *)var_s0 = 0;
            }
        }
        var_s2 += 1;
        var_s0 += 0x20;
        var_s1 += 0x20;
    } while (var_s2 < 5);
    return var_s3;
}
