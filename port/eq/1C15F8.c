#include "common.h"

s32 func_001C14A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

/* 0x001C15F8: r = func_001C14A0(arg0, arg1, (s16)arg2, (s16)arg3, 2); when r != 0 the byte arg5 goes to r + 0xD and
 * the byte arg4 to r + 0xC. Returns r. */
s32 func_001C15F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 r = func_001C14A0(arg0, arg1, (s16)arg2, (s16)arg3, 2);

    if (r != 0) {
        *(u8 *)((u8 *)r + 0xD) = (u8)arg5;
        *(u8 *)((u8 *)r + 0xC) = (u8)arg4;
    }
    return r;
}
