#include "common.h"

#define PTR(v) ((u8 *)(s32)(v))
#define LDF(p, off) (*(f32 *)((u8 *)(p) + (off)))
#define STF(p, off, v) (*(f32 *)((u8 *)(p) + (off)) = (v))

extern f32 D_003854D4;
extern u8 *D_00387E9C;

/* 0x001D5188: per-frame motion step of an object (state byte +0x77). State 0 counts +0x6C down by 1.0 and
 * switches to state 1 when it reaches 0; state 1 integrates position (+0x10..+0x18) and speed (+0x40, +0x48,
 * +0x5C..+0x60) with the scale factors +0x44 and +0x4C. A finished object (+0x7C set, +0x5C <= 0) is cleared
 * and decrements the counter at D_00387E9C+0x142C. */
void func_001D5188(s32 arg0) {
    u8 *o;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f3;
    f32 f4;
    f32 f5;
    f32 f6;
    f32 f7;
    f32 f8;
    u8 *c;
    s32 st;
    s32 physics;

    o = PTR(arg0);
    st = o[0x77];
    physics = 0;

    if (st == 0) {
        f0 = LDF(o, 0x6C) - 1.0f;
        STF(o, 0x6C, f0);
        if (f0 <= 0.0f) {
            STF(o, 0x6C, 0.0f);
            o[0x7C] = 1;
            o[0x77] = 1;
            physics = 1;
        }
    } else if (st == 1) {
        physics = 1;
    }

    if (physics) {
        f0 = LDF(o, 0x40);
        f3 = LDF(o, 0x20) * f0;
        f5 = LDF(o, 0x24) * f0;
        f7 = LDF(o, 0x28) * f0;
        f6 = f0 * LDF(o, 0x44);
        f4 = LDF(o, 0x10) + f3;
        f1 = LDF(o, 0x14) + f5;
        f2 = LDF(o, 0x18) + f7;
        f0 = f0 + f6;
        f8 = LDF(o, 0x48);
        f3 = LDF(o, 0x50);
        STF(o, 0x10, f4);
        STF(o, 0x14, f1);
        STF(o, 0x18, f2);
        STF(o, 0x40, f0);
        if (f3 < f8) {
            f0 = LDF(o, 0x4C) * D_003854D4;
        } else {
            f0 = LDF(o, 0x4C);
        }
        STF(o, 0x48, f8 + f0);

        f0 = LDF(o, 0x5C) + LDF(o, 0x60);
        f1 = LDF(o, 0x14) + LDF(o, 0x64);
        f2 = LDF(o, 0x58);
        STF(o, 0x5C, f0);
        STF(o, 0x14, f1);
        if (f2 <= f0) {
            f0 = -f2;
            f1 = LDF(o, 0x68);
            STF(o, 0x5C, f2);
            STF(o, 0x60, f0 / f1);
        }
    }

    if (o[0x7C] != 0) {
        f0 = LDF(o, 0x5C);
        if (f0 <= 0.0f) {
            STF(o, 0x5C, 0.0f);
            o[0x7C] = 0;
            o[0x7B] = 0;
            c = D_00387E9C;
            *(s32 *)(c + 0x142C) = *(s32 *)(c + 0x142C) - 1;
        }
    }
}
