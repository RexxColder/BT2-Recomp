#include "common.h"

/* GUESS arity: the asm sets a0..a3 only (t0 is never written) */
s32 func_002CF1C8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002B6700(s32 arg0);
s32 Rand_Range(s32 arg0);
extern u8 D_00377E18[] __attribute__((section(".data")));

void func_002B3190(s32 arg0) {
    u8 *base;
    s32 sp[6];
    s32 a2;
    s32 a3;

    base = (u8 *)arg0;
    a2 = *(s32 *)(base + 0x1BC);
    a3 = *(s32 *)(base + 0x3C);
    if (a2 != 0) {
        if (a2 == *(s32 *)(base + 0x1E0)) {
            sp[0] = 1;
            sp[1] = a2;
            sp[2] = *(s32 *)(base + 0x1E4);
            sp[3] = *(s32 *)(base + 0x1E8);
            sp[4] = 0;
        } else if (a2 == *(s32 *)(base + 0x1C0)) {
            sp[0] = 0;
            sp[1] = a2;
            sp[2] = *(s32 *)(base + 0x1C4);
            sp[3] = *(s32 *)(base + 0x1C8);
            sp[4] = *(s32 *)(base + 0x1CC);
        } else {
            sp[0] = *(s32 *)(base + 0x1D0);
            sp[1] = a2;
            sp[2] = *(s32 *)(base + 0x1D4);
            sp[3] = *(s32 *)(base + 0x1D8);
            sp[4] = *(s32 *)(base + 0x1DC);
        }
        sp[5] = 0;
        if (func_002CF1C8(a3, (s32)sp, a2, a3) != 0) {
            func_002B6700(-0x138);
            Rand_Range((s32)D_00377E18);
        }
    }
}
