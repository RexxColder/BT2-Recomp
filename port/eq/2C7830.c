#include "common.h"

s64 __divdi3(s64 arg0, s64 arg1);

s64 func_002C7830(s32 arg0, s32 arg1) {
    s64 n = (s64)arg0 * 0x055D4A80;

    return __divdi3(n, arg1);
}
