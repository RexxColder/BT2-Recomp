#include "common.h"

s32 func_00211310(void *a0, s32 a1, s32 a2);
s32 func_0023F420(void *a0);

s32 func_00218128(void *arg0, s32 arg1) {
    s32 mask;

    mask = 0;
    if (func_00211310(arg0, 0, 0x800) == 0) {
        return 0;
    }
    if ((u32)arg1 < 9) {
        mask = (s32)((u32)1 << (23 + arg1));
    }
    return (func_0023F420(arg0) & mask) != 0;
}
