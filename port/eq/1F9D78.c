#include "common.h"

s32 func_002113C0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_001F9D78(u8 *arg0, s32 arg1) {
    s32 ret = func_002113C0(arg0, 2, 0x10, 1);
    *(s32 *)(arg0 + 0x8E4) = arg1;
    return ret;
}
