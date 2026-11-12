#include "common.h"

#define BSWAP16(x) ((u16)((((u16)(x)) >> 8) | (((u16)(x)) << 8)))

s32 func_002E9808(u8 *arg0, s32 arg1, u8 *arg2, u8 *arg3);

s32 func_002E9880(u8 *arg0, s32 arg1, u8 *arg2, u8 *arg3) {
    u8 sp[2];
    s32 v;

    v = func_002E9808(arg0, arg1, sp, sp + 1);
    if (v != 0) {
        return -1;
    }
    if (sp[0] < 4) {
        *(s16 *)(arg3 + 2) = 0;
        *(s16 *)(arg2 + 2) = 0;
        *(s16 *)(arg3 + 0) = 0;
        *(s16 *)(arg2 + 0) = 0;
        return 0;
    }
    if (arg1 < 0x20) {
        return -1;
    }
    if (BSWAP16(*(u16 *)(arg0 + 0)) != 0x8000) {
        return -2;
    }
    if ((s16)(arg0[3] | ((((s32)*(u16 *)(arg0 + 2)) << 8) & ~0xFF)) < 0x1C) {
        return -1;
    }
    *(s16 *)(arg2 + 0) = (s16)BSWAP16(*(u16 *)(arg0 + 0x18));
    *(s16 *)(arg3 + 0) = (s16)BSWAP16(*(u16 *)(arg0 + 0x1A));
    *(s16 *)(arg2 + 2) = (s16)BSWAP16(*(u16 *)(arg0 + 0x1C));
    *(s16 *)(arg3 + 2) = (s16)BSWAP16(*(u16 *)(arg0 + 0x1E));
    return 0;
}
