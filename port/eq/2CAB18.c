#include "common.h"

s32 func_002CAB18(u8 *arg0, s32 arg1) {
    s32 k;
    s32 base = *(s32 *)(arg0 + 0x1FC0);

    for (k = 0; k < 16; k++) {
        if ((s32)(arg0 + 0x16B0 + 0x8 + 0x88 * k) == arg1) {
            return base + 0x180 + 0xF0 * k;
        }
    }
    return 0;
}
