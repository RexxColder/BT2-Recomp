#include "m2c_macros.h"

s64 __divdi3(s64 arg0, s64 arg1);
extern s64 D_003475D8 __attribute__((section(".data")));

s64 func_002D8B10(s64 arg0) {
    return __divdi3(arg0 * 0xF4240, D_003475D8);
}
