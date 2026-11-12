#include "common.h"

s32 func_002B95F8(u8 *arg0, s32 arg1) {
    s32 x = (arg1 < 0) ? arg1 + 7 : arg1;
    s32 r = arg1 - ((x >> 3) << 3);
    u8 *p = arg0 + 20 * r;

    if (*(s32 *)(p + 0xC0) == 1) {
        return *(s32 *)(p + 0xD0);
    }
    return 17;
}
