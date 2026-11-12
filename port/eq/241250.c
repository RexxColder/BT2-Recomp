#include "common.h"

/* 0x00241250: i = func_002411A0(a0, a1); return (s32)(((f32 *)(*(a0->+0x1530) + 0x980 field))[0x48/4 + i] * 30.0f). */
s32 func_002411A0(s32 arg0, s32 arg1);

s32 func_00241250(u8 *a0, s32 a1) {
    s32 i;
    u8 *tbl;
    f32 v;

    i = func_002411A0((s32)a0, a1);
    tbl = *(u8 **)(*(u8 **)(a0 + 0x1530) + 0x980);
    v = *(f32 *)(tbl + i * 4 + 0x48);
    return (s32)(v * 30.0f);
}
