#include "common.h"

/* 0x00209AC0: if (!D_00387930 || !((u32)a0 < 2)) return 1.0f; return *(f32 *)(func_00211288(a0) + 0x1F4). */
extern u8 D_00387930[];
s32 func_00211288(s32 arg0);

f32 func_00209AC0(s32 a0) {
    u8 *p;

    if (*(u8 **)D_00387930 == NULL) {
        return 1.0f;
    }
    if ((u32)a0 >= 2) {
        return 1.0f;
    }
    p = (u8 *)func_00211288(a0);
    return *(f32 *)(p + 0x1F4);
}
