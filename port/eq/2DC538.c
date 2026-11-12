#include "common.h"

s32 func_002DC538(u8 *arg0) {
    s32 v0;
    s32 v1;
    u8 b;

    if (arg0[0] != 0 || arg0[1] != 0 || arg0[2] != 1) {
        return 0;
    }
    b = arg0[3];
    v0 = 0x10000;
    if (b == 0xBA) {
        return v0;
    }
    if (b >= 0xBB) {
        v1 = 0xBB;
        v0 = 0x20000;
    } else {
        v1 = 0xB9;
        v0 = 0x80000;
    }
    if (b != v1) {
        v0 = (b < 0xBC) ? 0 : 0x40000;
    }
    return v0;
}
