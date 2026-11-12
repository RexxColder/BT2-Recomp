#include "common.h"

s32 func_002C3210(u8 *arg0);
s32 func_002C2FF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_002C0EA8(u8 *arg0, s32 arg1);
void func_002C0E78(u8 *arg0, s32 arg1, s32 arg2);

s32 func_002CED10(u8 *arg0, s32 unused1, s32 arg2, s32 arg3, s32 arg4) {
    s32 s0;

    if (func_002C3210(arg0) != 0) {
        return func_002C2FF0(0, 0xFF000135, arg2, arg3, arg4);
    }
    s0 = *(s32 *)(arg0 + 0x1F44);
    if (func_002C0EA8(arg0, s0) != 1) {
        func_002C0E78(arg0, s0, 1);
        *(s32 *)(arg0 + 0x44) = 1;
    }
    return 0;
}
