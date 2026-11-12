#include "common.h"

/* Builds a GS/GIF packet list (16-byte quadwords) at arg0 with 16 vertex-stride slots scaled by farg0.
 * Returns the address just past the last quadword written. */
s32 func_00114890(s32 arg0, f32 farg0) {
    s64 *p = (s64 *)arg0;
    s64 *tag;
    s32 count = 0;
    s32 a0;
    s32 x;
    s32 xl;
    s64 v;
    f32 fx;
    f32 fy;
    s32 yoff = 2048;
    s32 hi = (2048 << 4);
    s32 lo_a = hi + 576;
    s32 lo_b = hi - 576;

    p[0] = 0x1000000000008002LL;
    p[1] = 14;
    p += 2;
    p[0] = 0x41;
    p[1] = 0;
    p += 2;
    p[0] = 0x3F80000080606060LL;
    p[1] = 1;
    p += 2;
    tag = p;
    p += 2;

    /* loop 1: first half of the vertex list, 16-bit x/y from the scaled fixed-point step */
    a0 = -800;
    fx = 0.0f;
    fy = 0.0f;
    x = 2048;
    do {
        if (a0 != 0) {
            fx = (f32)a0;
            count = count + 1;
            fy = fx * 36.0f * farg0;
            x = (s32)fy + 2048;
            v = (s64)(s32)((u32)x << 4);
            p[0] = v | 0x82400000LL;
            p[1] = v | 0x7DC00000LL;
            p += 2;
            a0 = a0 + 200;
        } else {
            a0 = 200;
        }
    } while (a0 < 800);

    /* loop 2: second half, mirrored x offsets lo_a / lo_b */
    a0 = -800;
    do {
        if (a0 != 0) {
            fx = (f32)a0;
            count = count + 1;
            fy = fx * 36.0f * farg0;
            xl = (s32)fy + yoff;
            v = (s64)(s32)((u32)xl << 4);
            v = (s64)((u64)v << 16);
            p[0] = (s64)lo_a | v;
            p[1] = (s64)lo_b | v;
            p += 2;
            a0 = a0 + 200;
        } else {
            a0 = 200;
        }
    } while (a0 < 800);

    tag[0] = (s64)(count | 0x8000) | 0x2400000000000000LL;
    tag[1] = 85;

    p[0] = 0x1000000000008001LL;
    p[1] = 14;
    p += 2;
    p[0] = 0x3F80000080808080LL;
    p[1] = 1;
    p += 2;
    p[0] = 0x2400000000008002LL;
    p[1] = 85;
    p += 2;
    p[0] = 0x7DC08000LL;
    p[1] = 0x82408000LL;
    p += 2;
    p[0] = 0x80007DC0LL;
    p[1] = 0x80008240LL;
    p += 2;
    return (s32)(s64)p;
}
