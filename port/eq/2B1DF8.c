#include "common.h"

s32 func_00276B00(s32 arg0, s32 arg1, s32 arg2);
s32 func_00312650(s32 arg0, s32 arg1, s32 arg2);
f32 sqrtf(f32 arg0);
extern u8 D_003B26B0[] __attribute__((section(".data")));

/* 0x002B1DF8: over the 32 slots i of D_003B26B0 whose bit is set in word +0x20 and in word +0x14: when
 * func_00276B00(i, buf, buf+0x10) > 0, func_00312650(buf+0x20, buf, arg0+0xD0) and dist = sqrt(x*x + z*z) of that
 * vector; the slot with the smallest dist below 300.0f is returned (-1 when none). */
s32 func_002B1DF8(u8 *arg0) {
    u8 *g = D_003B26B0;
    u8 buf[0x30];
    f32 best = 300.0f;
    s32 bestIdx = -1;
    s32 i;

    for (i = 0; i < 32; i++) {
        u32 bit = 1u << i;
        f32 x;
        f32 z;
        f32 dist;

        if (!(*(u32 *)(g + 0x20) & bit)) {
            continue;
        }
        if (!(*(u32 *)(g + 0x14) & bit)) {
            continue;
        }
        if (func_00276B00(i, (s32)buf, (s32)(buf + 0x10)) <= 0) {
            continue;
        }
        func_00312650((s32)(buf + 0x20), (s32)buf, (s32)(arg0 + 0xD0));
        x = *(f32 *)(buf + 0x20);
        z = *(f32 *)(buf + 0x28);
        dist = sqrtf(x * x + z * z);
        if (dist < best) {
            best = dist;
            bestIdx = i;
        }
    }
    return bestIdx;
}
