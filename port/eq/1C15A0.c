#include "common.h"

s32 func_001C14A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

/* 0x001C15A0: r = func_001C14A0(arg0, arg1, (s16)arg2, (s16)arg3, 1); when r != 0, the three floats at arg4 are
 * copied to r + 0xC, +0x10, +0x14. Returns r. */
s32 func_001C15A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 *arg4) {
    s32 r = func_001C14A0(arg0, arg1, (s16)arg2, (s16)arg3, 1);

    if (r != 0) {
        *(f32 *)((u8 *)r + 0xC) = *(f32 *)(arg4 + 0x0);
        *(f32 *)((u8 *)r + 0x10) = *(f32 *)(arg4 + 0x4);
        *(f32 *)((u8 *)r + 0x14) = *(f32 *)(arg4 + 0x8);
    }
    return r;
}
