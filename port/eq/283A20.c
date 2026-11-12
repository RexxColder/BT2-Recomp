#include "common.h"

extern void *Dma_BeginDirect();
extern void Dma_EndDirect(s32 arg0);
extern f32 D_003870C8;
extern f32 D_003870CC;

/* Screen-quad GIF packet: header, four 3-word vertex blocks, then two corner blocks whose
   x/y are converted from fixed point (optionally doubled / biased by -1). */
void func_00283A20(s32 *v, s32 a1, s32 a2, u32 a3, s64 mode) {
    u64 *p = (u64 *)Dma_BeginDirect(v, a1);
    s32 flip = a1 & 0xFF;
    s32 i;
    f32 fx;
    f32 fy;
    u32 xbits;
    u32 ybits;

    p[0] = 0x1000000000008001ULL;
    p[1] = 14;
    p += 2;
    if (mode == 1) {
        p[0] = 88;
    } else if (mode < 2) {
        p[0] = 84;
    } else if (mode == 2) {
        p[0] = 82;
    } else {
        p[0] = 84;
    }
    p[1] = 0x42;
    p += 2;
    p[0] = 0x4400000000008001ULL;
    p[1] = 0x5510;
    p += 2;
    p[0] = 0x246;
    p[1] = 0x3F80000000000000ULL;
    p += 2;
    p[1] = 0x8E009000ULL;
    p[0] = 0x72007000ULL;
    p += 2;
    p[0] = 0x6400000000008004ULL;
    p[1] = 0x535310;
    p += 2;
    {
        s32 *q = v;
        for (i = 3; i >= 0; i--) {
            p[0] = 0x356;
            p[1] = 0x3F80000020808080ULL;
            p += 2;
            p[0] = 0;
            p[1] = (u64)(s64)q[0] | ((u64)(s64)q[1] << 16);
            q += 4;
            p += 2;
            p[0] = 0x0FF00FF0;
            p[1] = (u64)(s64)v[16] | ((u64)(s64)v[17] << 16);
            p += 2;
        }
    }
    p[1] = 0x525210;
    p[0] = 0x6400000000008001ULL;
    p += 2;
    p[0] = 0x56;
    p[1] = (u64)a3 | 0x3F80000000000000ULL;
    p += 2;

    fy = (f32)(v[21] - 0x7200) * D_003870C8 * 0.0625f;
    fx = (f32)(v[20] - 0x7000) * 0.001953125f * 0.0625f;
    if (flip) {
        fx = fx + fx;
        if (a2) {
            fx = fx - 1.0f;
        }
    }
    xbits = *(u32 *)&fx;
    ybits = *(u32 *)&fy;
    p[0] = (u64)xbits | ((u64)ybits << 32);
    p[1] = (u64)(s64)v[0] | ((u64)(s64)v[1] << 16);
    p += 2;

    fy = (f32)(v[25] - 0x7200) * D_003870CC * 0.0625f;
    fx = (f32)(v[24] - 0x7000) * 0.001953125f * 0.0625f;
    if (flip) {
        fx = fx + fx;
        if (a2) {
            fx = fx - 1.0f;
        }
    }
    xbits = *(u32 *)&fx;
    ybits = *(u32 *)&fy;
    p[0] = (u64)xbits | ((u64)ybits << 32);
    p[1] = (u64)(s64)v[12] | ((u64)(s64)v[13] << 16);
    p += 2;
    Dma_EndDirect((s32)p);
}
