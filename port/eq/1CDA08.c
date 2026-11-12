#include "common.h"

s32 Rand_IntRange(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

s32 func_001CDA08(u8 *arg0, s32 unused1, s32 arg2, s32 arg3) {
    u8 *p;
    s32 r;

    p = *(u8 **)(arg0 + 0x124);
    r = Rand_IntRange(0, 9, arg2, arg3);
    if (p == NULL) {
        return r;
    }
    while (p != NULL) {
        if (*(s32 *)p == r) {
            return -1;
        }
        p = *(u8 **)(p + 0x8);
    }
    return r;
}
