#include "common.h"

s32 func_002D2FC8(u8 *a0, s32 a1, s32 a2, s32 a3, s32 t0);

s32 func_002C0DA0(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *t1 = arg0 + 0x1310 + arg1 * 0x74;
    s32 a1 = 0;

    if (*(s32 *)(t1 + 4) == 0) {
        a1 = func_002D2FC8(arg0, *(s32 *)(t1 + 0x4C), 0xC, arg2, arg3);
    }
    *(s32 *)(arg0 + 0x44) = 1;
    return a1;
}
