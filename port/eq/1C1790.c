#include "common.h"

s32 func_001C14A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

/* 0x001C1790: r = func_001C14A0(arg0, arg1, (s16)arg2, (s16)arg3, 6). When r != 0: the word at r+0x14 = arg6
 * (t2), the halfword at r+0xC = (s16)arg4 (t0 sign-extended), the word at r+0x10 = arg5 (t1). Returns r. */
s32 func_001C1790(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 r;

    r = func_001C14A0(arg0, arg1, (s16)arg2, (s16)arg3, 6);
    if (r != 0) {
        *(s32 *)((u8 *)r + 0x14) = arg6;
        *(s16 *)((u8 *)r + 0xC) = (s16)arg4;
        *(s32 *)((u8 *)r + 0x10) = arg5;
    }
    return r;
}
