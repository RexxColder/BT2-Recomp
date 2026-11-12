#include "common.h"

s32 func_002C2FF0(s32 arg0, s32 arg1, s32 arg2);
s32 func_002C3210(u8 *arg0);
void func_002CF2C8(s32 arg0, s32 arg1, s32 arg2);

s32 func_002CF240(u8 *arg0, s32 arg1, s32 arg2) {
    if (arg1 == 0) {
        return 0;
    }
    if (arg2 <= 0) {
        return 0;
    }
    if (func_002C3210(arg0) != 0) {
        return func_002C2FF0(0, (s32)0xFF000165, arg2);
    }
    func_002CF2C8((s32)(arg0 + 0x13BC), arg1, arg2);
    return 0;
}
