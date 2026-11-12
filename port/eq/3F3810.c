#include "common.h"

extern u8 *D_0042A570 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));
extern s32 D_3876AC __attribute__((section(".data")));

s32 func_100D58(s32 a0, s32 a1, s32 a2);
void func_243A80(s32 a0, s32 a1, s32 a2);
s32 func_250978(s32 a0);
void func_2539C8(s32 a0);
void func_243968(s32 a0, s32 a1, s32 a2);
void func_28BB60(s32 a0);

/* 0x003F3810: menu state step on X = D_0042A570 (flags at X->0x218: 0x10000 armed, 0x20000 running) and
 * G = D_3876A4 (state at G->0x1C: 0x37 <-> 0x38 loop while func_250978 / func_2539C8 run). */
void func_003F3810(void) {
    u8 *X;
    u8 *G;
    u8 *base;
    s32 old;
    s32 s4;
    s32 st;

    X = D_0042A570;
    if ((*(s32 *)(X + 0x218) & 0x10000) == 0) {
        *(s32 *)(X + 0x218) = *(s32 *)(X + 0x218) | 0x10000;
        func_100D58(*(s32 *)(D_3876A4 + 0x4) + 0xE, 0, 1);
        func_243A80(0, 0, 0);
        return;
    }
    if (*(s32 *)(X + 0x218) & 0x20000) {
        return;
    }

    D_3876AC = func_100D58(0, 0, 0);
    if (D_3876AC == 0) {
        return;
    }

    X = D_0042A570;
    *(s32 *)(X + 0x218) = *(s32 *)(X + 0x218) | 0x20000;
    G = D_3876A4;
    base = X + *(s32 *)(X + 0x214) * 4;
    *(s32 *)(G + 0x494) = *(s32 *)(base + 0x21C) + *(s32 *)(base + 0x224) * 7;
    old = *(s32 *)(G + 0x1C);
    *(s32 *)(G + 0x1C) = 0x37;

    s4 = 1;
    while (s4 != 0) {
        st = *(s32 *)(D_3876A4 + 0x1C);
        if (st == 0x37) {
            if (func_250978(1) == 0) {
                s4 = 0;
            } else {
                *(s32 *)(D_3876A4 + 0x1C) = 0x38;
            }
        } else if (st == 0x38) {
            func_2539C8(2);
            *(s32 *)(D_3876A4 + 0x1C) = 0x37;
        }
    }
    *(s32 *)(D_3876A4 + 0x1C) = old;

    X = D_0042A570;
    if (*(s32 *)(X + 0x218) & 0x4000) {
        *(s32 *)(X + 0x218) = *(s32 *)(X + 0x218) ^ 0x4000;
    } else if (*(s32 *)(X + 0x218) & 0x8000) {
        *(s32 *)(X + 0x218) = *(s32 *)(X + 0x218) ^ 0x8000;
    }

    X = D_0042A570;
    *(s32 *)(X + 0x218) = *(s32 *)(X + 0x218) & ~0x10000;
    X = D_0042A570;
    *(s32 *)(X + 0x218) = *(s32 *)(X + 0x218) & ~0x20000;
    G = D_3876A4;
    *(s32 *)(G + 0x48C) = *(s32 *)(G + 0x48C) & ~1;
    *(s32 *)(G + 0x48C) = *(s32 *)(G + 0x48C) & ~2;
    func_243968(0, 0, 0);
    func_28BB60(D_3876AC);
    D_3876AC = 0;
}
