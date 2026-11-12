#include "common.h"

/* 0x0020A908: if (!D_00387930 || (u32)a0 >= 2) return 0; p = func_00211288(a0); return func_00217488(p) == 0xE4. */
extern u8 D_00387930[];
s32 func_00211288(s32 arg0);
s32 func_00217488(s32 arg0);

s32 func_0020A908(s32 a0) {
    s32 p;

    if (*(u8 **)D_00387930 == NULL) {
        return 0;
    }
    if ((u32)a0 >= 2) {
        return 0;
    }
    p = func_00211288(a0);
    return func_00217488(p) == 0xE4;
}
