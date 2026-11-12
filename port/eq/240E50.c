#include "common.h"

/* 0x00240E50: returns (s32)(float at *(*(a0+0x1530)+0x98C) + a1*4 + 0x58) * 30.0f). */
s32 func_00240E50(s32 a0, s32 a1) {
    u8 *v1;
    u8 *v0;
    f32 f;

    v1 = *(u8 **)(a0 + 0x1530);
    v0 = *(u8 **)(v1 + 0x98C);
    f = *(f32 *)(v0 + (a1 << 2) + 0x58);
    return (s32)(f * 30.0f);
}
