#include "common.h"

extern f32 D_00386C58, D_00386C5C, D_00386C60, D_00386C64, D_00386C68, D_00386C6C;
extern f32 D_00386C70, D_00386C74, D_00386C78, D_00386C7C;
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00269A40(s32 arg0, s32 arg1);
void func_003126C8(s32 arg0, s32 arg1);
void sceVu0CopyMatrix(s32 arg0, s32 arg1);
void sceVu0UnitMatrix(s32 arg0);
void sceVu0RotMatrixX(s32 arg0, s32 arg1, f32 farg0);
void sceVu0MulMatrix(s32 arg0, s32 arg1, s32 arg2);
void sceVu0InversMatrix(s32 arg0, s32 arg1);
void BtlOpp_GetDelta(s32 arg0, s32 arg1);
void func_00312638(s32 arg0, s32 arg1, s32 arg2);
void func_00210EE0(s32 arg0, s32 arg1);
void func_00312650(s32 arg0, s32 arg1, s32 arg2);
void sceVu0Normalize(s32 arg0, s32 arg1);
void sceVu0InterVector(s32 arg0, s32 arg1, s32 arg2, f32 farg0);
void sceVu0ApplyMatrix(s32 arg0, s32 arg1, s32 arg2);
f32 atan2f(f32 farg0, f32 farg1);
f32 Mathf_Asin(f32 farg0);
u8 *BtlChar_GetPos(s32 arg0);
f32 BtlUtil_WrapAngle(f32 farg0);
void func_00312490(s32 arg0, s32 arg1, s32 arg2);
void Vec3_RotateAxis(s32 arg0, s32 arg1, s32 arg2, f32 farg0);
void Quat_FromVectors(s32 arg0, s32 arg1, s32 arg2, f32 farg0);
void Quat_FromAxisAngle(s32 arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void Quat_Mul(s32 arg0, s32 arg1, s32 arg2);

#define SP(o) ((s32)&sp[o])
#define SF(o) (*(f32 *)&sp[o])
#define W(p, o) (*(s32 *)((p) + (o)))

/* 0x0023DE40: per-frame head/eye look-at rotation of a battle character (a0). */
void func_0023DE40(s32 arg0) {
    u8 sp[0x200];
    s32 s2 = arg0;
    s32 s3, fp, s0, s1, s4, s5, s6, s7, v0, i;
    f32 f20, f21, f22, f23, f24, f25, f26, f0, f1, f2;
    u8 *a3;

    s3 = 1;
    a3 = *(u8 **)(*(u8 **)(s2 + 0x1530) + 0x95C);
    *(s32 *)&sp[0x164] = 1;
    f0 = (f32)*(s8 *)(a3 + 0x298) / 180.0f;
    f1 = (f32)*(s8 *)(a3 + 0x297) / 180.0f;
    f26 = f0 * D_00386C58;
    f25 = f1 * D_00386C58;
    if (func_00211310(s2, 0, 1) == 0) {
        *(s32 *)&sp[0x164] = 0;
        s3 = 0;
    }
    if (func_00211310(s2, 9, 0x40) == 0) {
        *(s32 *)&sp[0x164] = 0;
        s3 = 1;
    }
    if (func_00211310(s2, 0xA, 1) != 0) {
        *(s32 *)&sp[0x164] = 0;
        s3 = 0;
    }
    f24 = 0.0f;
    fp = func_00269A40(*(s32 *)(s2 + 0x1530), 0x2E);
    v0 = func_00269A40(*(s32 *)(s2 + 0x1530), 0x2F);
    *(s32 *)&sp[0x160] = v0;
    func_003126C8(SP(0), fp + 0x90);
    func_003126C8(SP(0x10), *(s32 *)&sp[0x160] + 0x90);
    sceVu0CopyMatrix(SP(0x20), fp + 0x40);
    s1 = SP(0xB0);
    sceVu0UnitMatrix(s1);
    sceVu0RotMatrixX(s1, s1, f25);
    sceVu0MulMatrix(SP(0x20), SP(0x20), s1);
    s4 = SP(0x60);
    sceVu0InversMatrix(s4, SP(0x20));
    s1 = SP(0xF0);
    BtlOpp_GetDelta(s2, s1);
    func_00312638(s1, s1, s2 + 0x910);
    s0 = SP(0xA0);
    func_00210EE0(s2, s0);
    func_00312650(s1, s1, s0);
    sceVu0Normalize(s1, s1);
    SF(0xFC) = f24;
    s0 = s2 + 0x920;
    if (func_00211310(s2, 9, 0x20) != 0) {
        func_003126C8(s0, s1);
    } else {
        sceVu0InterVector(s0, s1, s0, D_00386C5C);
    }
    W((u8 *)s2, 0x92C) = 0;

    if (s3 == 0) {
        func_002113C0(s2, 9, 0x80, 0);
    } else {
        s6 = SP(0x100);
        __builtin_memset(&sp[0x110], 0, 0x10);
        f20 = -1.0f;
        SF(0x118) = f20;
        sceVu0ApplyMatrix(s6, s4, s0);
        sceVu0Normalize(s6, s6);
        f22 = f20;
        if (func_00211310(s2, 9, 0x80) != 0) {
            f23 = 1.0f;
            f21 = D_00386C60;
        } else {
            f23 = D_00386C64;
            f22 = D_00386C68;
            f21 = 1.5f;
        }
        f20 = atan2f(-SF(0x100), -SF(0x108));
        f0 = Mathf_Asin(SF(0x104));
        f1 = __builtin_fabsf(f20) * D_00386C6C;
        f0 = -f0 + f1;
        if (-f21 < f20 && f20 < f21 && f22 < f0 && f0 < f23) {
            if (func_00211310(s2, 9, 0x80) == 0) {
                BtlOpp_GetDelta(s2, SP(0x120));
                f20 = atan2f(SF(0x120), SF(0x128));
                f0 = BtlUtil_WrapAngle(f20 - *(f32 *)(BtlChar_GetPos(s2) + 0xB4));
                if (__builtin_fabsf(f0) < D_00386C70) {
                    func_002113C0(s2, 9, 0x80, 1);
                }
            }
        } else {
            func_002113C0(s2, 9, 0x80, 0);
        }
        if (func_00211310(s2, 9, 0x80) != 0) {
            u8 *v1 = *(u8 **)(s2 + 0x1530);
            u8 *vv = *(u8 **)(v1 + 0x95C);
            s32 lo;
            f32 q3 = D_00386C74;
            f23 = -((f32)*(u8 *)(vv + 0x296) / 180.0f * q3);
            f22 = (f32)*(u8 *)(vv + 0x294) / 180.0f * q3;
            f24 = 1.0f;
            f21 = (f32)*(u8 *)(vv + 0x295) / 180.0f * q3;
            s7 = SP(0x130);
            __builtin_memset(&sp[0x130], 0, 0x10);
            s5 = SP(0x120);
            SF(0x134) = f24;
            func_00312490(s5, s6, s7);
            sceVu0Normalize(s5, s5);
            f20 = -Mathf_Asin(SF(0x104));
            f2 = D_00386C78;
            f0 = __builtin_fabsf(atan2f(-SF(0x100), -SF(0x108)));
            f0 = f0 * SF(0x104);
            f0 = f0 * f2;
            f20 = f20 - f0;
            if (f21 < f20) {
                Vec3_RotateAxis(s6, s6, s5, f20 - f21);
            }
            if (f20 < f23) {
                Vec3_RotateAxis(s6, s6, s5, f20 - f23);
            }
            s0 = SP(0x140);
            func_003126C8(s0, SP(0x70));
            f21 = -f22;
            s1 = s6;
            s4 = s0;
            SF(0x154) = f24;
            *(s32 *)&sp[0x150] = 0;
            s3 = 1;
            *(s32 *)&sp[0x158] = 0;
            *(s32 *)&sp[0x15C] = 0;
            do {
                s32 a2 = s0;
                f20 = atan2f(-SF(0x100), -SF(0x108));
                s0 += 0x10;
                if (f20 < f21) {
                    Vec3_RotateAxis(s1, s1, a2, f21 - f20);
                }
                if (f22 < f20) {
                    Vec3_RotateAxis(s1, s1, s4, f22 - f20);
                }
                s3--;
                s4 += 0x10;
            } while (s3 >= 0);
            f21 = 0.5f;
            Quat_FromVectors(s5, SP(0x110), s6, f21);
            f20 = 1.0f;
            f22 = 0.0f;
            f24 = f20;
            Quat_FromAxisAngle(s7, f20, f22, f22, f26 * f21);
            Quat_Mul(s5, s5, s7);
            Quat_FromAxisAngle(s7, f20, f22, f22, f25 * f21);
            Quat_Mul(s5, s7, s5);
            func_003126C8(*(s32 *)(s2 + 0x1530) + 0xD30, s5);
            func_003126C8(*(s32 *)(s2 + 0x1530) + 0xD40, s5);
            *(u32 *)((u8 *)fp + 0xD0) &= ~1u;
            *(u32 *)((u8 *)*(s32 *)&sp[0x160] + 0xD0) &= ~1u;
            if (*(s32 *)&sp[0x164] == 0) {
                f24 = f22;
            }
        }
    }

    if (func_00211310(s2, 9, 0x20) != 0) {
        *(f32 *)(*(u8 **)(s2 + 0x1530) + 0xD50) = f24;
        *(f32 *)(*(u8 **)(s2 + 0x1530) + 0xD54) = f24;
    } else {
        u8 *v1 = *(u8 **)(s2 + 0x1530);
        f2 = D_00386C7C;
        f1 = *(f32 *)(v1 + 0xD50);
        f1 = f1 + (f24 - f1) * f2;
        *(f32 *)(v1 + 0xD50) = f1;
        v1 = *(u8 **)(s2 + 0x1530);
        f1 = *(f32 *)(v1 + 0xD54);
        f1 = f1 + (f24 - f1) * f2;
        *(f32 *)(v1 + 0xD54) = f1;
    }
}
