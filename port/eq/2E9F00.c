#include "common.h"

/* 0x002E9F00: returns -1 when arg1 < 16. Otherwise reads the u16 at +0 and returns -2 unless its bytes swapped
 * equal 0x8001. Then stores (byte at +3 | ((u16 at +2) << 8 & ~0xFF)) + 4 as a u16 at arg2 and returns 0. */
s32 func_002E9F00(u8 *arg0, s32 arg1, u16 *arg2) {
    u32 x;
    u32 y;

    if (arg1 < 0x10) {
        return -1;
    }
    x = *(u16 *)(arg0 + 0);
    y = ((x >> 8) | (x << 8)) & 0xFFFF;
    if (y != 0x8001) {
        return -2;
    }
    y = (u32)*(u16 *)(arg0 + 2) << 8;
    *arg2 = (u16)((arg0[3] | (y & ~0xFFu)) + 4);
    return 0;
}
