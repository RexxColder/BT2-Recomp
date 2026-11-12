#include "common.h"

/* 0x0023FC18: f = *(f32 *)(*(a0 + 0x1530)->+0x958 ->+0x94) * 30.0f; return 30000 / (s32)f. */
s32 func_0023FC18(s32 a0) {
    u8 *a1;
    u8 *v1;
    f32 f;
    s32 q;

    a1 = *(u8 **)(a0 + 0x1530);
    v1 = *(u8 **)(a1 + 0x958);
    f = *(f32 *)(v1 + 0x94);
    q = (s32)(f * 30.0f);
    return 30000 / q;
}
