#include "common.h"

extern u8 *D_00427334 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));
extern u8 D_003B0B00[] __attribute__((section(".data")));
extern u8 D_004278C0[] __attribute__((section(".data")));
extern u8 D_004278D0[] __attribute__((section(".data")));
extern u8 D_004278E0[] __attribute__((section(".data")));

s32 func_26EB60(u8 *p);
void func_26EB78(u8 *p, u8 *q);
void func_003E0640(void);
void func_243A80(s32 a0, s32 a1, s32 a2);
void func_297FE0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);

/* 0x003E07A8: input step on G = D_00427334, gated by func_26EB60(G+0x38) and the input block IN = D_003B0B00. Bit
 * 0x10 of IN->0x144 steps G->0x9C down (wrapping to 2) then func_003E0640 and func_297FE0(0,0,..). Bit 0x40 steps it up
 * (wrapping to 0 at 3). Else bit 0x4000 of IN->0x134 arms G->0x98 bits 1 and 2 and G->0xA4 = 0xF, and on G->0x9C == 1 /
 * 0 / 2 calls func_26EB78(G+0x38, D_004278D0 / D_004278C0 / D_004278E0) and sets P->0x1C = 0x2D / 0x2C / 0x2E; other
 * values only call func_297FE0(0,1,..). Else bit 0x1000 zeroes *arg0 and func_297FE0(0,2,..) after func_243A80. */
void func_003E07A8(s32 *arg0) {
    u8 *g;
    s32 in144;
    s32 in134;
    s32 v;

    g = D_00427334;
    if (func_26EB60(g + 0x38) == 0) {
        return;
    }
    in144 = *(s32 *)(D_003B0B00 + 0x144);
    if (in144 & 0x10) {
        *(s32 *)(g + 0x9C) = *(s32 *)(g + 0x9C) - 1;
        if (*(s32 *)(g + 0x9C) < 0) {
            *(s32 *)(g + 0x9C) = 2;
        }
        func_003E0640();
        func_297FE0(0, 0, 0x40, 0x40, 1);
        return;
    }
    if (in144 & 0x40) {
        *(s32 *)(g + 0x9C) = *(s32 *)(g + 0x9C) + 1;
        if (*(s32 *)(g + 0x9C) >= 3) {
            *(s32 *)(g + 0x9C) = 0;
        }
        func_003E0640();
        func_297FE0(0, 0, 0x40, 0x40, 1);
        return;
    }
    in134 = *(s32 *)(D_003B0B00 + 0x134);
    if (in134 & 0x4000) {
        *(s32 *)(g + 0x98) = *(s32 *)(g + 0x98) | 1;
        *(s32 *)(g + 0x98) = *(s32 *)(g + 0x98) | 2;
        *(s32 *)(g + 0xA4) = 0xF;
        v = *(s32 *)(g + 0x9C);
        if (v == 1) {
            func_26EB78(g + 0x38, D_004278D0);
            *(s32 *)(D_3876A4 + 0x1C) = 0x2D;
            func_297FE0(0, 1, 0x40, 0x40, 1);
        } else if (v == 0) {
            func_26EB78(g + 0x38, D_004278C0);
            *(s32 *)(D_3876A4 + 0x1C) = 0x2C;
            func_297FE0(0, 1, 0x40, 0x40, 1);
        } else if (v == 2) {
            func_26EB78(g + 0x38, D_004278E0);
            *(s32 *)(D_3876A4 + 0x1C) = 0x2E;
            func_297FE0(0, 1, 0x40, 0x40, 1);
        } else {
            func_297FE0(0, 1, 0x40, 0x40, 1);
        }
        return;
    }
    if (in134 & 0x1000) {
        func_243A80(0, 0, 0);
        *arg0 = 0;
        func_297FE0(0, 2, 0x40, 0x40, 1);
    }
}
