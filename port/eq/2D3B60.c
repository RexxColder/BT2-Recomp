#include "common.h"

s32 func_002C3210(s32 arg0);
s32 func_002C2FF0(s32 arg0, s32 arg1);
s32 func_002D3FD8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_002C00A8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_002D3B60(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 *s0;
    s32 s2;
    s32 tmp;

    s0 = (u8 *)arg0 + 0x2150;
    if (func_002C3210(arg0) != 0) {
        return func_002C2FF0(0, 0xFF000192);
    }
    s2 = *(s32 *)(s0 + 0x10);
    if (s2 == 8) {
        return func_002C2FF0(arg0, 0xFF000602);
    }
    tmp = *(s32 *)(s0 + 0x8) + arg1 * 0x10 + 4;
    func_002D3FD8(tmp, arg2, 0, arg3, arg4);
    func_002C00A8(arg0, s2, arg1, tmp);
    return 0;
}
