#include "common.h"

s32 func_002DA360(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s64 p1 = (s64)arg0 * arg3;
    s64 p2 = (s64)arg2 * arg1;

    return p2 >= p1;
}
