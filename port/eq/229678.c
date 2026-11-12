#include "common.h"

extern f32 D_0038641C;
extern f32 D_00386420;
extern f32 D_00386424;
extern f32 D_00386428;
extern f32 D_0038642C;
extern f32 D_00386430;
extern f32 D_00386434;
extern f32 D_00386438;

s32 func_0023BDA8(s32 arg0, s32 arg1);
void BtlAnim_SetBlend(f32 farg0, s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 BtlPad_Test4C(s32 arg0, s32 arg1);
s32 BtlPad_TestStep(s32 arg0, s32 arg1);
s32 BtlMember_HasKi(s32 arg0, s32 arg1);
s32 func_00240438(s32 arg0, s32 arg1);
s32 func_0023F410(s32 arg0, s32 arg1);
s32 func_0023F420(s32 arg0);
s32 func_00218758(s32 arg0);
s32 func_0023C710(s32 arg0);
s32 func_001FA288(s32 arg0, s32 arg1);

s32 func_00229678(s32 arg0) {
    s32 v;

    v = func_0023BDA8(arg0, 4);
    if (v != -1) {
        BtlAnim_SetBlend(D_0038641C, arg0);
        return v;
    }
    if (func_00211310(arg0, 5, 0x10) == 0) {
        if (BtlPad_Test4C(arg0, 0) != 0) {
            BtlAnim_SetBlend(D_00386420, arg0);
            return 0x65;
        }
        if (func_0023F420(arg0) & 0x800) {
            if (BtlPad_TestStep(arg0, 2) != 0) {
                if (BtlMember_HasKi(arg0, func_00240438(arg0, 8)) != 0) {
                    BtlAnim_SetBlend(D_00386424, arg0);
                    return 0x89;
                }
            }
            if (BtlPad_TestStep(arg0, 3) != 0 &&
                BtlMember_HasKi(arg0, func_00240438(arg0, 0xB)) != 0 &&
                func_00218758(arg0) != 0) {
                BtlAnim_SetBlend(D_00386428, arg0);
                return 0x8A;
            }
        }
        if (BtlPad_Test4C(arg0, 2) != 0 && (func_0023F420(arg0) & 0x100) != 0) {
            BtlAnim_SetBlend(D_0038642C, arg0);
            return 0x46;
        }
    }
    if (func_00211310(arg0, 0, 4) == 0) {
        if (BtlPad_Test4C(arg0, 4) != 0) {
            func_002113C0(arg0, 0, 2, 1);
            BtlAnim_SetBlend(D_00386430, arg0);
            return func_0023C710(arg0);
        }
        if (!(func_0023F410(arg0, 0) & 0x1000)) {
            if (BtlPad_Test4C(arg0, 5) != 0) {
                func_002113C0(arg0, 0, 2, 1);
                BtlAnim_SetBlend(D_00386434, arg0);
                return 0x12;
            }
        }
    }
    if (func_001FA288(arg0, 0x2B) == 0) {
        return -1;
    }
    BtlAnim_SetBlend(D_00386438, arg0);
    return 0xA;
}
