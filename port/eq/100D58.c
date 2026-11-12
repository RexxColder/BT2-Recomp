#include "common.h"

s32 func_002EB9B0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002EC6B0(s32 arg0);
s32 func_0028BAA8(s32 arg0);
s32 func_002EC0C8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_002EC990(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002EBB08(s32 arg0);
extern s32 D_00387688;
extern s32 D_0038768C;
extern s32 D_00387690;
extern s32 D_00387694;
extern s32 D_00387F20[];

s32 func_00100D58(s32 arg0, s32 arg1, s32 arg2) {
    s32 t;
    s32 val;

    if (arg2 != 0) {
        D_00387688 = 0;
        D_0038768C = 0;
        D_00387690 = 0;
    }
    if (D_00387688 == 1) {
        if (func_002EC0C8(D_0038768C, D_00387690, D_00387694, arg0) == D_00387690) {
            D_00387688 += 1;
        }
        return 0;
    }
    if (D_00387688 == 0) {
        t = (arg0 < 0x33B2);
        val = t ? arg0 : arg0 - 0x33B2;
        D_0038768C = func_002EB9B0(D_00387F20[t ? 0 : 1], val, arg2, arg0);
        D_00387690 = func_002EC6B0(D_0038768C);
        if (arg1 != 0) {
            D_00387694 = arg1;
        } else {
            D_00387694 = func_0028BAA8(D_00387690 << 0xB);
        }
        D_00387688 += 1;
        return 0;
    }
    if (D_00387688 == 2) {
        if (func_002EC990(D_0038768C, arg1, arg2, arg0) == 3) {
            func_002EBB08(D_0038768C);
            D_0038768C = 0;
            D_00387688 += 1;
        }
        return 0;
    }
    if (D_00387688 == 3) {
        return D_00387694;
    }
    return 0;
}
