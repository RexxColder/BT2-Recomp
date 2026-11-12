#include "common.h"

s32 func_001A2350(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_001A2F10(f32 farg0, s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 rand(void);
extern f32 D_00384E74;
extern f32 D_00384E78;
extern f32 D_00384E7C;
extern f32 D_00384E80;

void func_001A3FC0(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3) {
    u8 *e;
    u8 *t;
    u8 *s0;
    u8 *fp;
    f32 f0;
    f32 f1;
    f32 f2;
    f32 f3;
    f32 f20;
    s32 s4;
    s32 v0;

    e = arg0 + (arg3 << 7) + 4;
    f20 = (f32)e[0];
    if (e[1] != 0) {
        f20 = (f32)e[1];
    }
    fp = (u8 *)(s32)(*(s32 *)(arg2 + 0x3C) + (arg3 << 6));
    t = arg1 + arg3 * 4;
    s0 = t + 0x6C;

    for (;;) {
        f1 = *(f32 *)(t + 0x5C);
        if (!(f1 <= 0.0f)) {
            break;
        }
        s4 = 0;
        if (0.0f < f20) {
            for (;;) {
                v0 = arg0[1];
                if (v0 == 0) {
                    s4 = func_001A2350((s32)(arg0 + 4), *(s32 *)(arg2 + 0x3C),
                                       (s32)arg1, (s32)arg2);
                } else if (v0 == 1) {
                    s4 = func_001A2F10(*(f32 *)s0, (s32)e, (s32)fp, (s32)arg1,
                                       (s32)arg2, arg3);
                }
                if (s4 == 0) {
                    break;
                }
                *(s32 *)(arg1 + 0x58) = *(s32 *)(arg1 + 0x58) + 1;
                f0 = (f32)rand();
                f2 = *(f32 *)(e + 0xC);
                f1 = *(f32 *)(e + 0x8);
                f3 = *(f32 *)s0;
                f0 = f0 / D_00384E74;
                f2 = f2 * f0;
                f1 = f1 + f2;
                f0 = f3 + f1;
                if (D_00384E7C <= f0) {
                    f0 = f0 - D_00384E78;
                } else if (f0 <= D_00384E80) {
                    f0 = f0 + D_00384E78;
                }
                *(f32 *)s0 = f0;
                f20 = f20 - 1.0f;
                if (!(0.0f < f20)) {
                    break;
                }
            }
        }
        f0 = *(f32 *)(t + 0x5C) + *(f32 *)(e + 0x4);
        *(f32 *)(t + 0x5C) = f0;
        if (s4 == 0) {
            break;
        }
    }
}
