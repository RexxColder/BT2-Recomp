#include "common.h"

extern u8 *D_0042A580 __attribute__((section(".data")));
extern u8 D_003B0B00[] __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));

s32 func_26EB60(u8 *p);
void func_297FE0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);

/* 0x003FA268: input handler on the record G = D_0042A580 (after func_26EB60(G+0x64) != 0), reading the input block
 * IN = D_003B0B00 (0x134 buttons, 0x144 pressed bits). Bit 0x10: G->0xD4 counts down (clamped to 1 below 0); bit 0x40:
 * G->0xD4 counts up 0..1 (wraps to 0 at 2); neither: bit 0x8000 sets G->0xE8 = 0x65 and calls func_297FE0(0,1,..);
 * bit 0x4000 picks P->0x1C = 0xE / 0xF from G->0xD4 (0 / 1) and calls func_297FE0(0,1,..) after G->0xD0 |= 3 and
 * G->0xE0 = 0xF; bit 0x1000 sets G->0xE8 = 0x33, *out = 0, func_297FE0(0,2,..). Each call passes 0x40, 0x40, t0 = 1. */
void func_003FA268(s32 *arg0) {
    s32 a0;
    s32 a1;
    s32 v;

    if (func_26EB60(D_0042A580 + 0x64) == 0) {
        return;
    }
    if (*(s32 *)(D_003B0B00 + 0x144) & 0x10) {
        *(s32 *)(D_0042A580 + 0xD4) = *(s32 *)(D_0042A580 + 0xD4) - 1;
        if (*(s32 *)(D_0042A580 + 0xD4) < 0) {
            *(s32 *)(D_0042A580 + 0xD4) = 1;
        }
        a0 = 0;
        a1 = 0;
    } else if (*(s32 *)(D_003B0B00 + 0x144) & 0x40) {
        *(s32 *)(D_0042A580 + 0xD4) = *(s32 *)(D_0042A580 + 0xD4) + 1;
        if (*(s32 *)(D_0042A580 + 0xD4) >= 2) {
            *(s32 *)(D_0042A580 + 0xD4) = 0;
        }
        a0 = 0;
        a1 = 0;
    } else {
        v = *(s32 *)(D_003B0B00 + 0x134);
        if (v & 0x8000) {
            *(s32 *)(D_0042A580 + 0xE8) = 0x65;
            a0 = 0;
            a1 = 1;
        } else if (v & 0x4000) {
            switch (*(s32 *)(D_0042A580 + 0xD4)) {
            case 0:
                *(s32 *)(D_3876A4 + 0x1C) = 0xE;
                break;
            case 1:
                *(s32 *)(D_3876A4 + 0x1C) = 0xF;
                break;
            default:
                break;
            }
            *(s32 *)(D_0042A580 + 0xD0) = *(s32 *)(D_0042A580 + 0xD0) | 1;
            *(s32 *)(D_0042A580 + 0xD0) = *(s32 *)(D_0042A580 + 0xD0) | 2;
            *(s32 *)(D_0042A580 + 0xE0) = 0xF;
            func_297FE0(0, 1, 0x40, 0x40, 1);
            return;
        } else if (v & 0x1000) {
            *(s32 *)(D_0042A580 + 0xE8) = 0x33;
            *arg0 = 0;
            func_297FE0(0, 2, 0x40, 0x40, 1);
            return;
        } else {
            return;
        }
    }
    func_297FE0(a0, a1, 0x40, 0x40, 1);
}
