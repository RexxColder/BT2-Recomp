#include "common.h"

s32 func_002D0380(u8 *arg0) {
    u8 *p1 = arg0 + 0x1F30;
    s32 v = *(s32 *)(p1 + 0x14);
    s32 w = *(s32 *)(arg0 + 116 * v + 0x1360);
    s32 r = *(s32 *)(p1 + 68 * w + 0x20);

    if (r < 0) {
        return -1;
    }
    return r;
}
