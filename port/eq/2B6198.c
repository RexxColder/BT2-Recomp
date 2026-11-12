#include "common.h"

s32 func_002B7CB8(s32 arg0);

s32 func_002B6198(s32 arg0, s32 arg1) {
    u8 *base = (u8 *)func_002B7CB8(arg0);

    return *(s32 *)(base + arg1 * 0xF0 + 0x2528);
}
