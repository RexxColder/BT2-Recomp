#include "common.h"

extern u8 *D_004263E8 __attribute__((section(".data")));

s32 func_26EB70(u8 *arg0);
void func_26E9E8(u8 *arg0);
void func_2493C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_2510E0(void);

/* 0x003D8F48: G = D_004263E8. if (func_26EB70(G+0x1C) & 8): if (G->0x154 & 8) { v = G->0x6E38 != 0x12 ? 0x15 : 0x13;
 * G->0x6E38 = v; func_2493C0(G->0xC, 0x36B2, 0x3ACB, 0, G->0x6E38) } else { G->0x6E38 = 0x10; the same call }.
 * if (func_26EB70(G+0x1C) & 0x200) { G->0x6E38 = -1; G->0x154 &= ~0x80 }. if (func_26EB70(G+0x1C) & 0x10)
 * func_297FE0(2, 1, 0x40, 0x40, 1). Then func_26E9E8(G+0x1C) and func_26E9E8(G+0x28+0x1C). Tail call func_2510E0(). */
void func_003D8F48(void) {
    s32 v;
    s32 i;

    if (func_26EB70(D_004263E8 + 0x1C) & 0x8) {
        if (*(s32 *)(D_004263E8 + 0x154) & 0x8) {
            if (*(s32 *)(D_004263E8 + 0x6E38) != 0x12) {
                v = 0x15;
            } else {
                v = 0x13;
            }
            *(s32 *)(D_004263E8 + 0x6E38) = v;
            func_2493C0(*(s32 *)(D_004263E8 + 0xC), 0x36B2, 0x3ACB, 0, *(s32 *)(D_004263E8 + 0x6E38));
        } else {
            *(s32 *)(D_004263E8 + 0x6E38) = 0x10;
            func_2493C0(*(s32 *)(D_004263E8 + 0xC), 0x36B2, 0x3ACB, 0, *(s32 *)(D_004263E8 + 0x6E38));
        }
    }

    if (func_26EB70(D_004263E8 + 0x1C) & 0x200) {
        *(s32 *)(D_004263E8 + 0x6E38) = -1;
        *(s32 *)(D_004263E8 + 0x154) = *(s32 *)(D_004263E8 + 0x154) & ~0x80;
    }

    if (func_26EB70(D_004263E8 + 0x1C) & 0x10) {
        func_297FE0(2, 1, 0x40, 0x40, 1);
    }

    for (i = 0; i < 2; i++) {
        func_26E9E8(D_004263E8 + i * 0x28 + 0x1C);
    }
    func_2510E0();
}
