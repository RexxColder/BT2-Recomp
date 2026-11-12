#include "common.h"

s64 __divdi3(s64, s64);
extern s64 D_003475D8 __attribute__((section(".data")));

s64 func_002D8B50(s64 arg0) {
    return __divdi3(arg0 * 1000, D_003475D8);
}
