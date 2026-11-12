#include "common.h"

s32 func_001C14A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

/* 0x001C16A0(a0, a1, a2, a3, vecA, vecB): r = func_001C14A0(a0, a1, (s16)a2, (s16)a3, 4). When r != 0: the words
 * r+0xC..0x14 = vecA[0..2] and r+0x18..0x20 = vecB[0..2] (f32). Returns r. */
s32 func_001C16A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    f32 *a = (f32 *)arg4;
    f32 *b = (f32 *)arg5;
    u8 *r;

    r = (u8 *)func_001C14A0(arg0, arg1, (s16)arg2, (s16)arg3, 4);
    if (r != 0) {
        *(f32 *)(r + 0xC) = a[0];
        *(f32 *)(r + 0x10) = a[1];
        *(f32 *)(r + 0x14) = a[2];
        *(f32 *)(r + 0x18) = b[0];
        *(f32 *)(r + 0x1C) = b[1];
        *(f32 *)(r + 0x20) = b[2];
    }
    return (s32)r;
}
