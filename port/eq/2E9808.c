#include "common.h"

/* 0x002E9808(buf, size, out1, out2): size < 0x14 gives -1; the u16 at +0 byte-swapped must be 0x8000 (else -2); the
 * value (byte +3 | ((u16 at +2) << 8 & ~0xFF)) as an s16 must be >= 0x10 (else -1). Then out1 = byte +0x12,
 * out2 = byte +0x13 and the result is 0. */
s32 func_002E9808(u8 *arg0, s32 arg1, u8 *arg2, u8 *arg3) {
    u32 x;
    s32 v;

    if (arg1 < 0x14) {
        return -1;
    }
    x = *(u16 *)(arg0 + 0);
    x = ((x >> 8) | (x << 8)) & 0xFFFF;
    if (x != 0x8000) {
        return -2;
    }
    v = (s32)((u32)arg0[3] | (((u32)*(u16 *)(arg0 + 2) << 8) & ~0xFFu));
    if ((s16)v < 0x10) {
        return -1;
    }
    *arg2 = arg0[0x12];
    *arg3 = arg0[0x13];
    return 0;
}
