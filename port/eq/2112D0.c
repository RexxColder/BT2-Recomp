#include "common.h"

s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);

s32 func_002112D0(s32 arg0) {
    s32 r = func_00211310(arg0, 1, 0x100);

    return (r != 0) ? (arg0 + 0x6D0) : (arg0 + 0x5F0);
}
