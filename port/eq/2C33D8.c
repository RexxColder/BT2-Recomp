#include "common.h"

s32 func_002C3210(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0);
s32 func_002C2FF0(s32 a0, s32 a1);

s32 func_002C33D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 *a0;

    if (func_002C3210(arg0, arg1, arg2, arg3, arg4) != 0) {
        /* the later arguments are clobbered by the call above: only the first two are passed on. */
        return func_002C2FF0(0, (s32)0xFF000171);
    }
    if ((u32)(arg1 - 0xBC) < 0x44) {
        a0 = *(u8 **)((u8 *)arg0 + 0x1F7C);
        *(s32 *)(a0 + 0x150) = arg3;
        *(s32 *)(a0 + 4 * arg1 - 0x2B0) = arg2;
        *(s32 *)(a0 + 0x154) = arg4;
    }
    return 0;
}
