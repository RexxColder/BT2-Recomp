#include "common.h"

extern s64 D_003475D8 __attribute__((section(".data")));

s64 __divdi3(s64 a, s64 b);

/* a0 (64-bit) is not written before the jal: it is the function's parameter, passed through */
s64 func_002D8B88(s64 arg0) {
    return __divdi3(arg0, D_003475D8);
}
