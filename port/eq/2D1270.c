#include "common.h"

s64 __muldi3(s64 a, s64 b);
s64 __divdi3(s64 a, s64 b);
extern s64 D_00346E70 __attribute__((section(".data")));
extern s32 D_00346E78 __attribute__((section(".data")));

s64 func_002D1270(u8 *arg0, s64 arg1) {
    s64 s0;
    s64 r;
    s64 ret;

    ret = -1;
    s0 = *(s64 *)(arg0 + 0x158);
    if (s0 >= 0) {
        r = (s32)__divdi3(__muldi3(s0, arg1), 0x15F90);
        D_00346E70 = s0;
        ret = r;
        D_00346E78 = (s32)r;
    }
    return ret;
}
