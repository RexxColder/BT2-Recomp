#include "common.h"

extern f32 D_003851D4;
extern f32 D_003851D8;
extern f32 D_003851DC;
extern f32 D_003851E0;
extern f32 D_003851E4;

s32 rand(void);

#define S32F(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define F32F(p, off) (*(f32 *)((u8 *)(p) + (off)))
#define U8F(p, off) (*(u8 *)((u8 *)(p) + (off)))

f32 func_001CB6E8(s32 arg0) {
    u8 *s0;
    u8 *s1;
    u8 *a0p;
    s32 v0;
    s32 v1;
    s32 v0_3;
    s32 v0_4;
    s32 divisor;
    s32 rem;
    s32 quo;
    s32 bval;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f3;
    f32 f4;
    f32 f5;
    f32 f6;

    s0 = (u8 *)arg0;
    f1 = F32F(s0, 0x5C);
    s1 = (u8 *)S32F(s0, 0x34);
    if (f1 <= 0.0f) {
        a0p = (u8 *)S32F(s0, 0x38);
        v1 = S32F(s0, 0x40);
        v0_3 = v1 & 2;
        if (!(v1 & 0x20)) {
            f0 = F32F(s0, 0x8C) + F32F(s0, 0x70);
            F32F(s0, 0x8C) = f0;
            f1 = F32F(a0p, 0xC);
            if (f1 <= f0) {
                v1 = v1 | 0x20;
                F32F(s0, 0x8C) = f1;
                S32F(s0, 0x40) = v1;
                v0_3 = v1 & 2;
            }
        }
        if (v0_3 != 0 && F32F(s0, 0x60) <= 0.0f) {
            f2 = F32F(s0, 0x8C);
            if (!(v1 & 0x40)) {
                v1 = v1 | 0x40;
                S32F(s0, 0x40) = v1;
                f0 = -f2 / F32F(s1, 0x20);
                F32F(s0, 0x70) = f0;
            }
            f0 = F32F(s0, 0x70);
            f0 = f2 + f0;
            F32F(s0, 0x8C) = f0;
        }

        f0 = F32F(s0, 0x6C);
        f1 = f0 + F32F(s1, 4);
        F32F(s0, 0x6C) = f1;
        if (D_003851D4 <= f1) {
            f0 = f1 - D_003851D8;
            F32F(s0, 0x6C) = f0;
        } else if (f1 <= D_003851DC) {
            f0 = f1 + D_003851E0;
            F32F(s0, 0x6C) = f0;
        }

        f5 = F32F(s0, 0x74);
        f6 = F32F(s0, 0x78);
        f4 = F32F(s0, 0xC);
        f3 = f5 / f6;
        f0 = F32F(s0, 0x7C) * f3;
        f2 = F32F(s1, 0x10) + f0;
        F32F(s0, 0x64) = F32F(s1, 8) * f2 * f4;
        F32F(s0, 0x68) = F32F(s1, 0xC) * f2 * f4;

        if (!(v1 & 0x80)) {
            f0 = f5 + 1.0f;
            F32F(s0, 0x74) = f0;
            if (f6 <= f0) {
                v0 = v1 | 0x80;
                F32F(s0, 0x74) = f6;
                S32F(s0, 0x40) = v0;
                v1 = v0;
            }
        } else {
            f0 = f5 - 1.0f;
            F32F(s0, 0x74) = f0;
            if (f0 <= 0.0f) {
                F32F(s0, 0x74) = 0.0f;
                v0 = v1 & ~0x80;
                S32F(s0, 0x40) = v0;
                v1 = v0;
            }
        }

        v0_3 = v1 & 2;
        if (v1 & 0x100) {
            divisor = S32F(s1, 0x24);
            bval = U8F(s0, 0x45);
            f1 = F32F(s0, 0x4C);
            rem = bval % divisor;
            f0 = (f32)rem * f1;
            F32F(s0, 0x90) = f0;
            F32F(s0, 0x94) = f0 + f1;
            quo = bval / divisor;
            f1 = F32F(s0, 0x50);
            f0 = (f32)quo * f1;
            F32F(s0, 0x98) = f0;
            F32F(s0, 0x9C) = f0 + f1;
            f1 = F32F(s0, 0x54) + ((f32)rand() / D_003851E4);
            F32F(s0, 0x54) = f1;
            f0 = F32F(s1, 0x2C);
            if (f0 <= f1) {
                f1 = f1 - f0;
                F32F(s0, 0x54) = f1;
                bval = U8F(s0, 0x45);
                f0 = (f32)bval + 1.0f;
                if (f0 < 2147483648.0f) {
                    U8F(s0, 0x45) = (u8)(s32)f0;
                } else {
                    f0 = f0 - 2147483648.0f;
                    U8F(s0, 0x45) = (u8)(s32)f0;
                }
                if ((s32)U8F(s0, 0x45) >= S32F(s0, 0x48)) {
                    U8F(s0, 0x45) = 0;
                }
            }
            v1 = S32F(s0, 0x40);
            v0_3 = v1 & 2;
        }
    } else {
        v1 = S32F(s0, 0x40);
        f0 = f1 - 1.0f;
        F32F(s0, 0x5C) = f0;
        v0_3 = v1 & 2;
    }

    if (v0_3 != 0) {
        f1 = F32F(s0, 0x60);
        if (0.0f < f1) {
            F32F(s0, 0x60) = f1 - 1.0f;
        }
        f0 = F32F(s0, 0x8C);
        if (f0 <= 0.0f) {
            v1 = v1 | 4;
            S32F(s0, 0x40) = v1;
        }
        v0_4 = v1 & 8;
    } else {
        v0_4 = v1 & 8;
    }

    if (v0_4 == 0) {
        f0 = F32F(s0, 0x5C);
        if (f0 <= 0.0f) {
            f0 = F32F(s0, 0x58) - 1.0f;
            F32F(s0, 0x58) = f0;
            if (f0 <= 0.0f) {
                S32F(s0, 0x40) = v1 | 2;
            }
        }
    }
    return f0;
}
