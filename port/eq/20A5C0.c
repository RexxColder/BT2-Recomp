#include "common.h"

/* 0x0020A5C0: if (!D_00387930 || (u32)a0 >= 2) return 0; p = func_00211288(a0);
   return func_00211310(p, 0xC, 0x10) != 0 || func_00211310(p, 0xC, 0x800) != 0 || func_00211310(p, 0xC, 0x80000) != 0. */
extern u8 D_00387930[];
s32 func_00211288(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);

s32 func_0020A5C0(s32 a0) {
    s32 p;

    if (*(u8 **)D_00387930 == NULL) {
        return 0;
    }
    if ((u32)a0 >= 2) {
        return 0;
    }
    p = func_00211288(a0);
    if (func_00211310(p, 0xC, 0x10) != 0) {
        return 1;
    }
    if (func_00211310(p, 0xC, 0x800) != 0) {
        return 1;
    }
    if (func_00211310(p, 0xC, 0x80000) != 0) {
        return 1;
    }
    return 0;
}
