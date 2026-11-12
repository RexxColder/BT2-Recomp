#include "common.h"

void Vec3_Add(s32 arg0, s32 arg1, s32 arg2);
void Vec3_Sub(s32 arg0, s32 arg1, s32 arg2);
void Vec4_Set(s32 arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void func_00129BB8(f32 farg0, s32 arg0, s32 arg1);
void func_00129BD0(s32 arg0, s32 arg1, f32 farg0);
s32 func_001A2208(s32 arg0);
s32 rand(void);
extern f32 D_00384E64;

s32 func_001A2350(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *s0;
    u8 *s1;
    u8 *s2;
    u8 *s3;
    u8 *s4;
    f32 f0;
    f32 f1;
    f32 f20;
    f32 f21;
    f32 f22;
    f32 t;

    s3 = (u8 *)arg0;
    s2 = (u8 *)arg1;
    s4 = (u8 *)arg3;
    s1 = (u8 *)func_001A2208(arg2);
    if (s1 == 0) {
        return 0;
    }
    s0 = s1 + 0x90;
    f20 = D_00384E64;
    f22 = 1.0f;
    *(s32 *)s1 = *(s32 *)s1 | 1;
    f0 = (f32)rand();
    *(f32 *)(s1 + 0x08) = 0.0f;
    f21 = *(f32 *)(s1 + 0x08);

    f1 = (*(f32 *)(s3 + 0x10) + *(f32 *)(s3 + 0x14) * (f0 / f20)) * 30.0f;
    *(f32 *)(s1 + 0x0C) = f1;
    *(f32 *)(s1 + 0x10) = f1 * *(f32 *)(s3 + 0x18);
    *(u8 *)(s1 + 0x06) = 1;
    *(f32 *)(s1 + 0x14) = f1 - *(f32 *)(s3 + 0x74);
    Vec4_Set((s32)(s1 + 0x40), f21, f21, f21, f22);

    f0 = (f32)rand() / f20;
    *(f32 *)(s1 + 0x80) = *(f32 *)(s2 + 0x10) * f0;
    f0 = (f32)rand() / f20;
    *(f32 *)(s1 + 0x84) = *(f32 *)(s2 + 0x14) * f0;
    f0 = (f32)rand() / f20;
    *(f32 *)(s1 + 0x88) = *(f32 *)(s2 + 0x18) * f0;
    Vec3_Add((s32)(s1 + 0x80), (s32)(s1 + 0x80), (s32)s2);
    *(f32 *)(s1 + 0x8C) = f21;
    f0 = (f32)rand() / f20;
    *(f32 *)(s1 + 0x90) = *(f32 *)(s2 + 0x30) * f0;
    f0 = (f32)rand() / f20;
    *(f32 *)(s1 + 0x94) = *(f32 *)(s2 + 0x34) * f0;
    f0 = (f32)rand() / f20;
    *(f32 *)(s1 + 0x98) = *(f32 *)(s2 + 0x38) * f0;
    Vec3_Add((s32)s0, (s32)s0, (s32)(s2 + 0x20));
    Vec3_Sub((s32)s0, (s32)s0, (s32)s2);
    func_00129BD0((s32)s0, (s32)s0, f22 / *(f32 *)(s1 + 0x0C));

    f0 = (f32)rand() / f20;
    *(f32 *)(s1 + 0x9C) = (*(f32 *)(s2 + 0x0C) + *(f32 *)(s2 + 0x1C) * f0) / *(f32 *)(s3 + 0x70);

    f0 = (f32)rand() / f20;
    t = *(f32 *)(s3 + 0x40) + *(f32 *)(s3 + 0x44) * f0;
    t = *(f32 *)(s4 + 4) * t;
    *(f32 *)(s1 + 0x1C) = t;
    *(f32 *)(s1 + 0x1C) = t * *(f32 *)(s4 + 4);

    f0 = (f32)rand() / f20;
    f1 = (*(f32 *)(s3 + 0x48) + *(f32 *)(s3 + 0x4C) * f0) * *(f32 *)(s4 + 4);
    f1 = f1 - *(f32 *)(s1 + 0x1C);
    *(f32 *)(s1 + 0x24) = f1 / *(f32 *)(s1 + 0x10);
    func_00129BB8(f22, (s32)s0, (s32)s0);
    return 1;
}
