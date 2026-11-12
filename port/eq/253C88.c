#include "common.h"

void func_0024B010(s32 arg0, s32 arg1, void *arg2, void *arg3, s32 arg4);
s32 func_0024B210(void *arg0);
extern u8 *D_003879D0;
extern u8 *D_003876A4;

void func_00253C88(void) {
    u8 fr[0x40];
    s32 var_a2;
    s32 var_a3;
    s32 var_s0;
    s32 var_s0_2;
    s32 s1;
    s32 s2;
    s32 t1;
    s32 idx;
    s32 cmp;
    u8 *a1p;
    u8 *a1b;
    u8 *t0p;
    u8 *ptr;

    var_a2 = 0x204;
    var_a3 = 0;
    var_s0 = 0;
    do {
        a1p = D_003879D0 + var_a2;
        cmp = var_s0 < *(s32 *)(D_003879D0 + 0x26C);
        var_s0 += 1;
        if (cmp) {
            *(s32 *)a1p = *(s32 *)(*(u8 **)(D_003879D0 + 0x2A8) + var_a3 + 0xC);
            *(s32 *)(D_003879D0 + var_a2 + 0xC) = *(s32 *)(*(u8 **)(D_003879D0 + 0x2A8) + var_a3 + 0x10);
        } else {
            *(s32 *)a1p = -1;
            *(s32 *)(D_003879D0 + var_a2 + 0xC) = 0;
        }
        var_a2 += 0x14;
        var_a3 += 0x78;
    } while (var_s0 < 5);

    var_s0_2 = 0;
    s1 = 0x204;
    s2 = 0;
    *(s32 *)(D_003879D0 + 0x27C) = 0;
    do {
        idx = *(s32 *)(D_003879D0 + s1);
        if (idx >= 0) {
            a1b = *(u8 **)(D_003879D0 + 0x18);
            *(s32 *)(D_003879D0 + ((0x1A - var_s0_2) * 4) + 0x7C) =
                *(s32 *)(a1b + (((((u32)*(s32 *)(a1b + idx * 4 + 4)) >> 2) * 4)) + 0x10);
            t0p = fr + 0x20;
            t1 = 0;
            do {
                s32 m;
                s32 idx2;
                m = *(s32 *)(D_003876A4 + 0x38);
                idx2 = m * 7 + t1;
                t1 += 1;
                ptr = *(u8 **)(D_003879D0 + 0x2A8) + s2 + idx2 * 4 + 0x20;
                if (*(s32 *)ptr < 0) {
                    *(u16 *)t0p = 0;
                } else {
                    *(u16 *)t0p = (u16)(*(u16 *)ptr + 1);
                }
                t0p += 4;
            } while (t1 < 7);
            func_0024B010(*(s32 *)(D_003879D0 + 0x288), *(s32 *)(D_003879D0 + 0x28C), fr + 0x20, fr, 0x7D);
            *(s32 *)(D_003879D0 + s1 + 4) = func_0024B210(fr);
            *(s32 *)(D_003879D0 + 0x27C) = *(s32 *)(D_003879D0 + 0x27C) + *(s32 *)(D_003879D0 + s1 + 4);
        }
        var_s0_2 += 1;
        s1 += 0x14;
        s2 += 0x78;
    } while (var_s0_2 < 5);
}
