#include "common.h"

void func_002C5180(u8 *arg0) {
    s32 *p;
    s32 n;
    u64 big;

    big = ((u64)-1) >> 1;
    *(s32 *)(arg0 + 0x28) = 0x7FFFFFFF;
    *(u64 *)(arg0 + 0x18) = big;
    n = 0x43;
    *(s32 *)(arg0 + 0x38) = -1;
    p = (s32 *)(arg0 + 0x14C);
    *(s32 *)(arg0 + 0x0) = 0;
    *(s32 *)(arg0 + 0x4) = 0;
    *(s32 *)(arg0 + 0x8) = 0;
    *(u64 *)(arg0 + 0x10) = big;
    *(s32 *)(arg0 + 0x20) = 0;
    *(s32 *)(arg0 + 0x24) = 0x7FFFFFFF;
    *(s32 *)(arg0 + 0x2C) = -1;
    *(s32 *)(arg0 + 0x30) = -1;
    *(s32 *)(arg0 + 0x34) = -1;
    *(s32 *)(arg0 + 0x3C) = 0;
    do {
        n -= 1;
        *p = 0;
        p -= 1;
    } while (n >= 0);
    *(s32 *)(arg0 + 0x150) = 0;
    *(s32 *)(arg0 + 0x158) = -1;
    *(s32 *)(arg0 + 0x154) = 0;
}
