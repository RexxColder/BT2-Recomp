#include "common.h"

u8 *Dma_BeginDirect(s64 arg0, s32 arg1, s64 arg2, s64 arg3);
void Dma_EndDirect(u8 *arg0, s64 arg1);

/* 16-byte copy (lq/sq pair). */
#define COPY16(d, s)                                              \
    do {                                                          \
        ((s64 *)(d))[0] = ((s64 *)(s))[0];                        \
        ((s64 *)(d))[1] = ((s64 *)(s))[1];                        \
    } while (0)

/* cvt.w.s: truncates toward zero. */
/* cvt.w.s truncates toward zero (saturating): plain cast */
#define CVT_W_S(dst, fsrc) do { \
    (dst) = (s32)(fsrc); \
} while (0)

void func_00262AA8(u8 *arg0, u8 *arg1, u8 *arg2) {
    u8 *t6;
    u8 *s3;
    u8 *s4;
    u8 *s0;
    u8 *p;
    u8 *tag;
    u8 *e;
    u8 *r0;
    u8 *r1;
    u8 *r2;
    s32 spw[4] __attribute__((aligned(16)));
    s32 nN;
    s32 cnt;
    s32 t4;
    s32 blk;
    s32 hi;
    s32 i0;
    s32 i1;
    s32 i2;
    s32 t3;
    s32 t0;
    s32 t4v;
    s32 lo2;
    s32 a1x;
    s32 lo3;
    s32 v1x;
    s32 v0x;
    s64 A2;
    s64 A3;
    s64 mask;
    s64 a0arg;
    s64 a2a;
    s64 a3a;
    s64 s1;
    s64 s2;
    s64 s2p;
    s64 a1out;
    s64 a3out;
    s64 tv;
    s64 t9;

    t6 = *(u8 **)(arg0 + 0x44);
    if (*(s32 *)(t6 + 0x8) == 0) {
        return;
    }
    s3 = t6 + *(s32 *)(t6 + 0x8);
    s4 = t6 + *(s32 *)(s3 + 0xC);
    s0 = t6 + *(s32 *)(s3 + 0x8);
    nN = *(s32 *)(s3 + 0x4);

    A2 = *(s64 *)(s4 + 0x10);
    A3 = *(s64 *)(s4 + 0x18);
    mask = ((s64)0xFFF8001F << 32) | 0xFFFFFFFFLL;
    a2a = A2 & (s64)-0x4000;
    a3a = A3 & (s64)-0x4000;

    t3 = *(s32 *)(arg1 + 0xBC);
    t0 = *(s32 *)(arg1 + 0xC0);
    t4v = *(s32 *)(arg1 + 0xCC);

    lo2 = (s32)(A2 & 0x3FFF);
    a1x = lo2 + t3;
    lo3 = (s32)(A3 & 0x3FFF) + 0x3D40;
    v1x = (s32)((A2 >> 37) & 0x3FFF) + t0;
    v0x = (s32)((A3 >> 37) & 0x3FFF) + t4v;

    a0arg = (a3a | (s64)lo3) & mask;
    s2p = a2a | (s64)a1x;
    s1 = a0arg | ((s64)v0x << 37);
    s2 = (s2p & mask) | ((s64)v1x << 37);

    p = Dma_BeginDirect(a0arg, *(s32 *)(s3 + 0x8), a2a, a3a);

    a3out = s1 | ((s64)0x8000 << 19);
    a1out = s2 | ((s64)0x8000 << 19);

    CVT_W_S(spw[0], *(f32 *)(arg2 + 0x20));
    CVT_W_S(spw[1], *(f32 *)(arg2 + 0x24));
    CVT_W_S(spw[2], *(f32 *)(arg2 + 0x28));
    spw[3] = 0x80;

    t9 = ((s64)0x10000000 << 32) | 2;

    for (blk = 0; blk < 2; blk++) {
        /* Header: 3 quadwords; the GIF tag sits at p+0x30 and is written after the loop. */
        *(s64 *)(p + 0x00) = t9;
        *(s64 *)(p + 0x08) = 0xE;
        p += 0x10;
        *(s64 *)(p + 0x00) = 0;
        *(s64 *)(p + 0x08) = 0x3F;
        p += 0x10;
        if (blk == 0) {
            *(s64 *)(p + 0x00) = a1out;
            *(s64 *)(p + 0x08) = 6;
        } else {
            *(s64 *)(p + 0x00) = a3out;
            *(s64 *)(p + 0x08) = 7;
        }
        p += 0x10;
        tag = p;
        p += 0x10;

        hi = (blk == 0) ? 0x50 : 0x60;
        t4 = 0;
        cnt = 0;
        e = s4;
        if (nN > 0) {
            do {
                i0 = *(s32 *)(e + 0x0);
                i1 = *(s32 *)(e + 0x4);
                i2 = *(s32 *)(e + 0x8);
                r0 = s0 + i0 * 0x70;
                r1 = s0 + i1 * 0x70;
                r2 = s0 + i2 * 0x70;
                cnt++;
                if (!(*(s32 *)(r0 + 0x3C) & 0x8000) && !(*(s32 *)(r1 + 0x3C) & 0x8000) &&
                    !(*(s32 *)(r2 + 0x3C) & 0x8000)) {
                    t4++;
                    COPY16(p, r0 + hi);
                    p += 0x10;
                    COPY16(p, spw);
                    p += 0x10;
                    COPY16(p, r0 + 0x30);
                    p += 0x10;
                    COPY16(p, r1 + hi);
                    p += 0x10;
                    COPY16(p, spw);
                    p += 0x10;
                    COPY16(p, r1 + 0x30);
                    p += 0x10;
                    COPY16(p, r2 + hi);
                    p += 0x10;
                    COPY16(p, spw);
                    p += 0x10;
                    COPY16(p, r2 + 0x30);
                    p += 0x10;
                }
                e += 0x20;
            } while (cnt < nN);
        }

        if (blk == 0) {
            tv = (s64)(3 * t4) | 0x8000 | ((s64)0xC0B7 << 46);
        } else {
            tv = (s64)(3 * t4) | 0x8000 | ((s64)0xC4B7 << 46);
        }
        *(s64 *)(tag + 0x8) = 0x412;
        *(s64 *)(tag + 0x0) = tv;
    }

    Dma_EndDirect(p, a1out);
}
