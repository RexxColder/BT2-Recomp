#include "common.h"

/* 0x00209848: if (!D_00387930) return 0; if (!((u32)a0 < 2)) return 0; return func_00211288(a0)->+0x1F8 (u8). */
extern u8 D_00387930[];
s32 func_00211288(s32 arg0);

s32 func_00209848(s32 a0) {
    u8 *p;

    if (*(u8 **)D_00387930 == NULL) {
        return 0;
    }
    if ((u32)a0 >= 2) {
        return 0;
    }
    p = (u8 *)func_00211288(a0);
    return *(u8 *)(p + 0x1F8);
}
