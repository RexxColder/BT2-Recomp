#include "common.h"

extern u8 *D_3876A4 __attribute__((section(".data")));
extern u8 *D_0042311C __attribute__((section(".data")));

/* 0x003CD988: table of timeouts selected by mode (D_3876A4->0x8C: 0,1,2) and the flags word at D_0042311C->0x118
 * (bit 4 and bit 8), then by D_3876A4->0x90 (0..3). Anything else returns 0. */
s32 func_003CD988(void) {
    u8 *g = D_3876A4;
    s32 mode = *(s32 *)(g + 0x8C);
    s32 flags = *(s32 *)(D_0042311C + 0x118);
    s32 v1;
    s32 r = 0;

    if (mode == 1) {
        if (flags & 4) {
            v1 = *(s32 *)(g + 0x90);
            if (v1 == 1) {
                r = 45000;
            } else if (v1 < 2) {
                r = (v1 == 0) ? 15000 : 0;
            } else if (v1 == 2) {
                r = 70000;
            } else if (v1 == 3) {
                r = 120000;
            }
        } else if (flags & 8) {
            v1 = *(s32 *)(g + 0x90);
            if (v1 >= 1 && v1 < 4) {
                r = 1000;
            }
        }
    } else if (mode == 0) {
        if (flags & 4) {
            v1 = *(s32 *)(g + 0x90);
            if (v1 == 1) {
                r = 30000;
            } else if (v1 < 2) {
                r = (v1 == 0) ? 10000 : 0;
            } else if (v1 == 2) {
                r = 50000;
            } else if (v1 == 3) {
                r = 70000;
            }
        } else if (flags & 8) {
            v1 = *(s32 *)(g + 0x90);
            if (v1 == 1) {
                r = 5000;
            } else if (v1 == 2) {
                r = 10000;
            } else if (v1 == 3) {
                r = 15000;
            }
        }
    } else if (mode == 2) {
        if (flags & 4) {
            v1 = *(s32 *)(g + 0x90);
            if (v1 == 1) {
                r = 36000;
            } else if (v1 < 2) {
                r = (v1 == 0) ? 12000 : 0;
            } else if (v1 == 2) {
                r = 60000;
            } else if (v1 == 3) {
                r = 80000;
            }
        } else if (flags & 8) {
            v1 = *(s32 *)(g + 0x90);
            if (v1 == 1) {
                r = 6000;
            } else if (v1 == 2) {
                r = 12000;
            } else if (v1 == 3) {
                r = 18000;
            }
        }
    }
    return r;
}
