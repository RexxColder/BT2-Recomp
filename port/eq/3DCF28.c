#include "common.h"

extern u8 *D_0042732C __attribute__((section(".data")));

void func_100ED0(s32 arg0, u8 *arg1, s32 arg2);
s32 func_100FC8(s32 arg0);
void func_2B24C8(u8 *arg0, u8 *arg1, s32 arg2);
void Res_RelocateOffsets(u8 *arg0, u8 *arg1, u8 *arg2);

/* 0x003DCF28 (G = D_0042732C): state G->0x74C, index = state - 1 (unsigned < 6 or return):
 * 0 (state 1): p = G->0x114 advanced G->0x110 times along +8; func_100ED0(p->4 + 0x5EE, G->8, 1); func_100FC8(1); state 2.
 * 1 (state 2): if func_100FC8(0) != 0, state 3.
 * 2 (state 3): func_2B24C8(G->8, G->0xC, 0); sp[0] = G->0xC; Res_RelocateOffsets(sp, sp[0], sp[0]);
 *   G->0xE4 = *(sp[0]+0x10); G->0x108 |= 0x20; state 4.
 * 3 (state 4): if G->0x108 & 0x10, state 6.
 * 4 (state 5): state 6.
 * 5 (state 6): if G->0x108 & 0x10, G->0x108 ^= 0x10; state 1. */
void func_003DCF28(void) {
    u8 *sp[2];
    s32 idx;
    s32 k;
    s32 n;
    u8 *p;

    idx = *(s32 *)(D_0042732C + 0x74C) - 1;
    if ((u32)idx >= 6) {
        return;
    }
    switch (idx) {
    case 0:
        n = *(s32 *)(D_0042732C + 0x110);
        p = *(u8 **)(D_0042732C + 0x114);
        for (k = 0; k < n; k++) {
            p = *(u8 **)(p + 8);
        }
        func_100ED0(*(s32 *)(p + 4) + 0x5EE, *(u8 **)(D_0042732C + 8), 1);
        func_100FC8(1);
        *(s32 *)(D_0042732C + 0x74C) = 2;
        break;
    case 1:
        if (func_100FC8(0) != 0) {
            *(s32 *)(D_0042732C + 0x74C) = 3;
        }
        break;
    case 2:
        func_2B24C8(*(u8 **)(D_0042732C + 8), *(u8 **)(D_0042732C + 0xC), 0);
        sp[0] = *(u8 **)(D_0042732C + 0xC);
        Res_RelocateOffsets((u8 *)sp, sp[0], sp[0]);
        *(s32 *)(D_0042732C + 0xE4) = *(s32 *)(sp[0] + 0x10);
        *(s32 *)(D_0042732C + 0x108) = *(s32 *)(D_0042732C + 0x108) | 0x20;
        *(s32 *)(D_0042732C + 0x74C) = 4;
        break;
    case 3:
        if (*(s32 *)(D_0042732C + 0x108) & 0x10) {
            *(s32 *)(D_0042732C + 0x74C) = 6;
        }
        break;
    case 4:
        *(s32 *)(D_0042732C + 0x74C) = 6;
        break;
    case 5:
        if (*(s32 *)(D_0042732C + 0x108) & 0x10) {
            *(s32 *)(D_0042732C + 0x108) = *(s32 *)(D_0042732C + 0x108) ^ 0x10;
        }
        *(s32 *)(D_0042732C + 0x74C) = 1;
        break;
    }
}
