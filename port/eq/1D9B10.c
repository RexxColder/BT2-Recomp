#include "common.h"

extern f32 D_0038559C, D_003855A0, D_003855A4, D_003855A8, D_003855AC, D_003855B0, D_003855B4, D_003855B8;
extern f32 D_003855BC, D_003855C0, D_003855C4, D_003855C8, D_003855CC, D_003855D0, D_003855D4, D_003855D8;
extern f32 D_003855DC, D_003855E0, D_003855E4, D_003855E8, D_003855EC, D_003855F0, D_003855F4, D_003855F8;
extern f32 D_003855FC, D_00385600, D_00385604, D_00385608, D_0038560C;
extern u8 D_00342ED0[];
extern u8 D_00342F40[];

extern s32 rand(void);
extern f32 EftMath_WrapAngle(f32 a);
extern f32 func_0012A3F8(f32 a);
extern f32 Mathf_Cos(f32 a);
extern f32 BtlCharApi_GetHeight(s32 ch);
extern void Vec4_Scale(u8 *dst, u8 *src, f32 s);
extern void Vec4_Set(u8 *dst, f32 x, f32 y, f32 z, f32 w);
extern void func_00129C28(u8 *dst, u8 *src);
extern void func_001D5B18(u8 *pos, u8 *v1, u8 *v2, u8 *c1, u8 *c2, s32 t1, s32 t2, s32 t3,
                          f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18, f32 f19,
                          f32 s0, f32 s1, f32 s2);

#define RF() ((f32)rand() / DIV)

/* Spawns two + four "sparkle" particles around the position *src (16 bytes) of character ch: random angle,
   scale and speed values scaled by the character height; ring 1 (2 particles, uses color bytes 128 and tag
   arg2), ring 2 (4 particles, colors from tables D_00342ED0 / D_00342F40 indexed by arg2). */
void func_001D9B10(u8 *src, s32 ch, s32 arg2) {
    u8 sp[0xC0];
    u8 *pos = sp + 0x20;
    f32 DIV;
    f32 base;
    f32 a;
    f32 f20, f21, f22, f23, f24, f29, f30, f27, f26, f28, f31, f18;
    s32 i;
    s32 id = (s8)arg2;

    __builtin_memcpy(pos, src, 16);
    f28 = D_0038559C;
    f31 = D_003855A0;
    f27 = D_003855A4;
    f26 = 128.0f;
    DIV = D_003855A8;
    base = ((f32)rand() / DIV) * D_003855AC;
    for (i = 0; i < 2; i++) {
        f30 = D_003855B4;
        a = EftMath_WrapAngle(base + D_003855B0 * (f32)i);
        *(f32 *)(sp + 0x40) = func_0012A3F8(a);
        *(f32 *)(sp + 0x44) = Mathf_Cos(a);
        *(s32 *)(sp + 0x48) = 0;
        *(f32 *)(sp + 0x4C) = 1.0f;
        f24 = RF() * D_003855B8 + D_003855BC;
        f23 = RF() * D_003855C0 + D_003855C4;
        f22 = RF() * f31 + D_003855C8;
        f21 = RF() * 5.5f + 9.0f;
        f20 = RF() * D_003855CC + D_003855D0;
        f29 = RF() * D_003855D4 + f31;
        f24 = f24 * (BtlCharApi_GetHeight(ch) * f27);
        f23 = f23 * (BtlCharApi_GetHeight(ch) * f27 * f28);
        f22 = f22 * (BtlCharApi_GetHeight(ch) * f27 * f28);
        f21 = f21 * (BtlCharApi_GetHeight(ch) * f27 * f28);
        f30 = BtlCharApi_GetHeight(ch) * f27 * f28 * f30;
        Vec4_Scale(sp + 0x30, sp + 0x40, f20 * (BtlCharApi_GetHeight(ch) * f27 * f28));
        Vec4_Set(sp + 0x50, f26, f26, f26, 0.0f);
        Vec4_Set(sp + 0x60, f26, f26, f26, 70.0f);
        f20 = RF() * 360.0f;
        f18 = (rand() & 1) ? 1.5f : -1.5f;
        func_001D5B18(pos, sp + 0x30, sp + 0x40, sp + 0x50, sp + 0x60, 1, arg2 << 24 >> 24, 1,
                      f24, -2.0f, f23, f22, f21, f20, f18, f30, 0, f29, 0);
    }
    DIV = D_003855D8;
    f31 = ((f32)rand() / DIV) * D_003855DC;
    f30 = D_003855E0;
    f26 = D_003855E4;
    for (i = 0; i < 4; i++) {
        a = EftMath_WrapAngle(f31 + D_003855E8 * (f32)i);
        f29 = D_003855EC;
        *(f32 *)(sp + 0x80) = func_0012A3F8(a);
        *(f32 *)(sp + 0x84) = Mathf_Cos(a);
        *(s32 *)(sp + 0x88) = 0;
        *(f32 *)(sp + 0x8C) = 1.0f;
        f24 = RF() * f30 + D_003855F0;
        f23 = RF() * D_003855F4 + D_003855F8;
        f22 = RF() * D_003855FC + f30;
        f21 = RF() * 5.5f + 9.0f;
        f20 = RF() * D_00385600 + D_00385604;
        f27 = RF() * D_00385608 + D_0038560C;
        f24 = f24 * (BtlCharApi_GetHeight(ch) * f26);
        f23 = f23 * (BtlCharApi_GetHeight(ch) * f26 * f28);
        f22 = f22 * (BtlCharApi_GetHeight(ch) * f26 * f28);
        f21 = f21 * (BtlCharApi_GetHeight(ch) * f26 * f28);
        f29 = BtlCharApi_GetHeight(ch) * f26 * f28 * f29;
        Vec4_Scale(sp + 0x70, sp + 0x80, f20 * (BtlCharApi_GetHeight(ch) * f26 * f28));
        func_00129C28(sp + 0x90, D_00342ED0 + id * 16);
        func_00129C28(sp + 0xA0, D_00342F40 + id * 16);
        f20 = RF() * 360.0f;
        f18 = (rand() & 1) ? 1.5f : -1.5f;
        func_001D5B18(pos, sp + 0x70, sp + 0x80, sp + 0x90, sp + 0xA0, 0, -1, 0,
                      f24, -2.0f, f23, f22, f21, f20, f18, f29, 0, f27, 0);
    }
}
