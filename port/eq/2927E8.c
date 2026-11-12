#include "common.h"

extern f32 D_00387188;
extern f32 D_00387D8C;
void func_003126C8(s32 arg0, s32 arg1);
void func_00312650(s32 arg0, s32 arg1, s32 arg2);
void func_00312638(s32 arg0, s32 arg1, s32 arg2);
f32 sceVu0InnerProduct(s32 arg0, s32 arg1);
void sceVu0Normalize(s32 arg0);
s32 ColTri_ContainsPoint(s32 arg0, s32 arg1);
s32 ColSphere_TestLine(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void ColPlane_FromPoints(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void ColPlane_ProjectPoint(s32 arg0, s32 arg1, s32 arg2);
void ColLine_DistPoint(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 ColLine2_Intersect(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

#define SP(o) ((s32)&sp[o])
#define SF(o) (*(f32 *)&sp[o])
#define F(a) (*(f32 *)(a))

/* 0x002927E8: sweep a sphere (a0, +0x30 centre, +0x40 radius) along the vector at a0+0x60
 * against triangle a1 (verts at +0x00,+0x10,+0x20, plane at +0x30). Returns 1 on hit. */
s32 ColSweep_TestTri(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 sp[0x1F0];
    s32 s0, s1, s2, s3, s4, s5, s7;
    f32 f0, f1, f2, f3, f20, f21, f22;
    s32 v0;

    s5 = arg0 + 0x30;
    *(s32 *)&sp[0x170] = arg2;
    *(s32 *)&sp[0x174] = arg3;
    func_003126C8(SP(0x10), arg0 + 0x60);
    f0 = sceVu0InnerProduct(SP(0x10), arg1 + 0x30);
    if (D_00387188 < f0) {
        return 0;
    }
    s0 = SP(0x20);
    f21 = D_00387D8C;
    func_003126C8(SP(0x20), arg1 + 0x30);
    SF(0x2C) = -SF(0x2C);
    *(s32 *)&sp[0x178] = -1;
    f0 = sceVu0InnerProduct(SP(0x20), s5);
    f20 = f0 + SF(0x2C);
    f2 = F(arg0 + 0x40);
    if (f20 < -f2) {
        return 0;
    }
    s0 = SP(0x30);
    if (f2 < f20) {
        f20 = f20 - f2;
        f1 = sceVu0InnerProduct(arg1 + 0x30, SP(0x10));
        if (f1 != 0.0f) {
            f20 = -f20 / f1;
            f3 = F(s5);
            SF(0x3C) = 1.0f;
            SF(0x30) = f3 + SF(0x10) * f20;
            SF(0x34) = F(arg0 + 0x34) + SF(0x14) * f20;
            SF(0x38) = F(arg0 + 0x38) + SF(0x18) * f20;
            if (ColTri_ContainsPoint(arg1, SP(0x30)) != 0 && f20 < f21) {
                func_003126C8(SP(0), arg1 + 0x30);
                f21 = f20;
                *(s32 *)&sp[0x178] = 0;
            }
        }
    }

    f22 = 0.0f;
    f20 = D_00387D8C;
    s2 = arg1;
    s1 = 2;
    s3 = SP(0x40);
    s4 = SP(0x50);
    do {
        s0 = SP(0x30);
        SF(0x164) = f20;
        SF(0x168) = f20;
        func_003126C8(s0, s2);
        s2 += 0x10;
        func_00312650(s3, s0, SP(0x10));
        func_00312650(s4, s3, s0);
        v0 = ColSphere_TestLine(s5, s0, s3, SP(0x160), SP(0x164), SP(0x168));
        if (v0 != 0) {
            f0 = SF(0x164);
            f1 = SF(0x168);
            if (f1 < f0) {
                f0 = f1;
            }
            if (f0 < f22 || !(f0 < f21)) {
                s1--;
                continue;
            }
            f21 = f0;
            SF(0x60) = SF(0x30) + SF(0x50) * f21;
            SF(0x64) = SF(0x34) + SF(0x54) * f21;
            SF(0x68) = SF(0x38) + SF(0x58) * f21;
            *(s32 *)&sp[0x178] = 1;
            func_00312650(SP(0), s5, SP(0x60));
        }
        s1--;
    } while (s1 >= 0);

    s2 = SP(0x60);
    s7 = SP(0x70);
    s1 = 0;
    do {
        s1++;
        func_003126C8(s2, arg1 + ((s1 - 1) << 4));
        s4 = 0;
        s3 = 1;
        func_003126C8(s7, arg1 + (((s1 != 3) ? s1 : 0) << 4));
        func_00312650(SP(0x90), s7, SP(0x10));
        ColPlane_FromPoints(SP(0x80), s2, s7, SP(0x90));
        f0 = sceVu0InnerProduct(SP(0x80), s5);
        f2 = f0 + SF(0x8C);
        f3 = F(arg0 + 0x40);
        if (f3 < f2) {
            continue;
        }
        if (f2 < -f3) {
            continue;
        }
        f20 = __builtin_sqrtf(__builtin_fabsf(f3 * f3 - f2 * f2));
        ColPlane_ProjectPoint(SP(0xA0), SP(0x80), s5);
        ColLine_DistPoint(SP(0xA0), s2, s7, SP(0xB0));
        func_00312650(SP(0xC0), SP(0xB0), SP(0xA0));
        sceVu0Normalize(SP(0xC0));
        {
            f32 f6 = __builtin_fabsf(SF(0x80));
            f32 f7 = __builtin_fabsf(SF(0x84));
            f32 f3b = __builtin_fabsf(SF(0x88));
            SF(0xD0) = SF(0xC0) * f20 + SF(0xA0);
            SF(0xD4) = SF(0xC4) * f20 + SF(0xA4);
            SF(0xD8) = SF(0xC8) * f20 + SF(0xA8);
            if (f7 < f6 && f3b < f6) {
                s4 = 1;
                s3 = 2;
            } else if (f3b < f7) {
                s4 = 0;
                s3 = 2;
            }
        }
        s0 = SP(0xD0);
        func_00312638(SP(0xE0), s0, SP(0x10));
        SF(0xF0) = F(s0 + (s4 << 2));
        SF(0xF4) = F(s0 + (s3 << 2));
        SF(0x100) = SF(0xE0 + (s4 << 2));
        SF(0x104) = SF(0xE0 + (s3 << 2));
        SF(0x110) = F(s2 + (s4 << 2));
        SF(0x114) = F(s2 + (s3 << 2));
        SF(0x120) = F(s7 + (s4 << 2));
        SF(0x124) = F(s7 + (s3 << 2));
        v0 = ColLine2_Intersect(SP(0xF0), SP(0x100), SP(0x110), SP(0x120), SP(0x16C));
        if (v0 == 0) {
            continue;
        }
        f0 = SF(0x16C);
        f20 = 0.0f;
        if (f0 < f20) {
            continue;
        }
        SF(0x130) = SF(0xD0) + SF(0x10) * f0;
        SF(0x134) = SF(0xD4) + SF(0x14) * f0;
        SF(0x138) = SF(0xD8) + SF(0x18) * f0;
        func_00312650(SP(0x140), SP(0x60), SP(0x130));
        func_00312650(SP(0x150), SP(0x70), SP(0x130));
        f0 = sceVu0InnerProduct(SP(0x140), SP(0x150));
        if (f20 < f0) {
            continue;
        }
        f0 = SF(0x16C);
        if (f21 < f0) {
            continue;
        }
        f21 = f0;
        func_00312650(SP(0), s5, s0);
        *(s32 *)&sp[0x178] = 2;
    } while (s1 < 3);

    v0 = *(s32 *)&sp[0x178];
    if (v0 != -1) {
        f0 = f21 * SF(0x10);
        f2 = f21 * SF(0x14);
        f3 = f21 * SF(0x18);
        F(*(s32 *)&sp[0x170]) = F(arg0) + f0;
        F(*(s32 *)&sp[0x170] + 4) = F(arg0 + 4) + f2;
        F(*(s32 *)&sp[0x170] + 8) = F(arg0 + 8) + f3;
        F(*(s32 *)&sp[0x174]) = f21;
    }
    return (*(s32 *)&sp[0x178] ^ -1) != 0;
}
