#include "common.h"

/* 0x0026CA00(p, k): cnt = byte p+9; 0 gives NULL. w = the 4 bytes at p+0xA. When cnt - 1 == k the result is p+0xE.
 * Otherwise walks records from offset 0xE: off += w; b = byte at off; off += 1; r = p + off; off += 4; b == 0 gives
 * NULL; w = the 4 bytes at r; when b - 1 == k the result is p + off. */
u8 *func_0026CA00(u8 *arg0, s32 arg1) {
    s32 cnt = arg0[9];
    s32 w;
    s32 off;
    s32 b;
    u8 *r;

    if (cnt == 0) {
        return 0;
    }
    w = (s32)((u32)arg0[0xA] | ((u32)arg0[0xB] << 8) | ((u32)arg0[0xC] << 16) | ((u32)arg0[0xD] << 24));
    if (cnt - 1 == arg1) {
        return arg0 + 0xE;
    }
    off = 0xE;
    for (;;) {
        off += w;
        b = arg0[off];
        off += 1;
        r = arg0 + off;
        off += 4;
        if (b == 0) {
            return 0;
        }
        w = (s32)((u32)r[0] | ((u32)r[1] << 8) | ((u32)r[2] << 16) | ((u32)r[3] << 24));
        if (b - 1 == arg1) {
            return arg0 + off;
        }
    }
}
