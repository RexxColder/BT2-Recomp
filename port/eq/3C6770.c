#include "common.h"

extern u8 *D_00423114 __attribute__((section(".data")));

void func_100ED0(s32 a0, s32 a1, s32 a2);
s32 func_100FC8(s32 a0);
void func_2B24C8(u8 *a0, u8 *a1, s32 a2);
void Res_RelocateOffsets(u8 **a0, u8 *a1, u8 *a2);

/* 0x003C6770: state machine on G->0x362C (G = D_00423114), states 1..6 through jtbl_00423150; anything else returns.
 * 1: builds the record at G + 44 * idx (idx from G->0x188 and the 0x190 table) into G->0x1C0, func_100ED0(rec + 0x56B,
 *    G->8), func_100FC8(1), state 2.   2: func_100FC8(0) != 0 -> state 3.   3: func_2B24C8, Res_RelocateOffsets, G->0xC8,
 *    G->0x18C |= 0x40, state 4.   4: G->0x18C & 1 -> state 6.   5: state 6.   6: clear G->0x18C bit 0, state 1. */
void func_003C6770(void) {
    s32 st;
    s32 off;
    u8 *base;
    u8 *rec;
    u8 *v1p;
    u8 *slot[2];
    s32 a1v;
    s32 t0v;
    s32 idx;

    st = *(s32 *)(D_00423114 + 0x362C) - 1;
    if ((u32)st >= 6) {
        return;
    }
    switch (st) {
    case 0:
        off = *(s32 *)(D_00423114 + 0x188) << 2;
        base = D_00423114 + off;
        v1p = D_00423114 + off + 0x190;
        a1v = *(s32 *)(v1p + 8);
        t0v = *(s32 *)v1p;
        idx = a1v * 7 + t0v;
        rec = *(u8 **)(base + 0x1CC) + idx * 44;
        *(s32 *)(D_00423114 + 0x1C0) = *(s32 *)rec;
        func_100ED0(*(s32 *)rec + 0x56B, *(s32 *)(D_00423114 + 0x8), 1);
        func_100FC8(1);
        *(s32 *)(D_00423114 + 0x362C) = 2;
        break;
    case 1:
        if (func_100FC8(0) != 0) {
            *(s32 *)(D_00423114 + 0x362C) = 3;
        }
        break;
    case 2:
        func_2B24C8(*(u8 **)(D_00423114 + 0x8), *(u8 **)(D_00423114 + 0xC), 0);
        slot[0] = *(u8 **)(D_00423114 + 0xC);
        Res_RelocateOffsets(slot, *(u8 **)(D_00423114 + 0xC), *(u8 **)(D_00423114 + 0xC));
        *(s32 *)(D_00423114 + 0xC8) = *(s32 *)(slot[0] + 0x10);
        *(s32 *)(D_00423114 + 0x18C) = *(s32 *)(D_00423114 + 0x18C) | 0x40;
        *(s32 *)(D_00423114 + 0x362C) = 4;
        break;
    case 3:
        if (*(s32 *)(D_00423114 + 0x18C) & 1) {
            *(s32 *)(D_00423114 + 0x362C) = 6;
        }
        break;
    case 4:
        *(s32 *)(D_00423114 + 0x362C) = 6;
        break;
    case 5:
        if (*(s32 *)(D_00423114 + 0x18C) & 1) {
            *(s32 *)(D_00423114 + 0x18C) = *(s32 *)(D_00423114 + 0x18C) ^ 1;
        }
        *(s32 *)(D_00423114 + 0x362C) = 1;
        break;
    }
}
