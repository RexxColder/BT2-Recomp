#include "common.h"

s32 func_001F9978(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern f32 D_00386CE8;
extern f32 D_00386CEC;
extern f32 D_00386CF0;

f32 func_00240D50(s32 arg0, s32 arg1) {
    f32 var_f20;
    s32 temp_a2;
    s32 temp_v0;

    temp_a2 = arg1 * 4;
    var_f20 = *(f32 *)(*(s32 *)(*(s32 *)(arg0 + 0x1530) + 0x98C) + temp_a2) * 10.0f * D_00386CE8;
    if (arg1 != 0xF) {
        temp_v0 = func_001F9978(arg0, arg1, temp_a2, 0xF);
        var_f20 = var_f20 * ((f32)temp_v0 * D_00386CEC);
    }
    if (D_00386CF0 < var_f20) {
        var_f20 = D_00386CF0;
    }
    return var_f20;
}
