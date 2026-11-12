#include "common.h"

/* 0x002DE330: stores arg2 and arg3 at +0 and +4 and arg4 at +8 of record arg1 (12 bytes each) of the array at +0x3BC. */
void func_002DE330(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 *p = arg0 + arg1 * 12 + 0x3BC;

    *(s32 *)(p + 0x8) = arg4;
    *(s32 *)(p + 0x0) = arg2;
    *(s32 *)(p + 0x4) = arg3;
}
