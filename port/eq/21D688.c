#include "common.h"

void BtlAnim_SetBlend(f32 farg0, s32 arg1);
s32 BtlObjXf_Update(s32 arg0);
s32 BtlPad_Test4C(s32 arg0, s32 arg1);
f32 func_001FA318(s32 arg0);
s32 func_00210E18(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_002174B8(s32 arg0);
void func_002174D8(s32 arg0, s32 arg1);
s32 func_0023C710(s32 arg0);
s32 func_0023C798(s32 arg0, s32 arg1);
s32 func_0023F420(s32 arg0);
extern f32 D_00385DD8;
extern f32 D_00385DDC;
extern f32 D_00385DE0;
extern f32 D_00385DE4;

s32 func_0021D688(s32 arg0) {
    s32 temp_v0;

    if (func_00211310(arg0, 4, 0x1002) != 0) {
        if (!(func_0023F420(arg0) & 0x4000)) {
            goto block_15;
        }
        if ((func_00210E18(arg0) == 0x9C) && (BtlPad_Test4C(arg0, 1) != 0)) {
            func_002174D8(arg0, 0x7B);
        }
        if (!(D_00385DD8 < func_001FA318(arg0))) {
            goto block_15;
        }
        if (func_002174B8(arg0) != 0x7B) {
block_15:
            if (BtlPad_Test4C(arg0, 0) != 0) {
                func_002174D8(arg0, 0x49);
            }
            goto block_17;
        }
        BtlAnim_SetBlend(D_00385DDC, arg0);
        return func_002174B8(arg0);
    }
block_17:
    if (func_00211310(arg0, 2, 1) == 0) {
        return -1;
    }
    BtlAnim_SetBlend(D_00385DE0, arg0);
    if ((BtlObjXf_Update(arg0) != 0x39) || (*(s32 *)((u8 *)arg0 + 0x9C0) < 0) ||
        (temp_v0 = func_0023C798(arg0, 0x200), (temp_v0 == -1))) {
        if (func_002174B8(arg0) == -1) {
            return func_0023C710(arg0);
        }
        BtlAnim_SetBlend(D_00385DE4, arg0);
        return func_002174B8(arg0);
    }
    return temp_v0;
}
