#include "common.h"

s32 func_002DCE50(u8 *arg0) {
    s32 v;

    v = (((((arg0[0] << 8) | arg0[1]) << 8) | arg0[2]) << 8) | arg0[3];
    if (v == 0x100) {
        return 4;
    }
    if (v == 0x101) {
        return 3;
    }
    if ((u32)(v - 0x102) < 0xAEU) {
        return 1;
    }
    if (v == 0x1B2) {
        return 0x20;
    }
    if (v == 0x1B3) {
        return 0x40;
    }
    if (v == 0x1B5) {
        return 0x10;
    }
    if (v == 0x1B7) {
        return 0x80;
    }
    if (v == 0x1B8) {
        return 8;
    }
    return 0;
}
