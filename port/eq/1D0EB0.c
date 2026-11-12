#include "common.h"

extern u8 *D_00387E9C;

/* 0x001D0EB0(i, mode): 0 when the table is not in use (byte +0x1491 of the block); otherwise 1, after
 * updating entry i (0x14 bytes at +0x1400): mode 0 claims it (state 2: word 0 = i, word 4 = 0) unless it is
 * already 2; mode 1 releases it (state 0, word 4 = 0) when it is 2; any other mode only returns 1. */
s32 func_001D0EB0(s32 arg0, s32 arg1) {
    u8 *g = D_00387E9C;
    u8 *e;
    s32 mode = arg1 & 0xFF;

    if (g[0x1491] == 0) {
        return 0;
    }
    e = *(u8 **)(g + 0x1400) + arg0 * 0x14;
    if (mode == 0) {
        if (e[8] == 2) {
            return 1;
        }
        e[8] = 2;
        *(s32 *)e = arg0;
        *(s32 *)(e + 4) = 0;
        return 1;
    }
    if (mode == 1) {
        if (e[8] == 2) {
            e[8] = 0;
            *(s32 *)(e + 4) = 0;
        }
        return 1;
    }
    return 1;
}
