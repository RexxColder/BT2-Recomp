#include "common.h"

/* 0x002BFD70(p, idx, a, b, c): record r = p + 0x1320 + 0x74 * idx; t = (a + 7 < 0 ? a + 14 : a + 7) >> 3;
 * v = r->+4, divided by b when b >= 2; r->+0x0C = a, +0x10 = b, +8 = c, +0x14 = old r->+0,
 * +0x18 = old r->+0 + v, +0x1C = v / t. */
void func_002BFD70(u8 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 *r = arg0 + 0x1320 + arg1 * 0x74;
    s32 t;
    s32 old0;
    s32 v;

    t = (arg2 + 7 < 0) ? (arg2 + 14) : (arg2 + 7);
    t = t >> 3;
    old0 = *(s32 *)(r + 0);
    v = *(s32 *)(r + 4);
    if (arg3 >= 2) {
        v = v / arg3;
    }
    *(s32 *)(r + 0xC) = arg2;
    *(s32 *)(r + 0x10) = arg3;
    *(s32 *)(r + 0x8) = arg4;
    *(s32 *)(r + 0x14) = old0;
    *(s32 *)(r + 0x18) = old0 + v;
    *(s32 *)(r + 0x1C) = v / t;
}
