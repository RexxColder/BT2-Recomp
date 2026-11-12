#include "common.h"

/* 0x002D2FC8: table = *(arg0 + arg1 * 68 + 0x1F3C); if it is not null, return the function pointer at
 * table[arg2] called as f(arg0, arg3, arg4, 0); otherwise 0. */
s32 func_002D2FC8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 *table = *(u8 **)((u8 *)arg0 + arg1 * 68 + 0x1F3C);
    s32 v0 = 0;

    if (table != NULL) {
        s32 (*fn)(s32, s32, s32, s32) = (s32 (*)(s32, s32, s32, s32))(u32)*(s32 *)(table + arg2 * 4);

        v0 = fn(arg0, arg3, arg4, 0);
    }
    return v0;
}
