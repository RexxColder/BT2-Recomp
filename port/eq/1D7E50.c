#include "common.h"

extern f32 D_00385504;
extern f32 D_00385508;
extern f32 D_0038550C;
extern f32 D_00385510;
extern f32 D_00385514;
extern f32 D_00385518;
extern f32 D_0038551C;
extern f32 D_00385520;
extern f32 D_00385524;
extern f32 D_00385528;
extern f32 D_0038552C;

s32 rand();
f32 BtlCharApi_GetHeight(s32 arg0);
void Vec4_Set(u8 *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void func_002088F0(s32 arg0, u8 *arg1);
f32 func_0012A3F8(f32 farg0);
f32 Mathf_Cos(f32 farg0);
void Vec3_Cross(u8 *arg0, u8 *arg1, u8 *arg2);
void Vec3_Normalize(u8 *arg0, u8 *arg1);
void func_00129BB8(u8 *arg0, u8 *arg1, f32 farg0);
void func_00129DE0(u8 *arg0, u8 *arg1, u8 *arg2, f32 farg0);
void func_00129B28(u8 *arg0, u8 *arg1, u8 *arg2);
void func_001D4E70(s32 a0, u8 *a1, u8 *a2, u8 *a3, s32 t0, s32 t1, s32 t2, s32 t3,
                   f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18, f32 f19,
                   f32 s0, f32 s8, f32 s10, s32 s18, s32 s20, f32 s28);
void func_001D4678(s32 arg0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7,
                   f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18, f32 f19,
                   f32 st0, f32 st1, f32 st2, f32 st3);

#define F(o) (*(f32 *)(sp + (o)))

void func_001D7E50(s32 arg0, f32 farg0, f32 farg1, f32 farg2) {
    u8 sp[0x180] __attribute__((aligned(16)));
    f32 f20, f21, f31, f30, f29, f28, f25, f26, f18, f0;
    s32 v0, v1;

    F(0xD0) = farg2;
    Vec4_Set(sp + 0xA0, 0.0f, -1.0f, 0.0f, 1.0f);
    v0 = rand();
    f20 = (f32)v0 / D_00385504 * D_00385508 - D_0038550C;
    func_002088F0(arg0, sp + 0xC0);
    f0 = func_0012A3F8(F(0xC4) + f20);
    F(0x44) = 0.0f;
    F(0x40) = -f0;
    f0 = Mathf_Cos(F(0xC4) + f20);
    F(0x4C) = 1.0f;
    F(0x48) = -f0;
    Vec3_Cross(sp + 0xB0, sp + 0x40, sp + 0xA0);
    Vec3_Normalize(sp + 0xB0, sp + 0xB0);
    if (farg0 == 0.0f) {
        f20 = 0.0f;
    } else {
        f20 = farg0 / 90.0f;
    }
    if (farg1 == 0.0f) {
        f21 = 0.0f;
    } else {
        f21 = farg1 / 90.0f;
    }
    f0 = -1.0f;
    if (!(f20 < 0.0f)) f0 = 1.0f;
    func_00129BB8(sp + 0x60, sp + 0xB0, f0);
    f0 = -1.0f;
    if (!(f21 < 0.0f)) f0 = 1.0f;
    func_00129BB8(sp + 0x70, sp + 0x40, f0);
    f0 = f20;
    if (f0 < 0.0f) f0 = -f0;
    func_00129DE0(sp + 0x60, sp + 0x60, sp + 0xA0, f0);
    f0 = f21;
    if (f0 < 0.0f) f0 = -f0;
    f21 = D_00385510;
    func_00129DE0(sp + 0x70, sp + 0x70, sp + 0xA0, f0);
    func_00129B28(sp + 0x50, sp + 0x60, sp + 0x70);
    Vec3_Normalize(sp + 0x50, sp + 0x50);

    v0 = rand();
    f0 = (f32)v0 / f21;
    f31 = (f0 + f0) + 1.5f;
    v0 = rand();
    f30 = (f32)v0 / f21 + 1.0f;
    v0 = rand();
    f29 = (f32)v0 / f21 * 1.5f + 1.5f;
    v0 = rand();
    f28 = (f32)v0 / f21 * 5.0f + 9.0f;
    v0 = rand();
    f25 = (f32)v0 / f21 * D_0038551C + D_00385520;
    f20 = D_00385514;
    f26 = D_00385518;
    f31 = f31 * (BtlCharApi_GetHeight(arg0) * f20);
    f30 = f30 * (BtlCharApi_GetHeight(arg0) * f20);
    f29 = f29 * (BtlCharApi_GetHeight(arg0) * f20);
    f28 = f28 * (BtlCharApi_GetHeight(arg0) * f20);
    f0 = BtlCharApi_GetHeight(arg0) * f20;
    Vec4_Set(sp + 0x30, 0.0f, 0.0f, 0.0f, 1.0f);
    f26 = f0 * f26;
    f0 = BtlCharApi_GetHeight(arg0) * f20;
    F(0x34) = F(0x34) - 0.0f;
    F(0x30) = F(0x30) - (F(0x40) * 6.0f) * f0;
    f0 = BtlCharApi_GetHeight(arg0) * f20;
    F(0x3C) = 1.0f;
    F(0x38) = F(0x38) - (F(0x48) * 6.0f) * f0;
    v0 = rand();
    v1 = v0;
    if (v0 < 0) v1 = v0 + 31;
    v1 = (v1 >> 5) << 5;
    F(0) = D_00385524;
    f18 = (f32)(0x60 - (v0 - v1));
    f0 = F(0xD0);
    f0 = D_00385528;
    func_001D4E70(arg0, sp + 0x30, sp + 0x40, sp + 0x50, 0x80, 0x80, 0x80, 1,
                  f31, -10.0f, f30, f29, f28, 0.0f, f18, f26,
                  D_00385524, f25, 0.0f, 9, 0, F(0xD0));
    f26 = D_00385528;

    v0 = rand();
    f0 = (f32)v0 / f21;
    f31 = (f0 + f0) + 1.5f;
    v0 = rand();
    f30 = (f32)v0 / f21 + 1.0f;
    v0 = rand();
    f29 = (f32)v0 / f21 + 0.5f;
    v0 = rand();
    f28 = (f32)v0 / f21 * 5.0f + 11.0f;
    v0 = rand();
    f25 = (f32)v0 / f21 * 0.25f + 0.5f;
    f31 = f31 * (BtlCharApi_GetHeight(arg0) * f20);
    f30 = f30 * (BtlCharApi_GetHeight(arg0) * f20);
    f29 = f29 * (BtlCharApi_GetHeight(arg0) * f20);
    f28 = f28 * (BtlCharApi_GetHeight(arg0) * f20);
    f0 = BtlCharApi_GetHeight(arg0) * f20;
    Vec4_Set(sp + 0x30, 0.0f, 0.0f, 0.0f, 1.0f);
    f26 = f0 * f26;
    f0 = BtlCharApi_GetHeight(arg0) * f20;
    F(0x30) = F(0x30) - (F(0x40) * 6.0f) * f0;
    f0 = BtlCharApi_GetHeight(arg0) * f20;
    F(0x34) = F(0x34) - f0 * 3.0f;
    f0 = BtlCharApi_GetHeight(arg0) * f20;
    F(0x38) = F(0x38) - (F(0x48) * 6.0f) * f0;
    F(0x3C) = 1.0f;
    Vec4_Set(sp + 0x80, 128.0f, 128.0f, 128.0f, 0.0f);
    v0 = rand();
    v1 = v0;
    if (v0 < 0) v1 = v0 + 31;
    v1 = (v1 >> 5) << 5;
    Vec4_Set(sp + 0x90, 128.0f, 128.0f, 128.0f, (f32)(0x60 - (v0 - v1)));
    v0 = rand();
    f20 = (f32)v0 / f21 * 360.0f;
    v0 = rand();
    f18 = 1.5f;
    if (!(v0 & 1)) f18 = -1.5f;
    func_001D4678(arg0, (s32)(sp + 0x30), (s32)(sp + 0x40), (s32)(sp + 0x80), (s32)(sp + 0x90), 1, 0xB, 0,
                         f31, -10.0f, f30, f29, f28, f20, f18, f26,
                         D_0038552C, f25, 0.0f, F(0xD0));
}
