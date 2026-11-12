#include "common.h"

f32 BtlCharApi_GetHeight(s32 arg0);
f32 func_0029DFD0(s32 arg0);
void func_00312650(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern f32 D_003857B0;
extern u8 *D_003876A0;

f32 func_001FA588(u8 *arg0, s32 arg1, s32 arg2) {
    s32 sp[4];
    f32 temp_f20;
    f32 var_f0;

    var_f0 = 1.0f;
    if ((*(s64 *)(D_003876A0 + 0x4D8) & 0x3800) == 0) {
        func_00312650((s32)sp, arg2, arg1, arg1);
        temp_f20 = func_0029DFD0((s32)sp);
        var_f0 = ((temp_f20 / BtlCharApi_GetHeight(*(s32 *)(arg0 + 0x1534))) * D_003857B0) + D_003857B0;
        if (var_f0 > 1.0f) {
            var_f0 = 1.0f;
        }
    }
    return var_f0;
}
