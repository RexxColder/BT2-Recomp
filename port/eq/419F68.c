#include "common.h"

extern u8 *D_0042BB80 __attribute__((section(".data")));
extern u8 D_0042F480 __attribute__((section(".data")));
extern u8 D_0042F490 __attribute__((section(".data")));
extern u8 D_0042F4A0 __attribute__((section(".data")));
extern u8 D_003B0B00[] __attribute__((section(".data")));
extern u8 *D_003876A4 __attribute__((section(".data")));
extern u8 *D_00387F2C __attribute__((section(".data")));

s32 func_26EB60(u8 *arg0);
void func_26EB78(u8 *arg0, u8 *arg1);
void func_26EB90(u8 *arg0, u8 *arg1);
void func_297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_243A80(s32 arg0, s32 arg1, s32 arg2);
void func_4190C0(void);
void func_419E28(void);

#define G (D_0042BB80)
#define W(o) (*(s32 *)(G + (o)))

/* one pad block; pa/pb = the two button words (0x144/0x134 or 0x2C4/0x2B4), mode 0 uses func_26EB90, mode 1 func_26EB78.
 * Returns 1 when an action was taken (and func_297FE0 called). */
static s32 pad_part(s32 pa, s32 pb, s32 mode, s32 *arg0) {
    if ((pa & 0x10) && W(0xC8) < 8) {
        func_419E28();
        W(0xD4) = W(0xD4) - 1;
        if (W(0xD4) < 0) {
            W(0xD4) = W(0x13C) - 1;
        }
        func_26EB78(G + 0x30, &D_0042F480);
        func_297FE0(0, 0, 0x40, 0x40, 1);
        return 1;
    }
    if ((pa & 0x40) && W(0xC8) < 8) {
        func_419E28();
        W(0xD4) = W(0xD4) + 1;
        if (!(W(0xD4) < W(0x13C))) {
            W(0xD4) = 0;
        }
        func_26EB78(G + 0x30, &D_0042F490);
        func_297FE0(0, 0, 0x40, 0x40, 1);
        return 1;
    }
    if (pa & 0x400) {
        W(0xD8) = W(0xD8) - 1;
        if (W(0xD8) < 0) {
            W(0xD8) = W(0x144);
        }
        func_4190C0();
        func_297FE0(1, 0, 0x40, 0x40, 1);
        return 1;
    }
    if (pa & 0x800) {
        W(0xD8) = W(0xD8) + 1;
        if (W(0x144) < W(0xD8)) {
            W(0xD8) = 0;
        }
        func_4190C0();
        func_297FE0(1, 0, 0x40, 0x40, 1);
        return 1;
    }
    if (pb & 0x2000) {
        W(0xE0) = W(0xE0) ^ 1;
        if (W(0xE0) != 0) {
            *(s32 *)(D_00387F2C + 0x808) = *(s32 *)(D_00387F2C + 0x808) | 1;
        } else {
            *(s32 *)(D_00387F2C + 0x808) = *(s32 *)(D_00387F2C + 0x808) & ~1;
        }
        func_297FE0(0, 1, 0x40, 0x40, 1);
        return 1;
    }
    if ((pb & 0xC000) && W(0xC8) < 8) {
        if (pb & 0x8000) {
            W(0xD0) = W(0xD0) | 8;
        }
        W(0xD0) = W(0xD0) | 1;
        W(0xD0) = W(0xD0) | 2;
        W(0xE8) = 0xF;
        W(0xDC) = W(0xD4) - 3;
        if (W(0xDC) < 0) {
            W(0xDC) = W(0xDC) + W(0x13C);
        }
        if (mode == 0) {
            func_26EB90(G + 0x30, &D_0042F4A0);
            func_26EB90(G + 8, &D_0042F4A0);
        } else {
            func_26EB78(G + 0x30, &D_0042F4A0);
            func_26EB78(G + 8, &D_0042F4A0);
        }
        func_297FE0(0, 1, 0x40, 0x40, 1);
        return 1;
    }
    if ((pb & 0x1000) && W(0xC8) < 8) {
        func_243A80(0, 0, 0);
        *arg0 = 0;
        func_297FE0(0, 2, 0x40, 0x40, 1);
        return 1;
    }
    return 0;
}

void func_00419F68(s32 *arg0) {
    if (func_26EB60(G + 0x30) == 0) {
        return;
    }
    if (pad_part(*(s32 *)(D_003B0B00 + 0x144), *(s32 *)(D_003B0B00 + 0x134), 0, arg0)) {
        return;
    }
    if (*(s32 *)(D_003876A4 + 0x458) != 1) {
        return;
    }
    pad_part(*(s32 *)(D_003B0B00 + 0x2C4), *(s32 *)(D_003B0B00 + 0x2B4), 1, arg0);
}
