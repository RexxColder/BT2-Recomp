#include "common.h"

void *BtlChar_GetPos(s32 arg0);
f32 BtlUtil_WrapAngle(f32 farg0);
f32 atan2f(f32 farg0, f32 farg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
extern f32 D_00385AE4;

void func_00217238(s32 arg0, s32 arg1) {
    s32 var_s2;
    s32 var_s1;
    u8 *var_s0;
    f32 temp_f3;
    f32 temp_f2;
    f32 temp_f13;
    f32 temp_f12;
    f32 var_f0;

    var_s1 = arg0;
    var_s2 = arg1 & 0xFF;
    var_s0 = BtlChar_GetPos(arg0);
    if (func_00211310(var_s1, 0, 8) != 0) {
        temp_f13 = *(f32 *)(var_s0 + 0);
        temp_f3 = *(f32 *)(var_s0 + 0x40);
        temp_f12 = *(f32 *)(var_s0 + 8);
        temp_f2 = *(f32 *)(var_s0 + 0x48);
        if (((temp_f13 * temp_f3) + (temp_f12 * temp_f2)) > 0.0f) {
            if (((temp_f13 * temp_f2) - (temp_f12 * temp_f3)) > 0.0f) {
                var_f0 = atan2f(temp_f12, -temp_f13);
            } else {
                var_f0 = atan2f(-temp_f12, temp_f13);
            }
            if (var_s2 != 0) {
                var_f0 = BtlUtil_WrapAngle(var_f0 + D_00385AE4);
            }
            *(f32 *)(var_s0 + 0xB4) = var_f0;
        }
    }
    if (func_00211310(var_s1, 0, 0x10) != 0) {
        *(s32 *)(var_s0 + 0xB0) = 0;
    }
    if (func_00211310(var_s1, 0, 0x20) != 0) {
        *(s32 *)(var_s0 + 0xB0) = 0;
    }
}
