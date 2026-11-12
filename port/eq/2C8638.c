#include "common.h"

void func_002C8638(void *arg0, s32 arg1, void *arg2, s32 arg3) {
    u8 *p;
    u8 *q;

    p = (u8 *)arg0;
    q = (u8 *)arg2;
    *(s32 *)(p + 0) = *(s32 *)(q + 0);
    *(s32 *)(p + 4) = *(s32 *)(q + 4);
    *(s32 *)(p + 8) = *(s32 *)(q + 8);
    *(s32 *)(p + 0x20) = arg3;
    *(s32 *)(p + 0xC) = *(s32 *)(q + 0xC);
    *(s32 *)(p + 0x14) = *(s32 *)(q + 0x10);
    *(s32 *)(p + 0x10) = arg1;
}
