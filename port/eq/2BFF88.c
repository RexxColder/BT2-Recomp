#include "common.h"

void func_002BFFF8(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3);
s32 func_002C2FF0(u8 *arg0, s32 arg1, u8 *arg2, s32 arg3);

s32 func_002BFF88(u8 *arg0, u8 *arg1, s32 arg2) {
    u8 *base = arg0 + 0x1310 + arg2 * 0x74;

    if (*(s32 *)base != 4) {
        return func_002C2FF0(arg0, (s32)0xFF000409, base, 4);
    }
    func_002BFFF8(base + 0x10, arg1, base, *(s32 *)(arg1 + 4) != 0);
    return 0;
}
