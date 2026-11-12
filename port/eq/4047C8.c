#include "common.h"

extern u8 *D_0042BB70 __attribute__((section(".data")));

void func_2493C0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);

/* 0x004047C8: per-frame update of G = D_0042BB70. G->0x114 = G->0x110 + 8, bumped by 1 while below 10; then
 * func_2493C0(G->8, 0x36A3, 0x3ABC, 0, G->0x114). Dispatch on G->0x110 (0..4, else return): sets G->0x120 and G->0x118
 * (0: 5/0, 1: 5/1 then G->0xE4 and G->0xE8, 2: 2/4, 3: 6/5 then G->0xE4 and G->0xE8 from G->0xA0, 4: 2/2), then
 * G->0x11C = G->(0x168 + 4 * G->0x118). The G->0xE8 values are *(G->0x94 or G->0xA0 + 0x10) + 0x40. */
void func_004047C8(void) {
    s32 idx;

    *(s32 *)(D_0042BB70 + 0x114) = *(s32 *)(D_0042BB70 + 0x110) + 8;
    if (*(s32 *)(D_0042BB70 + 0x114) < 10) {
        *(s32 *)(D_0042BB70 + 0x114) = *(s32 *)(D_0042BB70 + 0x114) + 1;
    }
    func_2493C0(*(s32 *)(D_0042BB70 + 0x8), 0x36A3, 0x3ABC, 0, *(s32 *)(D_0042BB70 + 0x114));

    idx = *(s32 *)(D_0042BB70 + 0x110);
    if ((u32)idx >= 5) {
        return;
    }
    switch (idx) {
    case 0:
        *(s32 *)(D_0042BB70 + 0x120) = 5;
        *(s32 *)(D_0042BB70 + 0x118) = 0;
        *(s32 *)(D_0042BB70 + 0x11C) = *(s32 *)(D_0042BB70 + ((*(s32 *)(D_0042BB70 + 0x118)) << 2) + 0x168);
        break;
    case 1:
        *(s32 *)(D_0042BB70 + 0x120) = 5;
        *(s32 *)(D_0042BB70 + 0x118) = 1;
        *(s32 *)(D_0042BB70 + 0x11C) = *(s32 *)(D_0042BB70 + ((*(s32 *)(D_0042BB70 + 0x118)) << 2) + 0x168);
        *(s32 *)(D_0042BB70 + 0xE4) = *(s32 *)(*(u8 **)(D_0042BB70 + 0x94) + 0x10);
        *(s32 *)(D_0042BB70 + 0xE8) = *(s32 *)(*(u8 **)(D_0042BB70 + 0x94) + 0x10) + 0x40;
        break;
    case 2:
        *(s32 *)(D_0042BB70 + 0x120) = 2;
        *(s32 *)(D_0042BB70 + 0x118) = 4;
        *(s32 *)(D_0042BB70 + 0x11C) = *(s32 *)(D_0042BB70 + ((*(s32 *)(D_0042BB70 + 0x118)) << 2) + 0x168);
        break;
    case 3:
        *(s32 *)(D_0042BB70 + 0x120) = 6;
        *(s32 *)(D_0042BB70 + 0x118) = 5;
        *(s32 *)(D_0042BB70 + 0x11C) = *(s32 *)(D_0042BB70 + ((*(s32 *)(D_0042BB70 + 0x118)) << 2) + 0x168);
        *(s32 *)(D_0042BB70 + 0xE4) = *(s32 *)(*(u8 **)(D_0042BB70 + 0xA0) + 0x10);
        *(s32 *)(D_0042BB70 + 0xE8) = *(s32 *)(*(u8 **)(D_0042BB70 + 0xA0) + 0x10) + 0x40;
        break;
    case 4:
        *(s32 *)(D_0042BB70 + 0x120) = 2;
        *(s32 *)(D_0042BB70 + 0x118) = 2;
        *(s32 *)(D_0042BB70 + 0x11C) = *(s32 *)(D_0042BB70 + ((*(s32 *)(D_0042BB70 + 0x118)) << 2) + 0x168);
        break;
    }
}
