#include "common.h"

extern u8 D_00344A10[] __attribute__((section(".data")));

s64 func_002719E0(u32 arg0) {
    u32 i = (arg0 < 6) ? arg0 : 0;
    return *(s64 *)(D_00344A10 + i * 8);
}
