#include "common.h"

s32 func_00211310(u8 *arg0, s32 arg1, s32 arg2);
f32 func_001FA318(u8 *arg0);
s32 func_00210E18(u8 *arg0);
s32 BtlPad_Test4C(u8 *arg0, s32 arg1);
void func_002174D8(u8 *arg0, s32 arg1);
s32 func_002174B8(u8 *arg0);
void BtlAnim_SetBlend(f32 farg0, u8 *arg1);
s32 BtlObjXf_Update(u8 *arg0);
s32 func_0023C798(u8 *arg0, s32 arg1);
s32 func_0023C710(u8 *arg0);
extern f32 D_00385C04;
extern f32 D_00385C08;

s32 func_0021A2A8(u8 *arg0) {
    f32 f20;
    s32 v;

    if (func_00211310(arg0, 4, 2) == 0) {
        goto block_11;
    }
    f20 = func_001FA318(arg0);
    if (func_00210E18(arg0) == 0x95 && BtlPad_Test4C(arg0, 3) != 0) {
        func_002174D8(arg0, 0xB);
    }
    if (0.5f < f20 && f20 < D_00385C04 && func_002174B8(arg0) != -1) {
        return func_002174B8(arg0);
    }
block_11:
    if (func_00211310(arg0, 2, 1) == 0) {
        return -1;
    }
    BtlAnim_SetBlend(D_00385C08, arg0);
    if (BtlObjXf_Update(arg0) == 0x39 && *(s32 *)(arg0 + 0x9C0) >= 0) {
        v = func_0023C798(arg0, 0x200);
        if (v == -1) {
            return func_0023C710(arg0);
        }
        return v;
    }
    return func_0023C710(arg0);
}
