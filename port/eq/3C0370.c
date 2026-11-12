#include "common.h"

extern u8 *D_00421C94 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));
extern s32 D_3876AC __attribute__((section(".data")));

s32 func_100D58(s32 a0, s32 a1, s32 a2);
void func_243968(s32 a0, s32 a1, s32 a2, u8 *g);
void func_243A80(s32 a0, s32 a1, s32 a2);
void func_250978(s32 a0);
void func_28BB60(s32 a0);

/* 0x003C0370: G = D_00421C94, P = D_3876A4. If G->0x52C has no 0x100: set it, func_100D58(P->4 + 0xE, 0, 1), tail
 * func_243A80(0,0,0). Else if 0x200 is clear: D_3876AC = func_100D58(0,0,0); if non-zero set G->0x52C |= 0x200,
 * P->0x494 = G->0x520 + 0x4A, park P->0x1C at 0x29 and spin until it reads 0x29 (func_250978(1)), restore it, clear
 * 0x80/0x100/0x200 in G->0x52C, func_243968(0,0,0,G), func_28BB60(D_3876AC), D_3876AC = 0. */
void func_003C0370(void) {
    s32 saved;
    s32 s2;
    s32 v;

    v = *(s32 *)(D_00421C94 + 0x52C);
    if ((v & 0x100) == 0) {
        *(s32 *)(D_00421C94 + 0x52C) = v | 0x100;
        func_100D58(*(s32 *)(D_3876A4 + 4) + 0xE, 0, 1);
        func_243A80(0, 0, 0);
        return;
    }
    if ((v & 0x200) != 0) {
        return;
    }
    D_3876AC = func_100D58(0, 0, 0);
    if (D_3876AC == 0) {
        return;
    }
    *(s32 *)(D_00421C94 + 0x52C) |= 0x200;
    *(s32 *)(D_3876A4 + 0x494) = *(s32 *)(D_00421C94 + 0x520) + 0x4A;
    saved = *(s32 *)(D_3876A4 + 0x1C);
    *(s32 *)(D_3876A4 + 0x1C) = 0x29;
    s2 = 1; /* GUESS: this path never writes s2; the draft assumes the wait loop runs */
    do {
        if (*(s32 *)(D_3876A4 + 0x1C) == 0x29) {
            s2 = 0;
            func_250978(1);
        }
    } while (s2 != 0);
    *(s32 *)(D_3876A4 + 0x1C) = saved;
    *(s32 *)(D_00421C94 + 0x52C) &= ~0x80;
    *(s32 *)(D_00421C94 + 0x52C) &= ~0x100;
    *(s32 *)(D_00421C94 + 0x52C) &= ~0x200;
    func_243968(0, 0, 0, D_00421C94);
    func_28BB60(D_3876AC);
    D_3876AC = 0;
}
