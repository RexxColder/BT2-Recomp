#include "common.h"

extern u8 *D_003879A0;

#define W(p, off) (*(s32 *)((p) + (off)))

s32 func_00100FC8(s32 arg0);
void func_00100ED0(s32 arg0, s32 arg1, s32 arg2);
void func_002B24C8(s32 arg0, s32 arg1, s32 arg2);
void Res_RelocateOffsets(u8 *arg0, s32 arg1, s32 arg2);

/* jtbl_00374A70 by index (state - 1): 0 -> CE30, 1 -> CE98, 2 -> CEB8, 3 -> CF18, 4 -> CF28, 5 -> CE08. */
void func_0024CDD0(void) {
    u8 *d;
    u32 idx;
    u8 sp[0x10];
    u8 *entry;
    u8 *q;
    s32 x;
    s32 y;
    s32 v1;

    d = D_003879A0;
    idx = (u32)(W(d, 0x3224) - 1);
    if (idx >= 6) {
        return;
    }
    switch (idx) {
    case 0:
        x = W(d, 0x1CC);
        y = W(d, 0x1C8);
        v1 = 7 * x + y;
        entry = (u8 *)W(d, 0x1E8) + 44 * v1;
        W(d, 0x1D0) = W(entry, 0);
        func_00100ED0(W(entry, 0) + 0x56B, W(d, 8), 1);
        func_00100FC8(1);
        W(d, 0x3224) = 2;
        break;
    case 1:
        if (func_00100FC8(0) != 0) {
            W(d, 0x3224) = 3;
        }
        break;
    case 2:
        func_002B24C8(W(d, 8), W(d, 0xC), 0);
        W(sp, 0) = W(d, 0xC);
        Res_RelocateOffsets(sp, W(d, 0xC), W(d, 0xC));
        q = (u8 *)W(sp, 0);
        W(d, 0xD8) = W(q, 0x10);
        W(d, 0x1C4) = W(d, 0x1C4) | 0x40;
        W(d, 0x3224) = 4;
        break;
    case 3:
        if (W(d, 0x1C4) & 1) {
            W(d, 0x3224) = 6;
        }
        break;
    case 4:
        W(d, 0x3224) = 6;
        break;
    case 5:
        if (W(d, 0x1C4) & 1) {
            W(d, 0x1C4) = W(d, 0x1C4) ^ 1;
        }
        W(d, 0x3224) = 1;
        break;
    }
}
