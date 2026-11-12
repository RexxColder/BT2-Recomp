#include "common.h"

s64 __divdi3(s64 arg0, s64 arg1);

s64 func_002E0A98(s32 arg0, s32 arg1, s32 arg2) {
    s64 prod;

    prod = (s64)arg0 * (s64)arg1;
    if (arg2 == 0) {
        return ((arg0 ^ arg1) < 0) ? (s64)(-2147483647 - 1) : (s64)0x7FFFFFFF;
    }
    return (s64)(s32)__divdi3(prod, (s64)arg2);
}
