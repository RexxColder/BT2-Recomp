#include "common.h"

extern u8 *D_0042FD74 __attribute__((section(".data")));

void func_100ED0(s32 arg0, u8 *arg1, s32 arg2);
s32 func_100FC8(s32 arg0);
void func_2B24C8(u8 *arg0, u8 *arg1, s32 arg2);
void Res_RelocateOffsets(u8 *arg0, u8 *arg1, u8 *arg2);

/* 0x0041CD90 (todo sobre D_0042FD74: el asm usa s0 = %hi(D_0042FD74) y luego s0 - 0x28C = &D_0042FD74; el m2c lo
 * habia leido como D_0042FAE8, que no existe en el original). state = D_0042FD74->0x140; index = state - 1 (unsigned < 6 or return). Writes go to D_0042FD74 except
 * case 4. Case 0: func_100ED0(*(g2+8+(g2->0x1AC)*4+0x140) + 0x671, *(g2+8), 1), func_100FC8(1), state 2.
 * Case 1: if func_100FC8(0) != 0, state 3. Case 2: func_2B24C8(g2->8, g2->0xC, 0); sp[0] = g2->0xC;
 * Res_RelocateOffsets(sp, sp[0], sp[0]); g2->0xFC = *(sp[0]+0x10); g2->0x134 |= 8; state 4.
 * Case 3: if g2->0x134 & 4, state 6. Case 4: D_0042FD74->0x140 = 6. Case 5: if g2->0x134 & 4, g2->0x134 ^= 4; state 1. */
void func_0041CD90(void) {
    u8 *spw[2];
    s32 idx;
    s32 k;
    s32 v;

    idx = *(s32 *)(D_0042FD74 + 0x140) - 1;
    if ((u32)idx >= 6) {
        return;
    }
    switch (idx) {
    case 0:
        k = *(s32 *)(D_0042FD74 + 0x1AC);
        v = *(s32 *)(D_0042FD74 + 8 + k * 4 + 0x140);
        func_100ED0(v + 0x671, *(u8 **)(D_0042FD74 + 8), 1);
        func_100FC8(1);
        *(s32 *)(D_0042FD74 + 0x140) = 2;
        break;
    case 1:
        if (func_100FC8(0) != 0) {
            *(s32 *)(D_0042FD74 + 0x140) = 3;
        }
        break;
    case 2:
        func_2B24C8(*(u8 **)(D_0042FD74 + 8), *(u8 **)(D_0042FD74 + 0xC), 0);
        spw[0] = *(u8 **)(D_0042FD74 + 0xC);
        Res_RelocateOffsets((u8 *)spw, spw[0], spw[0]);
        *(s32 *)(D_0042FD74 + 0xFC) = *(s32 *)(spw[0] + 0x10);
        *(s32 *)(D_0042FD74 + 0x134) = *(s32 *)(D_0042FD74 + 0x134) | 0x8;
        *(s32 *)(D_0042FD74 + 0x140) = 4;
        break;
    case 3:
        if (*(s32 *)(D_0042FD74 + 0x134) & 0x4) {
            *(s32 *)(D_0042FD74 + 0x140) = 6;
        }
        break;
    case 4:
        *(s32 *)(D_0042FD74 + 0x140) = 6;
        break;
    case 5:
        if (*(s32 *)(D_0042FD74 + 0x134) & 0x4) {
            *(s32 *)(D_0042FD74 + 0x134) = *(s32 *)(D_0042FD74 + 0x134) ^ 0x4;
        }
        *(s32 *)(D_0042FD74 + 0x140) = 1;
        break;
    }
}
