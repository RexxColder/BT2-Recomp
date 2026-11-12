#include "common.h"

void BtlAnim_SetBlend(f32 farg0, u8 *arg1);
f32 func_001FA318(u8 *arg0);
s32 func_00211310(u8 *arg0, s32 arg1, s32 arg2);
s32 func_00217488(u8 *arg0);
s32 func_0023BDA8(u8 *arg0, s32 arg1);
s32 func_0023C710(u8 *arg0);
s32 func_0023C798(u8 *arg0, s32 arg1);
extern f32 D_00386784;
extern f32 D_00386788;
extern f32 D_0038678C;
extern f32 D_00386790;

s32 func_0022F320(u8 *arg0) {
    f32 var_f20;
    s32 temp_v0;
    s32 temp_v0_2;

    var_f20 = D_00386784;
    if (func_00217488(arg0) != 0x22) {
        var_f20 = 0.5f;
    }
    if (var_f20 < func_001FA318(arg0)) {
        temp_v0 = func_0023C798(arg0, 3);
        if (temp_v0 == -1) {
            temp_v0_2 = func_0023BDA8(arg0, 0x420000);
            if (temp_v0_2 == temp_v0) {
                goto block_12;
            }
            BtlAnim_SetBlend(D_0038678C, arg0);
            return temp_v0_2;
        }
        BtlAnim_SetBlend(D_00386788, arg0);
        return temp_v0;
    }
block_12:
    if (func_00211310(arg0, 2, 1) == 0) {
        return -1;
    }
    BtlAnim_SetBlend(D_00386790, arg0);
    return func_0023C710(arg0);
}
