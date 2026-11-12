#include "common.h"

s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_00206958(s32 arg0, s64 arg1);
s32 func_00217488(s32 arg0);
s32 BtlAnim_SetBlend(s32 arg0, f32 farg0);
s32 func_00212320(s32 arg0);
s32 func_002411E0(s32 arg0, s32 arg1);
s32 func_0023C710(s32 arg0);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern f32 D_00386998;

/* 0x00234D78: staged check. Returns 0x97 when the first probe succeeds (after a 0x800 flag call),
 * otherwise runs a second probe; a kind switch returns 0xC1..0xC3 for three of its values, and the
 * remaining path ends in a blend call and a tail call to func_0023C710 (or 0x21 / -1 early exits). */
s32 func_00234D78(s32 arg0) {
    s32 t;

    if (func_00211310(arg0, 4, 0x2000000) != 0) {
        func_002113C0(arg0, 2, 0x800, 1);
        return 0x97;
    }

    if (func_00211310(arg0, 4, 0x800000) != 0) {
        func_00206958(arg0, 0x20);
        t = func_00217488(arg0) - 0xB8;
        switch (t) {
            case 0:
            case 6:
                return 0xC1;
            case 1:
            case 7:
                return 0xC2;
            case 2:
            case 8:
                return 0xC3;
            default:
                break;
        }
    }

    if (func_00211310(arg0, 2, 1) == 0) {
        return -1;
    }
    BtlAnim_SetBlend(arg0, D_00386998);
    t = func_00212320(arg0);
    t = func_002411E0(arg0, t);
    if ((t & 0x40000000) != 0) {
        return 0x21;
    }
    return func_0023C710(arg0);
}
