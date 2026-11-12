#include "common.h"

s32 func_00203C58(u8 *a0, s64 a1);

/* 0x0023FB20: v = *(s32 *)(*(a0->+0x1530)->+0x958 + 0x7C); return func_00203C58(a0, 0x8000) ? 0 : v. */
s32 func_0023FB20(u8 *a0) {
    u8 *p = *(u8 **)(a0 + 0x1530);
    u8 *q = *(u8 **)(p + 0x958);
    s32 v = *(s32 *)(q + 0x7C);
    if (func_00203C58(a0, 0x8000) != 0) {
        v = 0;
    }
    return v;
}
