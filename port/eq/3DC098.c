#include "common.h"

extern u8 *D_004263EC __attribute__((section(".data")));
extern s32 D_003B0C34 __attribute__((section(".data")));

void func_297FE0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
void func_2493C0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);

/* 0x003DC098: step of the menu timer on G = D_004263EC, dispatched on v = G->0x78 - 1 through jtbl_00427240 (59
 * entries). v == 0: G->0x60 |= 4, G->0x68 = 5, then tail T. v == 50: the same with G->0x68 = 0xA. Even v in 2..6 and
 * 52..56: G->0x68++, then T. Odd v in 1..7 and 51..57: when D_003B0C34 & 0x4000, G->0x78++ and func_297FE0(0,1,0x40,
 * 0x40,1). v == 8: G->0x60 &= ~4, G->0x68 = G->0x64 + 1, func_2493C0 with that, G->0x78 = 0. v == 58: as 8 with
 * G->0x78 = 0 and G->0x6C = 3. T: G->0x78++, func_2493C0(G->0xC, 0x36B2, 0x3ACB, 0, G->0x68). Others: nothing. */
void func_003DC098(void) {
    s32 v;
    s32 tail;

    if (*(s32 *)(D_004263EC + 0x78) == 0) {
        return;
    }
    v = *(s32 *)(D_004263EC + 0x78) - 1;
    if ((u32)v >= 0x3B) {
        return;
    }
    tail = 0;
    if (v == 0 || v == 50) {
        *(s32 *)(D_004263EC + 0x60) = *(s32 *)(D_004263EC + 0x60) | 4;
        *(s32 *)(D_004263EC + 0x68) = (v == 0) ? 5 : 0xA;
        tail = 1;
    } else if (v == 8 || v == 58) {
        *(s32 *)(D_004263EC + 0x60) = *(s32 *)(D_004263EC + 0x60) & -5;
        *(s32 *)(D_004263EC + 0x68) = *(s32 *)(D_004263EC + 0x64) + 1;
        func_2493C0(*(s32 *)(D_004263EC + 0xC), 0x36B2, 0x3ACB, 0, *(s32 *)(D_004263EC + 0x68));
        *(s32 *)(D_004263EC + 0x78) = 0;
        if (v == 58) {
            *(s32 *)(D_004263EC + 0x6C) = 3;
        }
        return;
    } else if (((v >= 1 && v <= 7) || (v >= 51 && v <= 57)) && (v & 1)) {
        if (D_003B0C34 & 0x4000) {
            *(s32 *)(D_004263EC + 0x78) = *(s32 *)(D_004263EC + 0x78) + 1;
            func_297FE0(0, 1, 0x40, 0x40, 1);
        }
        return;
    } else if (((v >= 2 && v <= 6) || (v >= 52 && v <= 56)) && !(v & 1)) {
        *(s32 *)(D_004263EC + 0x68) = *(s32 *)(D_004263EC + 0x68) + 1;
        tail = 1;
    } else {
        return;
    }
    if (tail) {
        *(s32 *)(D_004263EC + 0x78) = *(s32 *)(D_004263EC + 0x78) + 1;
        func_2493C0(*(s32 *)(D_004263EC + 0xC), 0x36B2, 0x3ACB, 0, *(s32 *)(D_004263EC + 0x68));
    }
}
