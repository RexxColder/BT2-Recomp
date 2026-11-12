#include "common.h"

/* 0x0020A1A8: if (!D_00387930 || (u32)a0 >= 2) return 0.0f; f = (f32)(func_00211288(a0)->+0xB90) / 90.0f;
   return 1.0f < f ? 1.0f : f. */
extern u8 D_00387930[];
s32 func_00211288(s32 arg0);

f32 func_0020A1A8(s32 a0) {
    u8 *p;
    f32 f;

    if (*(u8 **)D_00387930 == NULL) {
        return 0.0f;
    }
    if ((u32)a0 >= 2) {
        return 0.0f;
    }
    p = (u8 *)func_00211288(a0);
    f = (f32)(*(s32 *)(p + 0xB90)) / 90.0f;
    if (1.0f < f) {
        return 1.0f;
    }
    return f;
}
