#include "common.h"

extern u8 *gSndRpc;

/* 0x002976A0(a0, a1, a2, a3, t0): with n = byte gSndRpc+0x68 below 0x20, stores the bytes a0, a1, a2, a3 at
 * +0x69+n, +0x89+n, +0xA9+n, +0xC9+n, the halfword t0 at +0xEA+2n (low byte first), and sets the byte +0x68 to n + 1. */
void func_002976A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u8 *g = gSndRpc;
    u32 n = g[0x68];

    if (n < 0x20) {
        g[0x69 + n] = (u8)arg0;
        g[0x89 + n] = (u8)arg1;
        g[0xA9 + n] = (u8)arg2;
        g[0xC9 + n] = (u8)arg3;
        g[0xEA + 2 * n] = (u8)arg4;
        g[0xEB + 2 * n] = (u8)((u32)arg4 >> 8);
        g[0x68] = (u8)(n + 1);
    }
}
