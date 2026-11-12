#include "m2c_macros.h"

void func_001EA610(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *dst = (u8 *)arg0 + (arg2 << 5);
    u8 *src2 = (u8 *)arg1 + arg2 * 0x10;
    u8 *src3 = (u8 *)arg1 + arg3 * 0x10;

    *(s64 *)(dst + 0x130) = *(s64 *)(src2 + 0);
    *(s64 *)(dst + 0x138) = *(s64 *)(src2 + 8);
    *(s64 *)(dst + 0x140) = *(s64 *)(src3 + 0);
    *(s64 *)(dst + 0x148) = *(s64 *)(src3 + 8);
}
