#include "common.h"

s32 func_002B95A8(s32 arg0, s32 arg1) {
    s32 idx;
    s32 *p;

    idx = arg1 - (((arg1 < 0) ? (arg1 + 7) : arg1) >> 3) * 8;
    p = (s32 *)(arg0 + (idx * 0x14) + 0xC0);
    if (p[0] == 1) {
        return p[2];
    }
    return 0;
}
