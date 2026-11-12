#include "common.h"

/* 0x003BCB28: scrambles the 27-byte block at arg0. s4 = big-endian u32 of arg0[0..3] (taken before any change). For
 * k = 2..23: r = s4 % k; the last k bytes arg0[27-k..26] are saved to tmp and written back rotated, byte j becoming
 * tmp[(r + j) % k]. (The asm also mirrors every write into a 27-byte stack copy at sp+0x20 that nothing reads.) */
void func_003BCB28(u8 *arg0) {
    u8 tmp[24];
    u64 s4;
    u64 r;
    s32 k;
    s32 j;
    s32 v;

    s4 = ((u64)arg0[0] << 24) | ((u64)arg0[1] << 16) | ((u64)arg0[2] << 8) | (u64)arg0[3];
    for (k = 2; k < 0x18; k++) {
        r = s4 % (u64)k;
        for (j = 0; j < k; j++) {
            tmp[j] = arg0[27 - k + j];
        }
        for (j = 0; j < k; j++) {
            v = (s32)r + j;
            arg0[27 - k + j] = (v < k) ? tmp[v] : tmp[v - k];
        }
    }
}
