#include "common.h"

extern u8 *D_00421CF4 __attribute__((section(".data")));

void func_100ED0(s32 arg0, u8 *arg1, s32 arg2);
s32 func_100FC8(s32 arg0);
void func_2B24C8(u8 *arg0, u8 *arg1, s32 arg2);
void Res_RelocateOffsets(u8 *arg0, u8 *arg1, u8 *arg2);

/* 0x003C2DF0: state machine on G->0x678 (G = D_00421CF4), index v1 = state - 1 (unsigned < 6 or return):
 * v1 0 (state 1): func_100ED0((s16)G->0x65C + 0x5EE, G->0x30, 1), func_100FC8(1), state = 2.
 * v1 1 (state 2): if func_100FC8(0) != 0, state = 3.
 * v1 2 (state 3): func_2B24C8(G->0x30, G->0x34, 0); sp[0] = G->0x34; Res_RelocateOffsets(sp, sp[0], sp[0]);
 *   G->0x184 = *(sp[0] + 0x10); G->0x1FC |= 0x80; state = 4.
 * v1 3 (state 4): if G->0x1FC & 0x40, state = 6.
 * v1 4 (state 5): state = 6.
 * v1 5 (state 6): if G->0x1FC & 0x40, G->0x1FC ^= 0x40; state = 1. */
void func_003C2DF0(void) {
    u8 *sp[2];
    s32 v1;

    v1 = *(s32 *)(D_00421CF4 + 0x678) - 1;
    if ((u32)v1 >= 6) {
        return;
    }
    switch (v1) {
    case 0:
        func_100ED0((s32)*(s16 *)(D_00421CF4 + 0x65C) + 0x5EE, *(u8 **)(D_00421CF4 + 0x30), 1);
        func_100FC8(1);
        *(s32 *)(D_00421CF4 + 0x678) = 2;
        break;
    case 1:
        if (func_100FC8(0) != 0) {
            *(s32 *)(D_00421CF4 + 0x678) = 3;
        }
        break;
    case 2:
        func_2B24C8(*(u8 **)(D_00421CF4 + 0x30), *(u8 **)(D_00421CF4 + 0x34), 0);
        sp[0] = *(u8 **)(D_00421CF4 + 0x34);
        Res_RelocateOffsets((u8 *)sp, sp[0], sp[0]);
        *(s32 *)(D_00421CF4 + 0x184) = *(s32 *)(sp[0] + 0x10);
        *(s32 *)(D_00421CF4 + 0x1FC) = *(s32 *)(D_00421CF4 + 0x1FC) | 0x80;
        *(s32 *)(D_00421CF4 + 0x678) = 4;
        break;
    case 3:
        if (*(s32 *)(D_00421CF4 + 0x1FC) & 0x40) {
            *(s32 *)(D_00421CF4 + 0x678) = 6;
        }
        break;
    case 4:
        *(s32 *)(D_00421CF4 + 0x678) = 6;
        break;
    case 5:
        if (*(s32 *)(D_00421CF4 + 0x1FC) & 0x40) {
            *(s32 *)(D_00421CF4 + 0x1FC) = *(s32 *)(D_00421CF4 + 0x1FC) ^ 0x40;
        }
        *(s32 *)(D_00421CF4 + 0x678) = 1;
        break;
    }
}
