#include "common.h"

extern u8 *D_003876A0;

/* 0x00101A60: stores six arguments into the record at D_003876A0 + 0xB8 (a3 at +0xC, t0 at +0x10, t1 at +0x14 and +0x1C). */
void func_00101A60(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    u8 *p = D_003876A0 + 0xB8;

    *(s32 *)(p + 0x1C) = arg5;
    *(s32 *)(p + 0x00) = arg0;
    *(s32 *)(p + 0x04) = arg1;
    *(s32 *)(p + 0x08) = arg2;
    *(s32 *)(p + 0x0C) = arg3;
    *(s32 *)(p + 0x10) = arg4;
    *(s32 *)(p + 0x14) = arg5;
}
