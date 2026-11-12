#include "common.h"

extern u8 *D_0042A588 __attribute__((section(".data")));
extern u8 D_0042B840 __attribute__((section(".data")));
extern u8 *D_003876A4 __attribute__((section(".data")));
extern u8 D_003B0B00[] __attribute__((section(".data")));

s32 func_26EB60(u8 *arg0);
void func_26EB78();
void func_297FE0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);

#define G_W(off) (*(s32 *)(D_0042A588 + (off)))

/* 0x003FD328: state machine on G->0x118 (G = D_0042A588), gated by func_26EB60(G + 0x60) != 0. Flags word
 * F = *(s32 *)(D_003B0B00 + 0x134) (bit 0x4000 = go). States 0..3, others return. Every case that does not return
 * early ends in a call func_297FE0 with (a0, a1, 0x40, 0x40, 1). *arg0 is cleared on the transition cases. */
void func_003FD328(s32 *arg0) {
    s32 i;
    s32 v;
    s32 f;

    if (func_26EB60(D_0042A588 + 0x60) == 0) {
        return;
    }

    switch (G_W(0x118)) {
    case 0:
        if (!(*(s32 *)(D_003B0B00 + 0x134) & 0x4000)) {
            return;
        }
        G_W(0x118) = 1;
        for (i = 0; i < 6; i++) {
            *(s32 *)(D_0042A588 + 0x16C + 4 * i) = *(s32 *)(D_0042A588 + 0x154 + 4 * i);
        }
        G_W(0xFC) &= ~0xFC;
        func_297FE0(2, 6, 0x40, 0x40, 1);
        return;

    case 1:
        if (!(*(s32 *)(D_003B0B00 + 0x134) & 0x4000)) {
            return;
        }
        G_W(0x118) = 2;
        func_26EB78(D_0042A588 + 0x60, &D_0042B840, D_0042A588);
        func_297FE0(0, 1, 0x40, 0x40, 1);
        return;

    case 2:
        f = *(s32 *)(D_003B0B00 + 0x144);
        if (f & 0x10) {
            v = G_W(0x230);
            if (v > 0) {
                G_W(0x230) = v - 1;
                func_297FE0(0, 0, 0x40, 0x40, 1);
            }
        } else if (f & 0x40) {
            v = G_W(0x230);
            if ((v + 5) < G_W(0x22C)) {
                G_W(0x230) = v + 1;
                func_297FE0(0, 0, 0x40, 0x40, 1);
            }
        }
        if (*(s32 *)(D_003B0B00 + 0x134) & 0x4000) {
            *arg0 = 0;
            G_W(0xFC) |= 1;
            G_W(0xFC) |= 2;
            G_W(0x10C) = 0xF;
            *(s32 *)(D_003876A4 + 0x1C) = 0x11;
            func_297FE0(0, 1, 0x40, 0x40, 1);
            return;
        }
        break;

    case 3:
        if (*(s32 *)(D_003B0B00 + 0x134) & 0x4000) {
            if (*(s32 *)(D_003876A4 + 0x40) & 4) {
                *arg0 = 0;
                G_W(0xFC) |= 1;
                G_W(0xFC) |= 2;
                G_W(0x10C) = 0xF;
                *(s32 *)(D_003876A4 + 0x1C) = 0x14;
            } else {
                G_W(0x23C) = 1;
            }
            func_297FE0(0, 1, 0x40, 0x40, 1);
        }
        break;

    default:
        break;
    }
}
