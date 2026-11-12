#include "common.h"

extern f32 D_003854B8;
extern f32 D_003854BC;
extern f32 D_003854C0;
extern f32 D_003854C4;
extern f32 D_003854C8;
extern f32 D_003854CC;
extern u8 *D_00387E9C;

typedef s32 (*Vec4SetInts)(void *, s32, f32, f32, f32, f32);
s32 Vec4_Set(void *arg0, f32 farg0, f32 farg1, f32 farg2, f32 farg3);
void func_001D3BF8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 farg0, f32 farg1, f32 farg2);
void func_001D4678(s32 arg0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7,
                   f32 f12, f32 f13, f32 f14, f32 f15, f32 f16, f32 f17, f32 f18, f32 f19,
                   f32 st0, f32 st1, f32 st2, f32 st3);
s32 rand(void);

void func_001D40E0(void) {
    u8 *base;
    u8 *p;
    u8 *s1;
    s32 n;
    s32 ri;
    s32 r;
    s32 r2;
    s32 m2;
    s32 a1v;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f3;
    f32 f4;
    f32 f12;
    f32 f14;
    f32 f15;
    f32 f16;
    f32 f18;
    f32 f20;
    f32 f21;
    f32 f22;
    f32 f23;
    f32 sp20[4];
    f32 sp30[4];

    base = D_00387E9C;
    if (*(s32 *)(base + 0x1424) != 0) {
        f23 = D_003854B8;
        f22 = D_003854BC;
        f20 = 96.0f;
        f21 = 8.0f;
        p = base;
        n = 0x1F;
        do {
            if (p[0x99] != 0 && p[0x98] != 0) {
                f1 = *(f32 *)(p + 0x74) / f23;
                f3 = *(f32 *)(p + 0x88);
                p[0x98] = 0;
                f0 = (f3 * f21) * f20;
                f4 = f1 * f22;
                f0 = f0 / f20;
                f1 = f1 + f1;
                f3 = f3 * f4;
                f2 = f1 * f3;
                f0 = f20 - f0;
                f2 = f2 / f1;

                /* cvt.w.s: truncates toward zero */
                ri = (s32)f0;

                if (f1 < f3) {
                    f12 = D_003854C0;
                } else {
                    f12 = f1 - f2;
                }
                if (ri > 0) {
                    func_001D3BF8(p + 0x20, ri, 0, *(s32 *)(p + 0x94), f12, D_003854C4,
                                  *(f32 *)(p + 0x8C));
                }
            }
            n -= 1;
            p += 0xA0;
        } while (n >= 0);
    }

    base = D_00387E9C;
    if (*(s32 *)(base + 0x1430) != 0) {
        s1 = *(u8 **)(base + 0x140C);
        n = 0x11;
        do {
            if (s1[0x5B] != 0 && s1[0x5A] != 0) {
                a1v = s1[0x54];
                s1[0x5A] = 0;
                ((Vec4SetInts)Vec4_Set)(sp20, a1v, (f32)a1v, (f32)s1[0x55], (f32)s1[0x56], 0.0f);
                Vec4_Set(sp30, (f32)s1[0x54], (f32)s1[0x55], (f32)s1[0x56],
                         *(f32 *)(s1 + 0x38));

                r = rand();
                f20 = ((f32)r / D_003854C8) * 360.0f;
                r2 = rand();
                m2 = r2 % 2;
                f0 = *(f32 *)(s1 + 0x34) * (f32)m2;
                f18 = (f0 == 0.0f) ? -1.0f : 1.0f;
                f14 = *(f32 *)(s1 + 0x28) * 1.5f;
                f15 = *(f32 *)(s1 + 0x2C) * -2.5f;
                f16 = (f32)*(s32 *)(s1 + 0x50) * D_003854CC;
                f16 = 5.0f - f16;
                f16 = *(f32 *)(s1 + 0x28) * f16;
                f0 = *(f32 *)(s1 + 0x44) / 30.0f;

                /* 8 int regs, 8 float regs, then four stack slots st0..st3 (all f32) */
                func_001D4678(0, (s32)s1, (s32)(s1 + 0x10), (s32)sp20, (s32)sp30, 0,
                              s1[0x58], s1[0x59],
                              0.0f, 0.0f, f14, f15, f16, f20, f18, 0.0f,
                              0.0f, f0, 0.0f, *(f32 *)(s1 + 0x4C));
            }
            n -= 1;
            s1 += 0x60;
        } while (n >= 0);
    }
}
