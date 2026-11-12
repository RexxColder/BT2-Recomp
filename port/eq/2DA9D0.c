#include "common.h"

extern void *memcpy(void *dst, const void *src, u32 n);
s32 func_002DAAF0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

/* 0x002DA9D0: consumes the count in arg2 in steps: while it is at least 4, func_002DAAF0 gives
 * two outputs (consumed amount and a flag word) that advance arg1, add to *arg3 and OR into *arg4.
 * Afterwards, when bit 0x20000 of *arg4 is set, the 32-byte entry at arg0+0x28 is copied to
 * arg0 + 0x48 + 32*k, where k is 0, 1 or 2 from the two words at +0x30 and +0x34. Returns 0. */
s32 func_002DA9D0(u8 *arg0, s32 arg1, s32 arg2, s32 *arg3, s32 *arg4) {
    s32 s0 = arg2;
    s32 s1 = arg1;
    s32 o[2];
    s32 v0;
    s32 a1;
    u8 *a0p;

    for (;;) {
        if (s0 < 4) {
            v0 = *arg4;
            break;
        }
        v0 = func_002DAAF0((s32)arg0, s1, s0, (s32)&o[0], (s32)&o[1]);
        s1 += o[0];
        *arg3 = *arg3 + o[0];
        s0 -= o[0];
        *arg4 = *arg4 | o[1];
        if (v0 == 0) {
            v0 = *arg4;
            break;
        }
    }

    if ((v0 & 0x20000) != 0) {
        a0p = arg0 + 0x28;
        if (*(s32 *)(a0p + 0x8) != 0) {
            a1 = 0;
        } else {
            a1 = (*(s32 *)(a0p + 0xC) == 0) ? 2 : 1;
        }
        memcpy(arg0 + (a1 << 5) + 0x48, a0p, 0x20);
    }
    return 0;
}
