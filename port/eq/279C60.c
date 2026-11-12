#include "common.h"

extern u32 D_003B0A84;
u8 *Dma_BeginDirect(u8 *arg0, s32 arg1);
s32 Dma_EndDirect(u8 *arg0);
s32 Tex_Log2Size(s32 arg0);

#define PQ(lo, hi)                      \
    do {                                \
        *(u64 *)s1 = (u64)(lo);         \
        *(u64 *)(s1 + 8) = (u64)(hi);   \
        s1 += 0x10;                     \
    } while (0)

/* 0x00279C60: build a GIF packet that blits a 256x(256>>a1) texture strip by strip
 * (two passes) and the 5-quad sprite rows at the end; returns Dma_EndDirect(end). */
s32 func_00279C60(u8 *arg0, s32 arg1) {
    u8 sp[0x70];
    u8 *s1;
    s32 s2, s7, s3, s4, s6, a3, i, t5;
    u64 s0, v, fp, r;
    u8 *sc;
    s32 cnt, strip, n;

    arg1 &= 0xFF;
    s2 = 0;
    s7 = 0;
    if (arg1 != 0) {
        s7 = 0x80;
        s2 = 1;
        if (*(s32 *)(arg0 + 0x90) == 0) {
            s7 = 0;
        }
    }
    s1 = Dma_BeginDirect(arg0, arg1);
    PQ(0x1000000000000009ULL, 0xE);
    PQ(0x1310000E0ULL, 0x4E);
    PQ(0x20170ULL, 0x4C);
    PQ(0x00007C0000007C00ULL, 0x18);
    PQ(0x007F0000007F0000ULL, 0x40);
    PQ(0x3FC003FC00AULL, 8);
    PQ(0, 0x3F);
    s0 = (u64)(s64)Tex_Log2Size(0x100);
    v = (u64)(s64)Tex_Log2Size(0x100);
    PQ((s0 << 26) | (v << 30) | 0x400012A00ULL, 6);
    PQ(0x116, 0);
    r = (u64)(*(f32 *)(arg0 + 0x80) * *(f32 *)(arg0 + 0x84));
    PQ((r << 24) | 0x3F80000000808080ULL, 1);
    a3 = (0x100 >> s2) >> 5;
    PQ((u64)(s64)a3 | 0x4400000000000000ULL, 0x5353);
    {
        s32 t1 = (0x80 / a3) * 16;
        s32 t0 = (s7 << 4) + 0x200;
        s32 a2 = t1 + 0x7C00;
        s32 t2 = 0x7C00;
        s32 a1 = s7;
        s32 t3 = 0;
        if (a3 > 0) {
            do {
                PQ((u64)(s64)(a1 << 4), (u64)(s64)t2 | 0x7C000000ULL);
                a1 += 0x20;
                t2 += t1;
                t3++;
                PQ((u64)(s64)t0 | 0x10000000ULL, (u64)(s64)a2 | 0x84000000ULL);
                t0 += 0x200;
                a2 += t1;
            } while (t3 < a3);
        }
    }
    s3 = 0x100 >> s2;
    PQ(0x1000000000000001ULL, 0xE);
    PQ(0xFF00000000020170ULL, 0x4C);
    sc = arg0 + 0xD0;
    s2 = s3 / s3;
    s4 = 0x80 / s2;
    fp = (u64)(s64)s2 | 0x4400000000000000ULL;
    s6 = 1;
    do {
        s32 a1, v1, a0, a2, t1;
        PQ(0x2400000000008001ULL, 0x10);
        *(u64 *)s1 = 0x156;
        r = (u64)*(f32 *)(sc - 4);
        *(u64 *)(s1 + 8) = (r << 24) | 0x3F80000000808080ULL;
        s1 += 0x10;
        *(u64 *)(s1 + 8) = 0x5353;
        *(u64 *)s1 = fp;
        t5 = 0;
        a3 = (s32) * (f32 *)(sc - 0x20);
        v1 = (s32) * (f32 *)(sc - 0x1C);
        a1 = (s32) * (f32 *)sc;
        s1 += 0x10;
        if (s2 > 0) {
            s32 v0 = ((v1 + a1 + 0x840) << 4);
            u64 t4, t3;
            s32 a3b, a1b, a2b, t0, t2;
            v1 = ((v1 - a1) << 4) + 0x7C00;
            a0 = (s4 + a1 + a3) << 4;
            a1b = ((s3 + s7) << 4) + 8;
            a2b = ((a3 - a1) << 4) + 0x7C00;
            t4 = (u64)(s64)v1 << 16;
            t3 = (u64)(s64)v0 << 16;
            t1 = a0 + 0x7C00;
            a3b = (s7 << 4) + 8;
            t2 = s4 << 4;
            t0 = s3 << 4;
            do {
                PQ((u64)(s64)a3b | 0x80000ULL, (u64)(s64)a2b | t4);
                a3b += t0;
                a2b += t2;
                t5++;
                PQ((u64)(s64)a1b | 0x10080000ULL, (u64)(s64)t1 | t3);
                a1b += t0;
                t1 += t2;
            } while (t5 < s2);
        }
        s6--;
        sc += 0x30;
    } while (s6 >= 0);

    PQ(0x1000000000000008ULL, 0xE);
    v = (D_003B0A84 & 1) ? 0xFF00000000080000ULL : 0xFF00000000080070ULL;
    PQ(v, 0x4C);
    PQ(0x0000720000007000ULL, 0x18);
    PQ(0x44, 0x42);
    PQ(0x3F80000080808080ULL, 1);
    PQ(0, 0x3F);
    PQ(0x5DC00AE00ULL, 6);
    {
        u64 t5v = 0x5DC00AE00ULL;
        u64 t4 = 0xA0000005ULL;
        u64 t3 = 0x8400000000008001ULL;
        s32 a1 = *(s32 *)(arg0 + 0x94);
        s32 a2 = *(s32 *)(arg0 + 0xA0);
        s32 v1 = *(s32 *)(arg0 + 0x98);
        s32 v0 = *(s32 *)(arg0 + 0x9C);
        s32 a0 = *(s32 *)(arg0 + 0x98);
        s32 a1orig = a1;
        u64 q;
        q = (u64)(s64)a1 | ((u64)(s64)(v1 + a2 - 1) << 48) | ((u64)(s64)a0 << 32) | ((u64)(s64)(a1 + v0 - 1) << 16);
        PQ(q, 0x40);
        PQ(0x156, 0);
        {
            s32 vv = *(s32 *)(arg0 + 0x9C);
            s32 w = vv < 0 ? vv + 0x1F : vv;
            s32 g = w >> 5;
            s32 s5v;
            s32 ss2, ss0, ssfp, ss4, hdr;
            f32 f0 = 1.0f;
            a1 = *(s32 *)(arg0 + 0x94);
            s7 = 0x80 / g;
            *(u64 *)&sp[0x20] = 0x156;
            *(u64 *)&sp[0x00] = t4;
            *(u64 *)&sp[0x10] = t3;
            *(u64 *)&sp[0x18] = 0xF4343160ULL;
            *(u64 *)&sp[0x28] = t5v;
            for (i = 0x30; i < 0x70; i++) {
                if (i != 0x20 && i != 0x28) {
                    sp[i] = 0;
                }
            }
            sp[0x33] = 0x80;
            *(f32 *)&sp[0x34] = f0;
            sp[0x30] = 0x80;
            sp[0x31] = 0x80;
            sp[0x32] = 0x80;
            s6 = 0;
            if (g > 0) {
                s3 = g;
                s2 = (a1 << 4) + 0x7000;
                s0 = (a1 << 4) + 0x7200;
                (void)ss2; (void)ss0; (void)ssfp; (void)ss4; (void)hdr; (void)s5v; (void)a1orig;
                do {
                    s32 t1v = s6 + s7;
                    *(u16 *)&sp[0x40] = (u16)s2;
                    *(u16 *)&sp[0x42] = 0x7200;
                    *(u16 *)&sp[0x50] = (u16)s0;
                    s0 += 0x200;
                    *(u16 *)&sp[0x52] = (u16)-0x7200;
                    *(u64 *)&sp[0x40] = *(u64 *)&sp[0x40] & 0xFF000000FFFFFFFFULL;
                    *(u64 *)&sp[0x50] = *(u64 *)&sp[0x50] & 0xFF000000FFFFFFFFULL;
                    *(u16 *)&sp[0x38] = (u16)((s6 << 4) + 8);
                    *(u16 *)&sp[0x48] = (u16)((t1v << 4) + 8);
                    *(u16 *)&sp[0x3A] = 8;
                    *(u16 *)&sp[0x4A] = 0x808;
                    s6 = t1v;
                    s3--;
                    s2 += 0x200;
                    sp[0x47] = 0xFF;
                    sp[0x57] = 0xFF;
                    __builtin_memcpy(s1, &sp[0x10], (u32)*(u16 *)&sp[0] << 4);
                    s1 += (u32)*(u16 *)&sp[0] << 4;
                } while (s3 != 0);
            }
        }
    }
    return Dma_EndDirect(s1);
}
