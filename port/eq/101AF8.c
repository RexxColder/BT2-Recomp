#include "common.h"

extern void *memset(void *dst, s32 c, u32 n);

/* 0x00101AF8: clears the 0x58-byte object and stores the 8 register args at +0, +4, +8, +0xC, +0x10, +0x14, +0x18,
 * stack args at +0x1C..+0x30 (8-byte slots), arg14 (s64) at +0x38, arg15 at +0x44, arg16 at +0x48, arg17 at +0x40. */
void func_00101AF8(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9,
                   s32 arg10, s32 arg11, s32 arg12, s32 arg13, s64 arg14, s32 arg15, s32 arg16, s32 arg17) {
    memset(arg0, 0, 0x58);
    *(s32 *)(arg0 + 0x40) = arg17;
    *(s32 *)(arg0 + 0x04) = arg2;
    *(s32 *)(arg0 + 0x08) = arg3;
    *(s32 *)(arg0 + 0x0C) = arg4;
    *(s32 *)(arg0 + 0x10) = arg5;
    *(s32 *)(arg0 + 0x14) = arg6;
    *(s32 *)(arg0 + 0x18) = arg7;
    *(s32 *)(arg0 + 0x00) = arg1;
    *(s32 *)(arg0 + 0x1C) = arg8;
    *(s32 *)(arg0 + 0x20) = arg9;
    *(s32 *)(arg0 + 0x24) = arg10;
    *(s32 *)(arg0 + 0x28) = arg11;
    *(s32 *)(arg0 + 0x2C) = arg12;
    *(s32 *)(arg0 + 0x30) = arg13;
    *(s64 *)(arg0 + 0x38) = arg14;
    *(s32 *)(arg0 + 0x44) = arg15;
    *(s32 *)(arg0 + 0x48) = arg16;
}
