#include "common.h"

/* 0x0020A7D0: if (!D_00387930 || (u32)a0 >= 2) return 0; v = func_00217488(func_00211288(a0)); return v >= 0xB8 && v < 0xC1. */
extern u8 D_00387930[];
s32 func_00211288(s32 arg0);
s32 func_00217488(s32 arg0);

s32 func_0020A7D0(s32 a0) {
    s32 v;

    if (*(u8 **)D_00387930 == NULL) {
        return 0;
    }
    if ((u32)a0 >= 2) {
        return 0;
    }
    v = func_00217488(func_00211288(a0));
    return v >= 0xB8 && v < 0xC1;
}
