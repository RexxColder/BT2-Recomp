#include "common.h"

extern u8 D_003B0F7C[] __attribute__((section(".data")));

/* 0x002A3DD8: record i (104 bytes at D_003B0F7C): +0 = 1, +1 = a1, +2 = a2, +3 = t1, +4 = a3, +5 = t0, +6 = t3,
 * +7 = 9th argument (stack), +8 = t2 as a word. */
void func_002A3DD8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8) {
    u8 *p = D_003B0F7C + arg0 * 104;

    p[7] = (u8)arg8;
    p[0] = 1;
    p[1] = (u8)arg1;
    p[2] = (u8)arg2;
    p[4] = (u8)arg3;
    p[5] = (u8)arg4;
    p[3] = (u8)arg5;
    *(s32 *)(p + 8) = arg6;
    p[6] = (u8)arg7;
}
