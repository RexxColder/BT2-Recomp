#include "common.h"

extern s32 D_00387E9C;
extern f32 D_003854E4;
extern f32 D_003854E8;

s32 rand(void);

/* 0x001D6580 (effect particle state machine). The state byte at +0x6B selects one of five arms (jtbl_0036F0B0):
 * 0 clears the active byte and decrements the counter at g+0x1438; 1 counts the timer at +0x60 down and falls into
 * arm 2 when it expires; 2 sets the fade values (+0x48/+0x4C/+0x50) and advances the state; 3 picks random
 * parameters when the flags byte at +0x6C is clear; 4 resets the state when the flags byte is clear. When the active
 * byte at +0x70 is set, the position (+0x10/+0x14/+0x18) and velocity (+0x20/+0x24/+0x28, +0x34 scale) are
 * integrated, and the two clamps on +0x50/+0x44 apply. */
void func_001D6580(u8 *obj) {
    u8 *g;
    s32 v;
    s32 v1;
    s32 r;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f3;
    f32 f4;
    f32 f5;
    f32 t;
    f32 acc;
    s32 cond;

    v = *(u8 *)(obj + 0x6B);
    if (v < 5) {
        switch (v) {
        case 0:
            *(u8 *)(obj + 0x6F) = 0;
            *(u8 *)(obj + 0x70) = 0;
            g = (u8 *)D_00387E9C;
            *(s32 *)(g + 0x1438) = *(s32 *)(g + 0x1438) - 1;
            break;

        case 1:
            f0 = *(f32 *)(obj + 0x60) - 1.0f;
            *(f32 *)(obj + 0x60) = f0;
            if (!(f0 <= 0.0f)) {
                break;
            }
            *(f32 *)(obj + 0x60) = 0.0f;
            goto arm_fade;

        case 2:
        arm_fade:
            *(u8 *)(obj + 0x70) = 1;
            *(u8 *)(obj + 0x6B) = *(u8 *)(obj + 0x6B) + 1;
            *(u8 *)(obj + 0x6C) = *(u8 *)(obj + 0x6C) | 4;
            *(f32 *)(obj + 0x50) = 128.0f;
            *(f32 *)(obj + 0x48) = D_003854E4;
            *(f32 *)(obj + 0x4C) = 85.0f;
            *(u8 *)(obj + 0x6B) = *(u8 *)(obj + 0x6B) + 1;
            *(s32 *)(obj + 0x44) = 0;
            break;

        case 3:
            if (*(u8 *)(obj + 0x6C) == 0) {
                r = rand();
                f2 = D_003854E8;
                f0 = (f32)r;
                f1 = *(f32 *)(obj + 0x44);
                f3 = 1.5f;
                f5 = 140.0f;
                f4 = 0.0f;
                f0 = f0 / f2;
                f2 = f5 - f1;
                f0 = f0 + f0;
                f1 = f0 + f3;
                *(f32 *)(obj + 0x48) = f2;
                if (f1 != f4) {
                    *(f32 *)(obj + 0x48) = f2 / (f1 * 30.0f);
                }
                f0 = *(f32 *)(obj + 0x50);
                f2 = f4 - f0;
                *(f32 *)(obj + 0x4C) = f5;
                *(u8 *)(obj + 0x6C) = *(u8 *)(obj + 0x6C) | 4;
                *(f32 *)(obj + 0x54) = f2;
                if (f1 != f4) {
                    *(f32 *)(obj + 0x54) = f2 / (f1 * 30.0f);
                }
                v1 = *(u8 *)(obj + 0x6B);
                *(u8 *)(obj + 0x6C) = *(u8 *)(obj + 0x6C) | 2;
                *(f32 *)(obj + 0x58) = f4;
                *(u8 *)(obj + 0x6B) = (u8)(v1 + 1);
            }
            break;

        case 4:
            if (*(u8 *)(obj + 0x6C) == 0) {
                *(u8 *)(obj + 0x6B) = 0;
            }
            break;

        default:
            break;
        }
    }

    if (*(u8 *)(obj + 0x70) != 0) {
        t = *(f32 *)(obj + 0x34);
        f1 = *(f32 *)(obj + 0x24) * t;
        *(f32 *)(obj + 0x14) = (*(f32 *)(obj + 0x14) + f1) + *(f32 *)(obj + 0x5C);
        *(f32 *)(obj + 0x10) = *(f32 *)(obj + 0x10) + *(f32 *)(obj + 0x20) * t;
        *(f32 *)(obj + 0x18) = *(f32 *)(obj + 0x18) + *(f32 *)(obj + 0x28) * t;
        *(f32 *)(obj + 0x34) = t + t * *(f32 *)(obj + 0x38);
        *(f32 *)(obj + 0x3C) = *(f32 *)(obj + 0x3C) + *(f32 *)(obj + 0x40);

        v1 = *(u8 *)(obj + 0x6C);
        if ((v1 & 2) != 0) {
            acc = *(f32 *)(obj + 0x50) + *(f32 *)(obj + 0x54);
            *(f32 *)(obj + 0x50) = acc;
            if (0.0f < *(f32 *)(obj + 0x54)) {
                cond = *(f32 *)(obj + 0x58) < acc;
            } else {
                cond = acc < *(f32 *)(obj + 0x58);
            }
            if (cond) {
                *(f32 *)(obj + 0x50) = *(f32 *)(obj + 0x58);
                v1 = v1 & ~2;
                *(u8 *)(obj + 0x6C) = (u8)v1;
            }
        }

        if ((v1 & 4) != 0) {
            acc = *(f32 *)(obj + 0x44) + *(f32 *)(obj + 0x48);
            *(f32 *)(obj + 0x44) = acc;
            if (0.0f < *(f32 *)(obj + 0x48)) {
                cond = *(f32 *)(obj + 0x4C) < acc;
            } else {
                cond = acc < *(f32 *)(obj + 0x4C);
            }
            if (cond) {
                *(f32 *)(obj + 0x44) = *(f32 *)(obj + 0x4C);
                *(u8 *)(obj + 0x6C) = (u8)(v1 & ~4);
            }
        }
    }
}
