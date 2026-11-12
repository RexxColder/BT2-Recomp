#include "common.h"

extern f32 D_003857E8, D_003857EC, D_003857F0, D_003857F4, D_003857F8, D_003857FC;
extern f32 D_00385800, D_00385804, D_00385808;
extern u8 *D_003876A0;

f32 BtlCharApi_GetHeight(s32 a0);
s32 BtlChar_GetPos(u8 *a0);
void func_003126C8(u8 *a0, s32 a1);
f32 func_00273048(void);
void BtlOpp_GetTargetPos(u8 *a0, u8 *a1);
void func_00312650(u8 *a0, u8 *a1, u8 *a2);
f32 BtlOpp_GetHalfHeightDiff(u8 *a0);
void sceVu0Normalize(u8 *a0, u8 *a1);
void func_001FA3D0(u8 *a0, u8 *a1, s32 a2);
f32 func_001FA4F0(u8 *a0, s32 a1);
f32 func_0029DFD0(u8 *a0);
void func_00312680(u8 *a0, u8 *a1, f32 f12);
f32 Mathf_Asin(f32 f12);
void Vec3_RotateX(u8 *a0, u8 *a1, f32 f12);
void Vec3_RotateY(u8 *a0, u8 *a1, f32 f12);
f32 BtlUtil_WrapAngle(f32 f12);
f32 func_001FA730(u8 *a0);
f32 atanf(f32 x);
f32 tanf(f32 x);
f32 sinf(f32 x);
f32 cosf(f32 x);
f32 sqrtf(f32 x);

#define F(p, o) (*(f32 *)((p) + (o)))

void func_001FAFD8(u8 *a0, u8 *a1, u8 *a2, u8 *a3) {
    u8 sp[0x60];
    u8 *s4 = a0 + 0x150;
    u8 *s3 = sp + 0x40;
    f32 f20, f21, f22, f23, f24, f25, f26, f27, f28, f29, f0, f4;

    f21 = BtlCharApi_GetHeight(*(s32 *)(a0 + 0x1534));
    func_003126C8(sp, BtlChar_GetPos(a0));
    f20 = func_00273048();
    f20 = f20 + BtlCharApi_GetHeight(*(s32 *)(a0 + 0x1534)) * 0.5f;
    if (f20 < F(sp, 4)) F(sp, 4) = f20;
    BtlOpp_GetTargetPos(a0, sp + 0x10);
    func_00312650(sp + 0x20, sp + 0x10, sp);
    f0 = BtlOpp_GetHalfHeightDiff(a0);
    F(sp, 0x24) = F(sp, 0x24) + f0;
    sceVu0Normalize(sp + 0x30, sp + 0x20);
    f0 = f21 * D_003857E8;
    *(s32 *)(a3 + 0) = 0;
    *(s32 *)(a3 + 8) = 0;
    F(a3, 0xC) = 1.0f;
    f0 = -f0;
    F(a3, 4) = f0;
    if (!(-10.0f < f0)) F(a3, 4) = -10.0f;
    func_001FA3D0(a0, s3, *(s32 *)(s4 + 0xB4));
    func_00312650(s3, s3, a3);
    f29 = func_001FA4F0(a0, *(s32 *)(s4 + 0xB4));
    f28 = F(s4, 0);
    f0 = func_0029DFD0(sp + 0x20);
    f27 = f28;
    if (f0 < 0.0f) {
        f20 = 0.0f;
    } else if (!(f0 < 100.0f)) {
        f20 = 1.0f;
    } else {
        f20 = (f0 - 0.0f) / 100.0f;
    }
    f0 = f20 + f20;
    f22 = 1.0f;
    f24 = 0.5f;
    f25 = D_003857F4;
    f20 = f0 - f22;
    f20 = (-f20) * __builtin_fabsf(f20) + (f20 + f20);
    f20 = f20 * f24 + f24;
    f20 = f20 * D_003857EC + D_003857F0;
    func_00312680(s3, s3, f20);
    f0 = (f22 - f20) * f24;
    func_00312680(a3, a3, f22 - f0);
    f0 = Mathf_Asin(F(sp, 0x34));
    f4 = (-f0) / f25;
    if (f22 < f4) f4 = f22;
    if (f4 < -1.0f) f4 = -1.0f;
    f23 = 0.0f;
    f21 = f4;
    if (f21 < f23) f21 = f23;
    f0 = f21 + f21;
    f21 = f0 - f22;
    f20 = ((-f4) * __builtin_fabsf(f4) + (f4 + f4)) * f25;
    f21 = (-f21) * __builtin_fabsf(f21) + (f21 + f21);
    f20 = f20 * D_003857F8;
    f21 = f21 * f24 + f24;
    Vec3_RotateX(s3, s3, f20);
    func_00312680(s3, s3, f22 - f21 * D_003857FC);
    f0 = f29 * f21;
    f26 = F(s4, 0xC);
    f20 = f20 - f0;
    f29 = f29 + f20;
    if (f26 <= f23) f26 = f25;
    f22 = sqrtf(F(sp, 0x20) * F(sp, 0x20) + F(sp, 0x28) * F(sp, 0x28));
    f23 = sqrtf(F(sp, 0x40) * F(sp, 0x40) + F(sp, 0x48) * F(sp, 0x48));
    f0 = (*(u32 *)(D_003876A0 + 0x4D8) & 2) ? 256.0f : 512.0f;
    f25 = 0.5f;
    f0 = f0 * f25 / D_00385800;
    f24 = 1.0f;
    f21 = f24;
    f20 = atanf(f0);
    f20 = (f20 + f20) * D_00385804;
    f21 = f20 * f21;
    f20 = f26 - f20;
    f0 = tanf(f21);
    f22 = atanf(f0 * (f23 / f22));
    f23 = F(s4, 8);
    f20 = f22 * f20;
    f23 = f23 / f26;
    f20 = f20 / f26;
    f21 = f21 + f20;
    Vec3_RotateY(s3, s3, f21 * f23);
    f0 = f26 / D_00385808;
    f22 = f22 * f0;
    f21 = f21 + f22;
    f21 = f21 * f25;
    f21 = f21 * f23;
    F(s4, 0x20) = f21;
    f28 = BtlUtil_WrapAngle(f28 - f21);
    {
        f32 x = F(a3, 0) + F(sp, 0);
        f32 y = F(a3, 4) + F(sp, 4);
        f32 z = F(a3, 8) + F(sp, 8);
        F(a3, 0xC) = f24;
        F(a3, 0) = x;
        F(a3, 4) = y;
        F(a3, 8) = z;
    }
    f20 = (-cosf(f27)) * F(sp, 0x40);
    f0 = sinf(f27);
    F(sp, 0x54) = F(sp, 0x44);
    f20 = f20 + f0 * F(sp, 0x48);
    F(sp, 0x50) = f20;
    f20 = sinf(f27) * F(sp, 0x40);
    f0 = cosf(f27);
    f20 = f20 + f0 * F(sp, 0x48);
    F(sp, 0x58) = f20;
    F(sp, 0x5C) = f24;
    F(a1, 0) = F(a3, 0) + F(sp, 0x50);
    F(a1, 4) = F(a3, 4) + F(sp, 0x54);
    F(a1, 0xC) = f24;
    F(a1, 8) = F(a3, 8) + f20;
    F(a2, 0) = f29;
    F(a2, 4) = f28;
    *(s32 *)(a2 + 0xC) = 0;
    *(s32 *)(a2 + 8) = 0;
    F(a1, 4) = F(a1, 4) + func_001FA730(a0);
}
