#include "common.h"

s32 func_002E9808(void *arg0, s32 arg1, void *arg2, void *arg3);

/* 0x002E9A80: parses a big-endian header at arg0 (magic 0x8000 at +0, fields at +2, +off...); returns 0, -1 or -2
 * or the nonzero result of func_002E9808. */
s32 func_002E9A80(void *arg0, s32 arg1, s32 *arg2, u16 *arg3, u16 *arg4, u32 *arg5, u32 *arg6, u32 *arg7, u32 *arg8) {
    u8 b0;
    u8 b1;
    u8 *d;
    s32 lim;
    s32 off;
    s32 v;
    s32 h2;
    s32 x;
    s32 y;
    s32 r;

    *arg3 = 0;
    r = func_002E9808(arg0, arg1, &b0, &b1);
    if (r != 0) {
        return r;
    }

    d = (u8 *)arg0;
    lim = (b0 == 4) ? 0x3C : 0x30;
    if (arg1 < lim) {
        return -1;
    }
    v = (d[0] << 8) | d[1];
    if (v != 0x8000) {
        return -2;
    }
    h2 = (s16)((d[2] << 8) | d[3]);
    if (h2 < lim - 4) {
        return -1;
    }

    off = (b0 == 4) ? 0x20 : 0x14;
    x = (s16)((d[off] << 8) | d[off + 1]);
    *arg2 = x;
    y = (d[off + 2] << 8) | d[off + 3];
    *arg3 = (u16)y;
    if ((s16)y != 1) {
        return -2;
    }

    *arg4 = (u16)((d[off + 6] << 8) | d[off + 7]);
    *arg5 = ((u32)d[off + 8] << 24) | ((u32)d[off + 9] << 16) | ((u32)d[off + 10] << 8) | (u32)d[off + 11];
    *arg6 = ((u32)d[off + 12] << 24) | ((u32)d[off + 13] << 16) | ((u32)d[off + 14] << 8) | (u32)d[off + 15];
    *arg7 = ((u32)d[off + 16] << 24) | ((u32)d[off + 17] << 16) | ((u32)d[off + 18] << 8) | (u32)d[off + 19];
    *arg8 = ((u32)d[off + 20] << 24) | ((u32)d[off + 21] << 16) | ((u32)d[off + 22] << 8) | (u32)d[off + 23];
    return 0;
}
