#include "common.h"

s32 func_0011EC10(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00126058(s32 arg0, s32 arg1, s32 arg2);

s32 func_0011ECA8(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u16 flags;

    flags = (u16)arg3;
    if (arg2 >= 0x2710) {
        return func_0011EC10(arg0, arg1, arg2 - 0x2710, flags);
    }
    if (arg1 != arg2) {
        return 0;
    }
    if (func_00126058(arg0, 2, 2) != 0) {
        return 1;
    }
    return (flags & 0x10) != 0;
}
