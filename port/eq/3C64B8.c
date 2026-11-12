#include "common.h"

extern u8 *D_00423114 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));

void func_248708(u8 *a0, u8 *a1, u8 *a2, u8 *a3);
void func_003C6408(s32 a0, u8 *a1, u8 *a2, s32 a3);

/* 0x003C64B8: sets up the record G = D_00423114 from the list at Q = G->4: G->0x1CC = Q + (Q->0x2C & ~3) + 4,
 * G->0x1C8 = *(Q + (Q->0x2C & ~3)), func_248708 on the 0x1D4/0x1D8/0x1C8/0x1CC block, then G->0x1C8 = G->0x1D4 and
 * the 7-way split of G->0x1C8 (quotient to G->0x3628, +1 on a remainder). Zeroes four fields of P = D_3876A4 and copies
 * the P->0x390 mod/div by 7 and P->0x3B8 / P->0x430 into G. Tail: func_003C6408(0, G, G, 7). The asm's break 0,7
 * divide-by-zero traps are not written. */
void func_003C64B8(void) {
    u8 *q;
    s32 idx;

    q = *(u8 **)(D_00423114 + 0x4);
    idx = (s32)((((u32)*(s32 *)(q + 0x2C)) >> 2) << 2);
    *(u8 **)(D_00423114 + 0x1CC) = q + idx + 4;
    *(s32 *)(D_00423114 + 0x1C8) = *(s32 *)(q + idx);

    func_248708(D_00423114 + 0x1D4, D_00423114 + 0x1D8, D_00423114 + 0x1C8, D_00423114 + 0x1CC);

    *(s32 *)(D_00423114 + 0x1C8) = *(s32 *)(D_00423114 + 0x1D4);
    *(u8 **)(D_00423114 + 0x1CC) = D_00423114 + 0x1D8;
    *(u8 **)(D_00423114 + 0x1D0) = D_00423114 + 0x19E8;

    *(s32 *)(D_00423114 + 0x3628) = *(s32 *)(D_00423114 + 0x1C8) / 7;
    if (*(s32 *)(D_00423114 + 0x1C8) % 7 != 0) {
        *(s32 *)(D_00423114 + 0x3628) = *(s32 *)(D_00423114 + 0x3628) + 1;
    }
    *(s32 *)(D_00423114 + 0x18C) = *(s32 *)(D_00423114 + 0x18C) & ~0x40;
    *(s32 *)(D_00423114 + 0x362C) = 1;
    *(s32 *)(D_00423114 + 0x18C) = *(s32 *)(D_00423114 + 0x18C) | 0x20000000;

    *(s32 *)(D_3876A4 + 0x390) = 0;
    *(s32 *)(D_3876A4 + 0x3B8) = 0;
    *(s32 *)(D_3876A4 + 0x408) = 0;
    *(s32 *)(D_3876A4 + 0x430) = 0;

    *(s32 *)(D_00423114 + 0x190) = *(s32 *)(D_3876A4 + 0x390) % 7;
    *(s32 *)(D_00423114 + 0x198) = *(s32 *)(D_3876A4 + 0x390) / 7;
    *(s32 *)(D_00423114 + 0x1A8) = *(s32 *)(D_3876A4 + 0x3B8);
    *(s32 *)(D_00423114 + 0x1B0) = *(s32 *)(D_3876A4 + 0x430);
    *(s32 *)(D_00423114 + 0x1B8) = *(s32 *)(D_3876A4 + 0x430);

    func_003C6408(0, D_00423114, D_00423114, 7);
}
