#include "common.h"

extern s32 D_003876A0;
extern s32 D_003876B0;
extern s32 D_00387A40;

void func_0027D7B8(s32 arg0);
void func_00104FC0(s32 arg0);
s32 func_00105000(void);
void func_0025E0B8(s32 arg0, s32 arg1, s32 arg2);
void func_0025FED8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_00260100(s32 arg0, f32 farg0);
void func_0025C6B8(void);
void func_0025CB50(f32 arg0, f32 arg1, f32 arg2);
void func_0025CB70(f32 arg0, f32 arg1, f32 arg2);
void func_0025CB90(f32 farg0);
void func_0025CBA0(f32 farg0, f32 farg1);
void func_0025E190(s32 arg0, s32 arg1);

/* Per-frame state machine on the block at D_003876B0: word 0 = state (0..5), word 1 = timer. */
s32 func_00105278(s32 arg0) {
    s32 s0 = arg0;
    s32 p = D_003876B0;
    s32 blk;

    if (*(s32 *)(p + 4) < 0) {
        *(s32 *)(p + 4) = 0;
    }
    if (*(s32 *)(p + 4) >= 81) {
        *(s32 *)(p + 4) = 80;
    }
    p = D_003876B0;

    switch (*(s32 *)p) {
    case 0:
        *(s64 *)(D_003876A0 + 0x4D8) = *(s64 *)(D_003876A0 + 0x4D8) & ~0x100LL;
        func_0027D7B8(1);
        func_00104FC0(9 * s0 + 0xACBB);
        *(s32 *)(D_003876B0 + 4) = 0;
        *(s32 *)D_003876B0 = *(s32 *)D_003876B0 + 1;
        return 0;

    case 1:
        *(s32 *)(p + 4) = *(s32 *)(p + 4) + 5;
        return 0;

    case 2:
        __builtin_memset((void *)(p + 0xC), 0, 0x30);
        s0 = s0 << 4;
        *(s32 *)(p + 0x18) = 0xACD6;
        *(s32 *)(p + 0x30) = *(s32 *)(p + 8);
        func_0025E0B8(0, *(s32 *)(D_00387A40 + 8), p + 0xC);
        func_0025FED8(*(s32 *)(D_00387A40 + 8), 7, 2, 1, 1);
        blk = *(s32 *)(D_00387A40 + 8);
        *(s32 *)(blk + 0xAF0) = *(s32 *)(blk + 0xAF0) | 0x20000000;
        *(s32 *)(blk + 0xAF0) = *(s32 *)(blk + 0xAF0) | 0x1000000;
        func_00260100(blk, 1.0f);
        func_0025C6B8();
        func_0025CB50(0.0f, *(f32 *)(s0 + *(s32 *)(D_003876B0 + 0x3C) + 4), 0.0f);
        func_0025CB70(0.0f, 0.0f, 0.0f);
        func_0025CB90(*(f32 *)(s0 + *(s32 *)(D_003876B0 + 0x3C) + 8));
        s0 = s0 + *(s32 *)(D_003876B0 + 0x3C);
        func_0025CBA0(*(f32 *)(s0 + 0xC), *(f32 *)(s0 + 8));
        *(s32 *)(D_003876B0 + 4) = *(s32 *)(D_003876B0 + 4) + 5;
        *(s32 *)D_003876B0 = *(s32 *)D_003876B0 + 1;
        return 0;

    case 3:
        if (func_00105000() != 0) {
            *(s32 *)D_003876B0 = *(s32 *)D_003876B0 + 1;
        }
        *(s32 *)(D_003876B0 + 4) = *(s32 *)(D_003876B0 + 4) + 5;
        return 0;

    case 4:
        *(s32 *)(p + 4) = *(s32 *)(p + 4) - 5;
        if (*(s32 *)(D_003876B0 + 4) >= 0) {
            return 0;
        }
        *(s32 *)D_003876B0 = *(s32 *)D_003876B0 + 1;
        return 0;

    case 5:
        func_0025E190(*(s32 *)(D_00387A40 + 8), 0);
        *(s32 *)D_003876B0 = 0;
        return 1;

    default:
        return 0;
    }
}
