#include "common.h"

extern f32 D_003868A0;
extern f32 D_003868A4;

s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 BtlAnim_SetBlend(s32 arg0, f32 farg0);
s32 func_00212320(s32 arg0);
s32 func_002411E0(s32 arg0, s32 arg1);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_0023C710(s32 arg0, s32 arg1);

/* 0x00231B58: state step for the battle object arg0. A probe (func_00211310 with 0x4000000) that
 * succeeds blends with D_003868A0 and dispatches on func_00212320: 3, 2 and 4 return 0xCE, 0xCD and
 * 0xCF. Otherwise (also when the probe fails) a second probe runs; zero returns -1. Then it blends
 * with D_003868A4 and tests bit 0x200000 of func_002411E0: set means three func_002113C0 calls and
 * return 0x21, clear means a tail call to func_0023C710 (with a1 = 1). */
s32 func_00231B58(u8 *arg0) {
    s32 r;
    s32 v;
    s32 r2;
    s32 r3;

    r = func_00211310((s32)arg0, 4, 0x4000000);
    if (r != 0) {
        BtlAnim_SetBlend((s32)arg0, D_003868A0);
        v = func_00212320((s32)arg0);
        if (v == 3) {
            return 0xCE;
        }
        if (v == 2) {
            return 0xCD;
        }
        if (v == 4) {
            return 0xCF;
        }
    }

    r2 = func_00211310((s32)arg0, 2, 1);
    if (r2 == 0) {
        return -1;
    }
    BtlAnim_SetBlend((s32)arg0, D_003868A4);
    v = func_00212320((s32)arg0);
    r3 = func_002411E0((s32)arg0, v);
    if ((r3 & 0x200000) != 0) {
        func_002113C0((s32)arg0, 1, 0x40000, 1);
        func_002113C0((s32)arg0, 1, 0x80000, 1);
        func_002113C0((s32)arg0, 2, 0x1000, 1);
        return 0x21;
    }
    return func_0023C710((s32)arg0, 1);
}
