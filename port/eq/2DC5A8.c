#include "common.h"

u8 *func_002DC608(s32 arg0, s32 arg1, s32 arg2);

s32 func_002DC5A8(u8 *arg0, s32 arg1) {
    u8 *p;

    p = func_002DC608((s32)arg0, arg1, 0xBA);
    if (p == NULL) {
        return 0;
    }
    p = p + 4;
    if (arg1 - ((s32)p - (s32)arg0) <= 0) {
        return 0;
    }
    return ((u8)p[0] >> 6) == 0;
}
