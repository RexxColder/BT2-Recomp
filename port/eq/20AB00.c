#include "common.h"

/* 0x0020AB00: if (!D_00387930 || (u32)a0 >= 2) return 0; p = func_00211288(a0);
   if (func_00211310(p, 1, 0x1000) == 0) return 0; if (func_00211310(p, 1, 0x4000) != 0) return 0;
   return func_00211310(p, 1, 0x8000) == 0. */
extern u8 D_00387930[];
s32 func_00211288(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);

s32 func_0020AB00(s32 a0) {
    s32 p;

    if (*(u8 **)D_00387930 == NULL) {
        return 0;
    }
    if ((u32)a0 >= 2) {
        return 0;
    }
    p = func_00211288(a0);
    if (func_00211310(p, 1, 0x1000) == 0) {
        return 0;
    }
    if (func_00211310(p, 1, 0x4000) != 0) {
        return 0;
    }
    return func_00211310(p, 1, 0x8000) == 0;
}
