#include "common.h"

f32 sinf(f32 arg0);

#define F(o) (*(f32 *)(a + (o)))
#define I(o) (*(s32 *)(a + (o)))
#define H(o) (*(u16 *)(a + (o)))

void func_003B6DE8(u8 *a) {
    u8 *s5;
    s32 s7, fp, i, x, y;
    u32 fl, v3, a0, v0;
    f32 f21, f1, f2, f3, f0, f20, f4;

    fl = H(0);
    if (fl == 0) return;
    s5 = *(u8 **)(a + 4);
    if (*(s32 *)s5 & 2) return;
    s7 = *(s32 *)(s5 + 0xC) - *(s32 *)(s5 + 4);
    fp = *(s32 *)(s5 + 0x10) - *(s32 *)(s5 + 8);

    if (fl & 1) {
        f0 = F(0xC) + 1.0f;
        f2 = F(0x10);
        F(0xC) = f0;
        if (f0 < f2) {
            f21 = f0 / f2;
            for (i = 0; i < 2; i++) {
                s32 st = I(0x20 + 4 * i);
                f3 = (f32)(I(0x28 + 4 * i) - st);
                F(0x18 + 4 * i) = (f32)st + f3 * f21;
                if (H(8) & 2) {
                    f20 = F(0x14) / 100.0f;
                    f20 = f3 * f20;
                    f0 = sinf(f21 * 3.1415925f);
                    F(0x18 + 4 * i) = F(0x18 + 4 * i) + f0 * f20;
                }
            }
            v0 = H(8);
        } else {
            f1 = (f32)I(0x28);
            I(0xC) = 0;
            f0 = (f32)I(0x2C);
            I(0x10) = 0;
            H(8) = 0;
            F(0x18) = f1;
            F(0x1C) = f0;
            v0 = H(8);
        }
        if (v0 == 0) H(0) = H(0) & 0xFFFE;
        x = (s32)F(0x18);
        *(s32 *)(s5 + 4) = x;
        *(s32 *)(s5 + 0xC) = x + s7;
        y = (s32)F(0x1C);
        *(s32 *)(s5 + 8) = y;
        *(s32 *)(s5 + 0x10) = y + fp;
        fl = H(0);
    }

    if (fl & 2) {
        f1 = F(0x34) + 1.0f;
        f2 = F(0x38);
        f21 = f1 / f2;
        F(0x34) = f1;
        if (f1 < f2) {
            for (i = 0; i < 2; i++) {
                f0 = F(0x54 + 4 * i);
                f1 = (F(0x5C + 4 * i) - f0) * f21;
                F(0x4C + 4 * i) = f0 + f1;
            }
            v3 = H(0x30);
        } else {
            for (i = 0; i < 2; i++) {
                F(0x4C + 4 * i) = F(0x5C + 4 * i);
            }
            H(0x30) = H(0x30) | 1;
            v3 = H(0x30);
        }
        v0 = 1; /* X handled */
        if (v3 & 2) {
            f2 = F(0x44);
            f1 = f2 * 0.0f;
            f3 = F(0x3C) + f1;
            f2 = f2 * F(0x4C);
            f0 = f3 + f2;
            *(s32 *)(s5 + 4) = (s32)f3;
            *(s32 *)(s5 + 0xC) = (s32)f0;
            v3 = H(0x30);
        } else if (v3 & 4) {
            f1 = F(0x44);
            f0 = f1 * F(0x4C);
            f3 = F(0x3C);
            f1 = f1 * 0.5f;
            f2 = f0 * 0.5f;
            f3 = f3 + f1;
            f0 = f3 + f2;
            f1 = f3 - f2;
            *(s32 *)(s5 + 0xC) = (s32)f0;
            *(s32 *)(s5 + 4) = (s32)f1;
            v3 = H(0x30);
        } else if (v3 & 8) {
            f2 = F(0x44);
            f0 = F(0x3C);
            f1 = F(0x4C);
            f3 = f0 + f2;
            f2 = f2 * f1;
            *(s32 *)(s5 + 0xC) = (s32)f3;
            f0 = f3 - f2;
            *(s32 *)(s5 + 4) = (s32)f0;
            v3 = H(0x30);
        } else {
            v0 = 0; /* skip the 0x10 test */
        }
        if (v0 && (v3 & 0x10)) {
            f2 = F(0x48);
            f1 = f2 * 0.0f;
            f0 = F(0x50);
            f3 = F(0x40) + f1;
            f2 = f2 * f0;
            f0 = f3 + f2;
            *(s32 *)(s5 + 8) = (s32)f3;
            *(s32 *)(s5 + 0x10) = (s32)f0;
            v3 = H(0x30);
            v0 = v3 & 1;
        } else if (v3 & 0x20) {
            f1 = F(0x48);
            f0 = f1 * F(0x50);
            f3 = F(0x40);
            f1 = f1 * 0.5f;
            f2 = f0 * 0.5f;
            f3 = f3 + f1;
            f0 = f3 + f2;
            f1 = f3 - f2;
            *(s32 *)(s5 + 0x10) = (s32)f0;
            *(s32 *)(s5 + 8) = (s32)f1;
            v3 = H(0x30);
            v0 = v3 & 1;
        } else if (v3 & 0x40) {
            f2 = F(0x48);
            f0 = F(0x40);
            f1 = F(0x50);
            f3 = f0 + f2;
            f2 = f2 * f1;
            *(s32 *)(s5 + 0x10) = (s32)f3;
            f0 = f3 - f2;
            *(s32 *)(s5 + 8) = (s32)f0;
            v3 = H(0x30);
            v0 = v3 & 1;
        } else {
            v0 = v3 & 1;
        }
        if (v0) {
            H(0x30) = 0;
            v3 = 0;
        }
        if (v3 != 0) {
            fl = H(0);
        } else {
            H(0) = H(0) & 0xFFFD;
            fl = H(0);
        }
    }

    if (fl & 4) {
        a0 = H(0x64);
        if (a0 & 4) {
            f0 = F(0x68) + 1.0f;
            f2 = F(0x6C);
            F(0x68) = f0;
            if (f2 <= f0) {
                H(0x64) = 0;
                a0 = 0;
            }
        } else if (a0 & 1) {
            f0 = F(0x68) + 1.0f;
            f2 = F(0x6C);
            F(0x68) = f0;
            if (f2 <= f0) {
                v0 = (a0 & 0xFFFE) | 2;
                F(0x68) = f2;
                H(0x64) = v0;
                a0 = v0;
            }
        } else if (a0 & 2) {
            f0 = F(0x68) - 1.0f;
            f2 = 0.0f;
            F(0x68) = f0;
            if (f0 <= f2) {
                v0 = (a0 & 0xFFFD) | 1;
                F(0x68) = f2;
                H(0x64) = v0;
                a0 = v0;
            }
        }
        if (a0 == 0) H(0) = H(0) & 0xFFFB;
        f2 = F(0x68);
        f0 = F(0x6C);
        f1 = F(0x74);
        f21 = f2 / f0;
        f3 = F(0x78) - f1;
        f0 = f3 * f21;
        f1 = f1 + f0;
        f2 = f1 * 255.0f;
        F(0x70) = f1;
        *(s32 *)(s5 + 0x34) = (s32)f2;
        fl = H(0);
    }

    if (fl & 8) {
        f4 = 1.0f;
        f0 = F(0x80) + f4;
        f3 = F(0x88);
        f1 = F(0x8C);
        f2 = F(0x84);
        f3 = f3 + f1;
        F(0x80) = f0;
        F(0x88) = f3;
        if (f2 <= f0) {
            a0 = H(0x7C);
            if (a0 & 1) {
                F(0x88) = f4;
                H(0x7C) = 0;
            } else if (a0 & 2) {
                I(0x88) = 0;
                H(0x7C) = 0;
            } else {
                H(0x7C) = 0;
            }
            v0 = H(0x7C);
        } else if (f4 <= f3) {
            F(0x88) = f4;
            H(0x7C) = 0;
            v0 = H(0x7C);
        } else {
            f0 = 0.0f;
            if (f3 <= f0) {
                F(0x88) = f0;
                H(0x7C) = 0;
            }
            v0 = H(0x7C);
        }
        if (v0 == 0) H(0) = H(0) & 0xFFF7;
        f1 = F(0x88);
        f0 = F(0x90) * f1;
        *(s32 *)(s5 + 0x34) = (s32)f0;
        fl = H(0);
    }

    if (fl & 0x10) {
        u8 *s0 = a + 0xAC;
        u8 *s3 = a + 0x94;
        u8 *s1 = a + 0xA4;
        s32 s2 = 1;
        do {
            f1 = *(f32 *)s0;
            f0 = f1 + *(f32 *)(s1 + 0x10);
            *(f32 *)s0 = f0;
            if (3.1415925f <= f0) {
                *(f32 *)s0 = f0 - 6.283185f;
            }
            f0 = sinf(*(f32 *)s0);
            s2 -= 1;
            f1 = *(f32 *)s1;
            s1 += 4;
            *(f32 *)(s0 - 0x10) = f0 * f1;
            s0 += 4;
        } while (s2 >= 0);
        f1 = *(f32 *)(s3 + 8);
        f0 = *(f32 *)s3 + f1;
        x = (s32)f0;
        *(s32 *)(s5 + 4) = x;
        *(s32 *)(s5 + 0xC) = x + s7;
        f1 = *(f32 *)(s3 + 0xC);
        f0 = *(f32 *)(s3 + 4) + f1;
        y = (s32)f0;
        *(s32 *)(s5 + 8) = y;
        *(s32 *)(s5 + 0x10) = y + fp;
    }
}
