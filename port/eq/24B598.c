#include "common.h"

extern u8 *D_00387F2C;

/* 0x0024B598: reads the 0x38-byte record arg1 of the table at arg0 and its selector word w (0..9
 * allowed, else 0). Each selector tests one or two flag bytes of the global block D_00387F2C
 * (offsets +0x2C0..+0x2CC) and returns 1 when they are set; selector 0 always returns 1, selector
 * 9 returns 1 only when all 14 bytes at +0x2C0 are non-zero. Returns 0 or 1. */
s32 func_0024B598(u8 *arg0, s32 arg1) {
    s32 w = *(s32 *)(arg0 + arg1 * 0x38);
    u8 *p;
    s32 i;

    if ((u32)w >= 10) {
        return 0;
    }

    p = D_00387F2C;
    switch (w) {
        case 0:
            return 1;
        case 1:
            return p[0x2C0] != 0;
        case 2:
            return p[0x2C1] != 0 && p[0x2C2] != 0;
        case 3:
            return p[0x2C3] != 0;
        case 4:
            return p[0x2C4] != 0 && p[0x2C5] != 0;
        case 5:
            return p[0x2C7] != 0 && p[0x2C8] != 0;
        case 6:
            return p[0x2C9] != 0 && p[0x2CA] != 0;
        case 7:
            return p[0x2CB] != 0;
        case 8:
            return p[0x2CC] != 0;
        case 9:
            for (i = 0; i < 14; i++) {
                if (p[0x2C0 + i] == 0) {
                    return 0;
                }
            }
            return 1;
        default:
            return 0;
    }
}
