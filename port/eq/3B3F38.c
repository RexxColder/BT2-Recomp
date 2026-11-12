#include "common.h"

extern u8 *D_00421380 __attribute__((section(".data")));
extern u8 *D_003876A4 __attribute__((section(".data")));
extern u8 D_003B0B00[] __attribute__((section(".data")));
extern u8 D_00421780[] __attribute__((section(".data")));
extern u8 D_00421790[] __attribute__((section(".data")));
extern u8 D_004217A0[] __attribute__((section(".data")));

s32 func_26EB60(u8 *arg0);
void func_26EB78(u8 *arg0, u8 *arg1);
void func_003B3DE8(void);
void func_243A80(s32 arg0, s32 arg1, s32 arg2);
void func_297FE0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);

/* 0x003B3F38: object G = D_00421380, gated by func_26EB60(G + 0x38) != 0. Flags word F1 = D_003B0B00 + 0x144.
 * F1 & 0x10 steps the 0..9 counter G->0xE8 down (wrap to 9) and the G->0xF0 pair, then func_003B3DE8, func_26EB78 with
 * D_00421780, and func_297FE0(0, 0, ...). F1 & 0x40 steps G->0xE8 up (wrap to 0) and calls with D_00421790 the same way.
 * Otherwise, with F2 = D_003B0B00 + 0x134: bit 0x4000 and G->0xE8 < 10 selects a jump-table case (jtbl_004217B0) that
 * writes the state word P->0x1C of D_003876A4, then the shared tail (G->0xF0, G->0xE4 |= 3, G->0xF8 = 0xF,
 * func_26EB78 with D_004217A0, func_297FE0(0, 1, ...)). Without 0x4000, bit 0x1000 selects func_243A80 and the
 * *arg0 = 0 path with func_297FE0(0, 2, ...). */
void func_003B3F38(s32 *arg0) {
    u8 *g;
    u8 *p;
    s32 f1;
    s32 f2;
    s32 e8;

    g = D_00421380;
    if (func_26EB60(g + 0x38) == 0) {
        return;
    }

    f1 = *(s32 *)(D_003B0B00 + 0x144);
    if (f1 & 0x10) {
        *(s32 *)(g + 0xF0) = *(s32 *)(g + 0xE8) - 2;
        if (*(s32 *)(g + 0xF0) < 0) {
            *(s32 *)(g + 0xF0) += 10;
        }
        *(s32 *)(g + 0xE8) = *(s32 *)(g + 0xE8) - 1;
        if (*(s32 *)(g + 0xE8) < 0) {
            *(s32 *)(g + 0xE8) = 9;
        }
        func_003B3DE8();
        func_26EB78(g + 0x38, D_00421780);
        func_297FE0(0, 0, 0x40, 0x40, 1);
        return;
    }

    if (f1 & 0x40) {
        *(s32 *)(g + 0xF0) = *(s32 *)(g + 0xE8) - 2;
        if (*(s32 *)(g + 0xF0) < 0) {
            *(s32 *)(g + 0xF0) += 10;
        }
        *(s32 *)(g + 0xE8) = *(s32 *)(g + 0xE8) + 1;
        if (*(s32 *)(g + 0xE8) >= 10) {
            *(s32 *)(g + 0xE8) = 0;
        }
        func_003B3DE8();
        func_26EB78(g + 0x38, D_00421790);
        func_297FE0(0, 0, 0x40, 0x40, 1);
        return;
    }

    f2 = *(s32 *)(D_003B0B00 + 0x134);
    if (f2 & 0x4000) {
        e8 = *(s32 *)(g + 0xE8);
        if ((u32)e8 >= 10) {
            return;
        }
        p = D_003876A4;
        switch (e8) {
        case 0:
            if (*(s32 *)(p + 0x2C) & 0x02000000) {
                *(s32 *)(p + 0x1C) = 7;
            } else {
                *(s32 *)(p + 0x1C) = 6;
            }
            break;
        case 1:
            *(s32 *)(p + 0x1C) = 0xA;
            break;
        case 2:
            *(s32 *)(p + 0x1C) = 0x18;
            break;
        case 3:
            *(s32 *)(p + 0x1C) = 0x1E;
            break;
        case 4:
            *(s32 *)(p + 0x1C) = 0x3D;
            break;
        case 5:
            *(s32 *)(p + 0x1C) = 0x35;
            break;
        case 6:
            *(s32 *)(p + 0x1C) = 0x5;
            break;
        case 7:
            *(s32 *)(p + 0x1C) = 0x26;
            break;
        case 8:
            *(s32 *)(p + 0x1C) = 0x30;
            break;
        case 9:
            *(s32 *)(p + 0x1C) = 0x2B;
            break;
        default:
            break;
        }

        *(s32 *)(g + 0xF0) = *(s32 *)(g + 0xE8) - 2;
        if (*(s32 *)(g + 0xF0) < 0) {
            *(s32 *)(g + 0xF0) += 10;
        }
        *(s32 *)(g + 0xE4) |= 1;
        *(s32 *)(g + 0xE4) |= 2;
        *(s32 *)(g + 0xF8) = 0xF;
        func_26EB78(g + 0x38, D_004217A0);
        func_297FE0(0, 1, 0x40, 0x40, 1);
        return;
    }

    if (f2 & 0x1000) {
        func_243A80(0, 0, 0);
        *arg0 = 0;
        func_297FE0(0, 2, 0x40, 0x40, 1);
    }
}
