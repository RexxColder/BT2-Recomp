#include "common.h"

s32 BtlObjXf_Update(s32 arg0);
s32 func_00218128(s32 arg0, s32 arg1);
s32 func_0023BDA8(s32 arg0, s32 arg1);
void BtlAnim_SetBlend(s32 arg0, f32 farg0);
s32 BtlPad_Test4C(s32 arg0, s32 arg1);
s32 BtlPad_TestStep(s32 arg0, s32 arg1);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_00217518(s32 arg0, s32 arg1);
s32 func_0023F420(s32 arg0);
s32 func_0023F410(s32 arg0);
s32 func_00240438(s32 arg0, s32 arg1);
s32 BtlMember_HasKi(s32 arg0, s32 arg1);
s32 func_00218758(s32 arg0);
s32 func_00218328(s32 arg0);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_0023D380(s32 arg0);
s32 func_001FA288(s32 arg0, s32 arg1);
s32 func_0023C710(s32 arg0);
extern f32 D_003864E8, D_003864EC, D_003864F0, D_003864F4, D_003864F8, D_003864FC, D_00386500;
extern f32 D_00386504, D_00386508, D_0038650C, D_00386510;

s32 func_0022AE78(s32 s0) {
    s32 s1;

    if (BtlObjXf_Update(s0) != 0x20) {
        s1 = func_0023BDA8(s0, func_00218128(s0, 3) != 0 ? 0x1001A : 0x1A);
        if (s1 != -1) {
            BtlAnim_SetBlend(s0, D_003864E8);
            return s1;
        }
        if (BtlPad_Test4C(s0, 0) != 0) {
            if (func_00218128(s0, 1) != 0 && func_00211310(s0, 0, 1) != 0) {
                return func_00217518(0x1E, 0x64);
            }
            BtlAnim_SetBlend(s0, D_003864EC);
            return 0x63;
        }
        if ((func_0023F420(s0) & 0x800) != 0) {
            if (BtlPad_TestStep(s0, 2) != 0) {
                if (BtlMember_HasKi(s0, func_00240438(s0, 4)) != 0) {
                    BtlAnim_SetBlend(s0, D_003864F0);
                    return 0x8B;
                }
            }
            if (BtlPad_TestStep(s0, 3) != 0) {
                if (BtlMember_HasKi(s0, func_00240438(s0, 7)) != 0) {
                    if (func_00218758(s0) != 0) {
                        BtlAnim_SetBlend(s0, D_003864F4);
                        return 0x8C;
                    }
                }
            }
        }
        if (BtlPad_Test4C(s0, 2) != 0) {
            if ((func_0023F420(s0) & 0x100) != 0) {
                BtlAnim_SetBlend(s0, D_003864F8);
                return 0x45;
            }
        }
        if (func_00211310(s0, 1, 4) != 0) {
            if (BtlPad_Test4C(s0, 4) != 0) {
                BtlAnim_SetBlend(s0, D_003864FC);
                return (func_0023F410(s0) & 0x1000) != 0 ? 0xC : 0x11;
            }
            if (BtlPad_Test4C(s0, 5) != 0) {
                BtlAnim_SetBlend(s0, D_00386500);
                return (func_0023F410(s0) & 0x1000) != 0 ? 0xA : 0x12;
            }
        }
    }
    if (BtlObjXf_Update(s0) == 0x20 && func_00218328(s0) != 0) {
        BtlAnim_SetBlend(s0, D_00386504);
        func_002113C0(s0, 0xE, 0x200, 1);
        if (func_00211310(s0, 1, 4) != 0) {
            func_002113C0(s0, 1, 4, 0);
            func_002113C0(s0, 0, 2, 1);
        }
        return func_0023D380(s0);
    }
    if (func_001FA288(s0, 0x19) != 0) {
        BtlAnim_SetBlend(s0, D_00386508);
        return func_0023C710(s0);
    }
    if (func_001FA288(s0, 0x20) != 0) {
        BtlAnim_SetBlend(s0, D_0038650C);
        return func_0023C710(s0);
    }
    if ((*(u32 *)((u8 *)s0 + 0x8DC) & 2) != 0) {
        BtlAnim_SetBlend(s0, D_00386510);
        return func_0023C710(s0);
    }
    return -1;
}
