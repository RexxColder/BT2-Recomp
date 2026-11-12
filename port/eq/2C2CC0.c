#include "common.h"

s32 func_002C2CC0(s32 arg0, s32 (*arg1)(s32, s32)) {
    s32 sp[4];
    s32 r;

    r = arg1(arg0, (s32)sp);
    return (r != 0) ? sp[0] : -1;
}
