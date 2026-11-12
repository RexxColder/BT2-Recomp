#include "common.h"

s32 func_002B8280(s32 arg0);
s32 func_002BBDE8(s32 arg0);
s32 func_002E0C78(s32 arg0);
s32 Rand_Range(s32 arg0);
extern u8 D_00379268[] __attribute__((section(".data")));

s32 func_002B8938(u8 *arg0) {
    s32 temp_v1;
    s32 var_s0;
    s32 var_s1;
    s32 var_v0;
    u8 *var_s2;

    var_s2 = arg0;
    if (func_002B8280((s32)arg0) != 1) {
        Rand_Range((s32)D_00379268);
        return 0;
    }
    var_v0 = 0;
    if (*(s32 *)(var_s2 + 0x3C) != 0) {
        var_s1 = func_002E0C78((s32)var_s2);
        var_s0 = func_002BBDE8((s32)(var_s2 + 0x284));
        temp_v1 = func_002BBDE8((s32)(var_s2 + 0x2A4));
        if (var_s1 == var_s0) {
            var_v0 = var_s1;
        } else {
            var_s0 = (var_s0 == 0) ? temp_v1 : var_s0;
            var_v0 = (var_s1 == 0) ? var_s0 : var_s1;
            if (var_s1 == temp_v1) {
                var_v0 = var_s1;
            }
        }
    }
    return var_v0;
}
