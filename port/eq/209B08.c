#include "common.h"

/* 0x00209B08: if (!D_00387930 || (u32)a0 >= 2) return 0; p = func_00211288(a0);
   if (func_00211310(p, 0xE, 0x1000) != 0) return -1; if (func_00211310(p, 0xE, 0x800) != 0) return 1; return 0. */
extern u8 D_00387930[];
s32 func_00211288(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);

s32 func_00209B08(s32 a0) {
    s32 p;

    if (*(u8 **)D_00387930 == NULL) {
        return 0;
    }
    if ((u32)a0 >= 2) {
        return 0;
    }
    p = func_00211288(a0);
    if (func_00211310(p, 0xE, 0x1000) != 0) {
        return -1;
    }
    if (func_00211310(p, 0xE, 0x800) != 0) {
        return 1;
    }
    return 0;
}
