#include "common.h"

s32 func_00241C98(void *arg0, s32 arg1) {
    u8 *base;
    s32 idx;
    f32 t;
    f32 c30;
    s32 r;

    base = *(u8 **)((u8 *)arg0 + 0x1530);
    idx = (arg1 != 0) ? 1 : 0;
    t = *(f32 *)(*(u8 **)(base + 0x984) + idx * 4 + 0x10);
    c30 = 30.0f;
    t = t * c30;
    /* cvt.w.s truncates toward zero (saturating): plain cast */
    r = (s32)t;
    return r;
}
