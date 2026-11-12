#include "common.h"

extern f32 D_0038590C, D_00385910, D_00385914, D_00385918, D_0038591C;

s32 func_0025FBE8(s32 a0, s64 a1);
s32 func_002406A8(u8 *a0);
s32 BtlObjAnim_GetEventArg(s32 a0, s32 a1);
s32 BtlObjAnim_MaskToNode(s32 a0);
void func_003126C8(u8 *a0, u8 *a1);
s32 func_00240A20(u8 *a0);
s32 BtlKiBlast_GetHitsOf(u8 *a0);
s32 BtlKiBlast_GetUnk31Of(u8 *a0);
s32 func_0023FDB8(u8 *a0);
f32 func_00240618(u8 *a0);
f32 func_00240480(u8 *a0);
f32 func_00240528(u8 *a0);
f32 BtlKiBlast_GetUnk28Of(u8 *a0);
f32 BtlKiBlast_GetUnk2COf(u8 *a0);
s32 func_0023FFF8(u8 *a0);
u8 *BtlMember_GetActiveGauge(u8 *a0);
f32 func_00217330(u8 *a0);
f32 BtlCharApi_GetHeight(s32 a0);
extern f32 func_00212970();
s32 func_00211310(u8 *a0, s32 a1, s32 a2);
f32 BtlOpp_GetDistance(u8 *a0);
void sceVu0Normalize(u8 *a0, u8 *a1);
void Vec3_RotateAxis(u8 *a0, u8 *a1, u8 *a2, f32 f12);
void func_002115B0(u8 *a0, s32 a1, s32 a2);
s32 BtlObj_GetNodeSide(s32 a0);
void Vec3_RotateY(u8 *a0, u8 *a1, f32 f12);
void func_0019D4A8(u8 *a0);
void func_001AE210(u8 *a0);
void func_001AC898(u8 *a0);
void func_001ABF08(u8 *a0);
s32 BtlChar_FrameMod(s32 a0);
void func_0020FC38(u8 *a0, s32 a1);
void func_00212DD8(u8 *a0, s32 a1);
void BtlChar_SetSmallVibration(u8 *a0, f32 f12);
void func_00312680(u8 *a0, u8 *a1, f32 f12);
s32 func_0026A2B0(s32 a0, u8 *a1, f32 f12);

#define F(p, o) (*(f32 *)((p) + (o)))
#define W(p, o) (*(s32 *)((p) + (o)))

s32 func_002046C8(u8 *a0) {
    u8 sp[0x70];
    s32 s2, s3, s5, s0, v1, g;
    f32 f20, f0;
    f32 f21, f22, f23;

    if (!func_0025FBE8(W(a0, 0x1530), 4)) return 0;
    s2 = func_002406A8(a0);
    s5 = BtlObjAnim_MaskToNode(BtlObjAnim_GetEventArg(W(a0, 0x1530), 4));
    func_003126C8(sp + 0x40, a0 + 0xA00);
    s3 = func_00240A20(a0);
    *(u16 *)(sp + 0x14) = s5;
    *(u16 *)(sp + 0x10) = *(u16 *)(a0 + 0x1534);
    if (!(0 < s3)) s3 = 1;
    *(u16 *)(sp + 0x12) = *(u16 *)(a0 + 0x1534);
    *(u16 *)(sp + 0x16) = *(u16 *)(*(u8 **)(a0 + 0x1530) + 0x9F0);
    sp[0x1A] = BtlKiBlast_GetHitsOf(a0);
    sp[0x1B] = BtlKiBlast_GetUnk31Of(a0);
    *(s16 *)(sp + 0x18) = func_0023FDB8(a0);
    *(s16 *)(sp + 0x1C) = (s32)func_00240618(a0);
    F(sp, 0x20) = func_00240480(a0);
    F(sp, 0x24) = func_00240528(a0);
    F(sp, 0x28) = BtlKiBlast_GetUnk28Of(a0);
    F(sp, 0x2C) = BtlKiBlast_GetUnk2COf(a0);
    sp[0x35] = 1;
    sp[0x34] = 1;
    sp[0x36] = (func_0023FFF8(a0) >> 5) & 1;
    switch ((u32)(s32) * (s16 *)(sp + 0x18)) {
    case 1: case 5: case 9: W(sp, 0x30) = 1; break;
    case 2: case 6: case 10: W(sp, 0x30) = 2; break;
    case 3: case 7: case 11: W(sp, 0x30) = 3; break;
    default: W(sp, 0x30) = 0; break;
    }
    if (*(BtlMember_GetActiveGauge(a0) + 0x2C) != 0) {
        v1 = *(s16 *)(sp + 0x18);
        if (v1 == 4) sp[0x1A] = 0;
        else if (v1 < 5) sp[0x1A] = (v1 == 0) ? 0 : 7;
        else sp[0x1A] = (v1 == 8) ? 0 : 7;
    }
    if (s3 > 0) {
        f21 = 0.5f;
        f22 = D_0038590C;
        f23 = D_00385910;
        do {
            func_003126C8(sp, sp + 0x40);
            if (s2 == 1) {
            } else if (s2 < 2) {
                if (s2 == 0) {
                    f20 = func_00217330(a0);
                    f0 = BtlCharApi_GetHeight(W(a0, 0x1534)) * 3.0f;
                    if (f0 < f20) {
                        F(sp, 0) = F(sp, 0) + (func_00212970() - f21) * f22;
                        F(sp, 4) = F(sp, 4) + (func_00212970() - f21) * f22;
                    } else {
                        F(sp, 0) = F(sp, 0) + (func_00212970() - f21) * f22;
                        F(sp, 4) = F(sp, 4) + (func_00212970() - 1.0f) * f23;
                    }
                    F(sp, 8) = F(sp, 8) + (func_00212970() - f21) * f22;
                }
            } else if (s2 < 7) {
                if (func_00211310(a0, 0, 1)) {
                    f20 = BtlOpp_GetDistance(a0) * D_00385914;
                    f20 = f20 / F(sp, 0x20);
                    f20 = f20 * F(sp, 0x24);
                    f20 = f20 * f21;
                    if (0.75f < f20) f20 = 0.75f;
                    if (f20 < f23) f20 = D_00385918;
                    if (s2 == 2) {
                        F(sp, 0x60) = F(sp, 0x48);
                        W(sp, 0x64) = 0;
                        F(sp, 0x68) = -F(sp, 0x40);
                        sceVu0Normalize(sp + 0x60, sp + 0x60);
                        Vec3_RotateAxis(sp, sp, sp + 0x60, f20);
                    } else {
                        s0 = 0;
                        if (s2 == 4) {
                            s0 = 1;
                        } else if (s2 < 5) {
                            if (s2 == 3) {
                                s0 = func_00211310(a0, 5, 0x80) != 0;
                                func_002115B0(a0, 5, 0x80);
                            }
                        } else if (s2 == 6) {
                            s0 = (u32)BtlObj_GetNodeSide(s5) < 1;
                        }
                        if (s0) Vec3_RotateY(sp, sp, -f20);
                        else Vec3_RotateY(sp, sp, f20);
                    }
                }
            }
            g = sp[0x1A];
            if (g == 0x11) func_0019D4A8(sp);
            else if (g == 0x10) func_001AE210(sp);
            else if (g == 0xE || g == 0xF) func_001AC898(sp);
            else func_001ABF08(sp);
            v1 = W(a0, 0x1448);
            s3--;
            W(a0, 0x146C) = W(a0, 0x146C) + 1;
            W(a0, 0x1448) = v1 + 1;
        } while (s3 != 0);
    }
    v1 = sp[0x1A];
    if (v1 >= 0x10 || v1 < 0xE) {
        func_0020FC38(a0, BtlChar_FrameMod(2) + 0xF);
    } else {
        func_0020FC38(a0, 1);
    }
    v1 = *(s16 *)(sp + 0x18);
    if (!(v1 < 4) || !(v1 > 0)) func_00212DD8(a0, 0xC);
    BtlChar_SetSmallVibration(a0, D_0038591C);
    func_00312680(sp + 0x50, sp + 0x40, -1.0f);
    return func_0026A2B0(W(a0, 0x1530), sp + 0x50, 3.0f);
}
