#include "common.h"

s64 func_002C10E8(s64 arg0, u64 arg1) {
    s64 lo;
    u64 c;
    s64 hi;
    s64 t;

    lo = (s64)(s32)(u32)arg0;
    c = (arg1 < (u64)lo) ? 1 : 0;
    hi = arg0 >> 32;
    t = hi + (s64)c;
    return (s64)(((u64)t << 32) | (arg1 & 0xFFFFFFFFu));
}
