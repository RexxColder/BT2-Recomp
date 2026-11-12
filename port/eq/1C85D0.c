#include "common.h"

s32 EftTexSet_Keep32(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

extern s32 D_003878AC;

/* a0..a2 are not read by the original: they are kept in the signature so arg3..arg5 land in a3, t0, t1. */
void func_001C85D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    EftTexSet_Keep32(D_003878AC, 1, 0, arg3, arg4, arg5);
}
