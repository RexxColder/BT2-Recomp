#include "common.h"

void *memcpy(void *arg0, const void *arg1, u32 arg2);
s32 func_002C2DD0(void *arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002C2DE0(void *arg0);
s32 func_002C30A0(s32 arg0, void *arg1, s32 arg2);
s32 func_002B6700(s32 arg0);
void func_002B6818(s32 arg0, s32 arg1);
void Rand_Range(void *arg0);
extern u8 D_003787E8[] __attribute__((section(".data")));
extern u8 D_003787F0[] __attribute__((section(".data")));
extern u8 D_00378720[] __attribute__((section(".data")));

/* 0x002B6750(x, _, a2, a3) (GUESS arity: a2 and a3 are passed through to func_002C2DD0): buf = { word 0 of
 * D_00378720, x }. When func_002C2DD0(D_003787E8, 0x37B0, a2, a3) == 1: when func_002C2DE0(buf) is nonzero,
 * func_002B6700(-0x12D); else when func_002C30A0(0, func_002B6818, 0) is nonzero, func_002B6700(-0x12F).
 * Otherwise Rand_Range(&D_003787F0) and return -1. func_002B6700 returns its argument, so the error paths return
 * -0x12D / -0x12F; when func_002C30A0 is zero the result is its 0. */
s32 func_002B6750(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 buf[2];
    s32 r;

    (void)arg1;
    memcpy(buf, D_00378720, 8);
    buf[1] = arg0;
    r = func_002C2DD0(D_003787E8, 0x37B0, arg2, arg3);
    if (r == 1) {
        if (func_002C2DE0(buf) != 0) {
            return func_002B6700(-0x12D);
        }
        if (func_002C30A0(0, (void *)func_002B6818, 0) != 0) {
            return func_002B6700(-0x12F);
        }
        return 0;
    }
    Rand_Range(D_003787F0);
    return -1;
}
