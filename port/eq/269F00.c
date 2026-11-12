#include "common.h"

#define GS_END 0x70000000u
#define GS_AD 0x6C058000u

/* 0x00269F00: rebases a GS packet chain. flag != 0 walks the words linearly
 * (end tag 0x70000000); flag == 0 walks the chain links (word at +0 is the
 * relative offset to the next tag, lhu +6 / +8 are counts). */
void func_00269F00(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7) {
    u8 *t4;
    u8 *t5;
    u8 *t6;
    u32 mx;
    u32 my;
    u32 v0;
    u32 w14;
    u32 w18;
    u32 w24;
    u32 w28;
    u32 x;
    u32 y;

    t4 = (u8 *)a1;
    mx = a6;
    my = a7;

    if ((a0 & 0xFF) != 0) {
        /* pass 1: running minimum over every A+D entry */
        t5 = t4;
        if (*(u32 *)t5 == GS_END) {
            return;
        }
        while (*(u32 *)t5 != GS_END) {
            if (*(u32 *)t5 == GS_AD) {
                x = *(u32 *)(t5 + 0x14) & 0x3FFF;
                y = (*(u32 *)(t5 + 0x18) >> 5) & 0x3FFF;
                if (x < mx) {
                    mx = x;
                }
                if (y < my) {
                    my = y;
                }
            }
            t5 += 4;
        }
        /* pass 2: rebase every A+D entry */
        if (*(u32 *)t4 == GS_END) {
            return;
        }
        t5 = t4;
        while (*(u32 *)t5 != GS_END) {
            if (*(u32 *)t5 == GS_AD) {
                w14 = *(u32 *)(t5 + 0x14);
                w18 = *(u32 *)(t5 + 0x18);
                w24 = *(u32 *)(t5 + 0x24);
                w28 = *(u32 *)(t5 + 0x28);
                *(u32 *)(t5 + 0x14) = (w14 & 0xFFFFC000u) | (((w14 & 0x3FFF) - mx + a2));
                *(u32 *)(t5 + 0x18) = (w18 & 0xFFF8001Fu) | (((((w18 >> 5) & 0x3FFF) - my + a3)) << 5);
                *(u32 *)(t5 + 0x24) = (w24 & 0xFFFFC000u) | (u32)a4;
                *(u32 *)(t5 + 0x28) = (w28 & 0xFFF8001Fu) | ((((w28 >> 5) & 0x3FFF) + (u32)a5) << 5);
            }
            t5 += 4;
        }
        return;
    }

    /* flag == 0: walk the chain links, pass 1 (minimum) */
    t6 = t4;
    for (;;) {
        v0 = *(u16 *)(t6 + 8);
        if (v0 != 0) {
            t5 = t6 + 0x60;
            if (*(u32 *)t5 != GS_END) {
                while (*(u32 *)t5 != GS_END) {
                    if (*(u32 *)t5 == GS_AD) {
                        x = *(u32 *)(t5 + 0x14) & 0x3FFF;
                        y = (*(u32 *)(t5 + 0x18) >> 5) & 0x3FFF;
                        if (x < mx) {
                            mx = x;
                        }
                        if (y < my) {
                            my = y;
                        }
                    }
                    t5 += 4;
                }
            }
        }
        v0 = *(u16 *)(t6 + 6);
        if (v0 != 0) {
            t6 = t4;
            break;
        }
        t6 = t6 + *(s32 *)t6;
    }

    /* flag == 0: pass 2 (rebase) */
    for (;;) {
        v0 = *(u16 *)(t6 + 8);
        if (v0 != 0) {
            t5 = t6 + 0x60;
            if (*(u32 *)t5 != GS_END) {
                while (*(u32 *)t5 != GS_END) {
                    if (*(u32 *)t5 == GS_AD) {
                        w14 = *(u32 *)(t5 + 0x14);
                        w18 = *(u32 *)(t5 + 0x18);
                        w24 = *(u32 *)(t5 + 0x24);
                        w28 = *(u32 *)(t5 + 0x28);
                        *(u32 *)(t5 + 0x14) = (w14 & 0xFFFFC000u) | (((w14 & 0x3FFF) - mx + a2));
                        *(u32 *)(t5 + 0x18) = (w18 & 0xFFF8001Fu) | (((((w18 >> 5) & 0x3FFF) - my + a3)) << 5);
                        *(u32 *)(t5 + 0x24) = (w24 & 0xFFFFC000u) | (u32)a4;
                        *(u32 *)(t5 + 0x28) = (w28 & 0xFFF8001Fu) | ((((w28 >> 5) & 0x3FFF) + (u32)a5) << 5);
                    }
                    t5 += 4;
                }
            }
        }
        v0 = *(u16 *)(t6 + 6);
        if (v0 != 0) {
            return;
        }
        t6 = t6 + *(s32 *)t6;
    }
}
