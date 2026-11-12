#include "common.h"

extern s32 D_00387930;
extern s32 func_00211288();
extern s32 func_002113C0();

/* 0x0020CC10: if flag set and idx < 2 (unsigned): tail call func_002113C0(func_00211288(idx), 7, 1, 1). */
s32 func_0020CC10(u32 idx) {
    if (D_00387930 == 0) {
        return idx < 2; /* stale v0 from the delay-slot sltiu */
    }
    if (idx >= 2) {
        return 0;
    }
    return func_002113C0(func_00211288(idx), 7, 1, 1);
}
