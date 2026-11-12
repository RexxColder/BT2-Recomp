#include "m2c_macros.h"

void func_002115B0(s32 arg0, s32 arg1, s32 arg2) {
    s32 *temp_a0;
    s32 off;

    off = (arg1 * 4) + 0x2B0;
    temp_a0 = (s32 *) (arg0 + off);
    *temp_a0 ^= arg2;
}
