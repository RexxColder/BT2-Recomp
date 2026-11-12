#include "common.h"

s32 func_001C96C0(f32 farg0, u8 *arg1, u8 *arg2, u8 *arg3, u8 *arg4, s32 arg5);
s32 rand();
extern f32 D_003851B4;
extern f32 D_003851B8;
extern f32 D_003851BC;
extern f32 D_003851C0;

void func_001CA258(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3) {
    u8 *s0;
    u8 *s3;
    u8 *s6;
    u8 *v0p;
    s32 v1;
    s32 r;
    s32 rnd;
    f32 f0;
    f32 f20;

    f20 = (f32)*(u8 *)(arg2 + 4);
    if (*(u8 *)(arg2 + 5) != 0) {
        f20 = (f32)*(u8 *)(arg2 + 5);
    }
    s6 = *(u8 **)(arg1 + 0x3C) + (arg3 << 6);
    v0p = arg0 + (arg3 << 2);
    s0 = v0p + 0x70;
    s3 = v0p + 0x5C;

    for (;;) {
        if (*(f32 *)s3 > 0.0f) {
            break;
        }
        v1 = 0;
        if (0.0f < f20) {
            do {
                r = func_001C96C0(*(f32 *)s0, arg2, s6, arg0, arg1, arg3);
                v1 = 0;
                if (r == 0) {
                    break;
                }
                *(s32 *)(arg0 + 0x58) = *(s32 *)(arg0 + 0x58) + 1;
                rnd = rand();
                v1 = 1;
                f0 = *(f32 *)s0 + (*(f32 *)(arg2 + 0xC) + *(f32 *)(arg2 + 0x10) * ((f32)rnd / D_003851B4));
                *(f32 *)s0 = f0;
                if (D_003851B8 <= f0) {
                    f0 = f0 - D_003851BC;
                    *(f32 *)s0 = f0;
                } else if (f0 <= D_003851C0) {
                    f0 = f0 + D_003851BC;
                    *(f32 *)s0 = f0;
                }
                f20 = f20 - 1.0f;
            } while (0.0f < f20);
        }
        f0 = *(f32 *)s3 + *(f32 *)(arg2 + 0x8);
        *(f32 *)s3 = f0;
        if (v1 == 0) {
            break;
        }
    }
}
