#include "common.h"

s32 func_001279C0(u8 *arg0) {
    u8 *p;
    u8 *q;

    if (*(s32 *)(arg0 + 0x68) != 0) {
        return 0;
    }
    p = *(u8 **)(arg0 + 0x64);
    if (p == NULL) {
        return 0;
    }
    q = *(u8 **)(p + 0x20);
    return (*(s32 *)(q + 0x2C) & 0x8) ? 1 : 0;
}
