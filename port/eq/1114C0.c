#include "common.h"

extern u8 D_0036C8B0[] __attribute__((section(".data")));
extern u16 D_0036C8D0[] __attribute__((section(".data")));

s32 func_001114C0(u8 *arg0, u32 arg1, s32 arg2) {
    s32 spw[8];
    u32 rem;
    s32 t2;
    s32 t5;
    s32 t6;
    s32 t7;
    u8 *t0;
    u32 q;
    s32 w;

    memcpy(spw, D_0036C8B0, 0x20);
    rem = arg1;
    t2 = arg2;
    t5 = 0;
    t6 = 0;
    t7 = 0;
    t0 = arg0;

    if (t2 <= 0) {
        return t7;
    }
    while (t2 > 0) {
        w = spw[t2 - 1];
        q = (w != 0) ? rem / (u32)w : 0;

        if (q == 0 && t5 != 0) {
            *(u16 *)(t0 + 0xC) = D_0036C8D0[0];
            *(u16 *)(t0 + 0x10) = D_0036C8D0[2];
            *(u16 *)(t0 + 0xE) = D_0036C8D0[1];
            *(u16 *)(t0 + 0x12) = D_0036C8D0[3];
        } else if (q == 0 && t2 == 1 && arg1 == 0) {
            *(u16 *)(t0 + 0xC) = D_0036C8D0[0];
            *(u16 *)(t0 + 0x10) = D_0036C8D0[2];
            *(u16 *)(t0 + 0xE) = D_0036C8D0[1];
            *(u16 *)(t0 + 0x12) = D_0036C8D0[3];
            if (t5 == 0) {
                t7 = t6;
            }
        } else if (q == 0) {
            *(u16 *)(t0 + 0xC) = D_0036C8D0[0x64 / 2];
            *(u16 *)(t0 + 0x10) = D_0036C8D0[0x68 / 2];
            *(u16 *)(t0 + 0xE) = D_0036C8D0[0x66 / 2];
            *(u16 *)(t0 + 0x12) = D_0036C8D0[0x6A / 2];
        } else {
            if (t5 == 0) {
                t7 = t6;
            }
            rem = rem - (u32)((s32)q * w);
            t5 = 1;
            *(u16 *)(t0 + 0xC) = D_0036C8D0[5 * q];
            *(u16 *)(t0 + 0x10) = D_0036C8D0[5 * q + 2];
            *(u16 *)(t0 + 0xE) = D_0036C8D0[5 * q + 1];
            *(u16 *)(t0 + 0x12) = D_0036C8D0[5 * q + 3];
        }

        *(u16 *)(t0 + 0x14) = 1;
        t2 = t2 - 1;
        t6 = t6 + 1;
        t0 = t0 + 0x60;
    }
    return t7;
}
