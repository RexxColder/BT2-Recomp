#include "common.h"

s64 func_002A2C98(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 *t0 = *(u8 **)(arg0 + 0x10) + arg1 * 64;
    s64 r = *(s64 *)(t0 + 0x30);

    r |= (s64)(*(s32 *)(t0 + 0x24) + arg3) << 37;
    r |= (s64)(*(s32 *)(t0 + 0x20) + arg2);
    r |= (s64)0x8000 << 19;
    return r;
}
