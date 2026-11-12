#include "common.h"

s32 func_002CF3D8(u8 *arg0, u8 *arg1, s32 *arg2) {
    s32 a1;
    s32 count;
    s32 next;
    s32 v;
    u8 *p;

    if (*(s32 *)(arg0 + 0x8) == *(s32 *)(arg0 + 0x4)) {
        *arg2 = 1;
        return -1;
    }
    a1 = *(s32 *)(arg0 + 0xC);
    p = *(u8 **)(arg0 + 0x0) + a1 * 0x10;
    *(s64 *)(p + 0x0) = *(s64 *)(arg1 + 0x0);
    next = a1 + 1;
    *(s64 *)(p + 0x8) = *(s64 *)(arg1 + 0x8);
    count = *(s32 *)(arg0 + 0x4);
    if (next >= count) {
        next = (a1 - count) + 1;
    }
    *(s32 *)(arg0 + 0xC) = next;
    v = *(s32 *)(arg0 + 0x8) + 1;
    *(s32 *)(arg0 + 0x8) = v;
    if (v >= count) {
        *arg2 = 1;
    } else {
        *arg2 = 0;
    }
    return 0;
}
