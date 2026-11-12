#include "common.h"

s32 func_002C2CF8(s32 arg0, s32 arg1, s32 (*arg2)(s32, s32, s32 *)) {
    s32 sp[4];
    s32 v0 = arg2(arg0, arg1 & 0xFF, sp);

    return (v0 != 0) ? sp[0] : -1;
}
