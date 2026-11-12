#include "common.h"

extern u8 *D_00387AD8;
extern u8 *D_00387AE0;

s32 EftBurst_IsBusy(void);
void Vec4_Set(u8 *a0, f32 f12, f32 f13, f32 f14, f32 f15);
void func_00129C50(u8 *a0, u8 *a1, u8 *a2);
void func_00129B28(u8 *a0, u8 *a1, u8 *a2);
void func_0012A108(u8 *a0, u8 *a1, u8 *a2, u8 *a3, u8 *t0, s32 t1);
s32 EftWater_IsOnScreen(u8 *a0, s32 a1);

#define F(p, o) (*(f32 *)((p) + (o)))
#define W(p, o) (*(s32 *)((p) + (o)))

s32 func_001DAF18(u8 *a0, u8 *a1, u8 *a2, s32 a3, s32 t0, s32 t1, s32 t2, u8 *t3,
                  f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18, f32 f19,
                  s32 sel) {
    u8 sp[0x1b0];   /* tamano de locales del original (antes 0x198) */
    u8 *s0, *t1p, *p, *q;
    s32 s1, v, v0;
    u8 r = a3, g = t0, b = t1, al = t2;
    f32 f20, f21, f22, f23, f24, f25;
    u64 x;

    sel &= 0xFF;
    *(u64 *)(sp + 0) = *(u64 *)(a0 + 0);
    *(u64 *)(sp + 8) = *(u64 *)(a0 + 8);
    W(sp, 0x190) = (s32)t3;
    for (s1 = 0; s1 < 8; s1++) *(u64 *)(sp + 0x10 + s1 * 8) = *(u64 *)(a1 + s1 * 8);
    W(sp, 0x194) = sel;
    for (s1 = 0; s1 < 8; s1++) *(u64 *)(sp + 0x50 + s1 * 8) = *(u64 *)(a2 + s1 * 8);
    v0 = EftBurst_IsBusy();
    if (v0) return v0;
    if (al < 5) return 1;
    f22 = f12 * f15;
    f24 = f12 * f13;
    f25 = f12 * f14;
    f22 = f22 * 0.5f;
    f23 = -f22;
    Vec4_Set(sp + 0x90, f23, 0.0f, f24, 1.0f);
    Vec4_Set(sp + 0xA0, f22, 0.0f, f24, 1.0f);
    Vec4_Set(sp + 0xB0, f23, 0.0f, f25, 1.0f);
    Vec4_Set(sp + 0xC0, f22, 0.0f, f25, 1.0f);
    Vec4_Set(sp + 0x110, f16, f17, 1.0f, 0.0f);
    Vec4_Set(sp + 0x120, f18, f17, 1.0f, 0.0f);
    Vec4_Set(sp + 0x130, f16, f19, 1.0f, 0.0f);
    Vec4_Set(sp + 0x140, f18, f19, 1.0f, 0.0f);
    s0 = sp + 0x90;
    s1 = 3;
    do {
        s1--;
        func_00129C50(s0, sp + 0x10, s0);
        func_00129B28(s0, s0, sp);
        F(s0, 0xC) = 1.0f;
        s0 += 0x10;
    } while (s1 >= 0);
    func_0012A108(sp + 0x150, sp + 0xD0, sp + 0x50, sp + 0x90, sp + 0x110, 4);
    s0 = sp + 0x150;
    s1 = 0;
    p = s0;
    do {
        s0 += 0x10;
        v0 = EftWater_IsOnScreen(p, 4);
        s1++;
        if (!v0) return 0;
        p = s0;
    } while (s1 < 4);
    t1p = D_00387AD8;
    v0 = (s32)t1p + 0x90;
    D_00387AD8 = (u8 *)v0;
    if (!t1p) return v0;
    *(u64 *)(t1p + 0x20) = 0x5C;
    *(u64 *)(t1p + 0x00) = 0xA0000008ULL;
    *(u64 *)(t1p + 0x10) = 0xE400000000008001ULL;
    *(u64 *)(t1p + 0x18) = 0x42142142142160ULL;
    t1p[0x30] = r; t1p[0x31] = g; t1p[0x32] = b; t1p[0x33] = al;
    t1p[0x48] = r; F(t1p, 0x34) = F(sp, 0xD8);
    t1p[0x49] = g; t1p[0x4A] = b; t1p[0x4B] = al;
    t1p[0x60] = r; F(t1p, 0x4C) = F(sp, 0xE8);
    t1p[0x61] = g; t1p[0x62] = b; t1p[0x63] = al;
    t1p[0x78] = r; F(t1p, 0x64) = F(sp, 0xF8);
    t1p[0x79] = g; t1p[0x7A] = b; t1p[0x7B] = al;
    F(t1p, 0x7C) = F(sp, 0x108);
    F(t1p, 0x38) = F(sp, 0xD0);
    F(t1p, 0x3C) = F(sp, 0xD4);
    F(t1p, 0x50) = F(sp, 0xE0);
    F(t1p, 0x54) = F(sp, 0xE4);
    F(t1p, 0x68) = F(sp, 0xF0);
    F(t1p, 0x6C) = F(sp, 0xF4);
    F(t1p, 0x80) = F(sp, 0x100);
    F(t1p, 0x84) = F(sp, 0x104);
    for (s1 = 0; s1 < 4; s1++) {
        static const u16 offs[4] = {0x40, 0x58, 0x70, 0x88};
        static const u16 so[4] = {0x150, 0x160, 0x170, 0x180};
        u8 *d = t1p + offs[s1];
        *(u16 *)(d + 0) = *(u16 *)(sp + so[s1]);
        *(u16 *)(d + 2) = *(u16 *)(sp + so[s1] + 4);
        x = *(u64 *)d;
        x = (x & 0xFF000000FFFFFFFFULL) | ((u64)((u32)W(sp, so[s1] + 8) & 0xFFFFFF) << 32);
        *(u64 *)d = x;
        d[7] = 0xFF;
    }
    *(u64 *)(t1p + 0x28) = *(u64 *)(u32)W(sp, 0x190);
    v = (W(sp, 0x158) + W(sp, 0x188) + (W(sp, 0x178) + W(sp, 0x168))) >> 10;
    sel = W(sp, 0x194);
    if (v >= 0) {
        if (v < 0x1000) {
            q = D_00387AE0 + (v * 2 + sel) * 8;
            v0 = W(q, 4);
        } else {
            q = D_00387AE0 + sel * 8 + 0xFFF0;
            v0 = W(q, 4);
        }
    } else {
        q = D_00387AE0 + sel * 8;
        v0 = W(q, 4);
    }
    W((u8 *)v0, 4) = (s32)t1p;
    W(q, 4) = (s32)t1p;
    return v0;
}
