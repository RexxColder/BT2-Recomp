#include "common.h"

s32 Dma_BeginDirect(void);
s32 Dma_EndDirect(u8 *arg0);
void GfxPostQuad_Set(u8 *a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, s32 a6, s32 a7,
                     s32 a8, s32 a9, s32 a10, s32 a11);

/* 0x0027DE68: builds a GS/DMA packet list (16 qwords of quads plus a
 * fixed header and trailer) at the Dma_BeginDirect buffer. */
s32 func_0027DE68(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1) {
    u8 frame[0x80];
    u8 *s3;
    u8 *s5;
    s64 s0;
    s64 s1;
    s32 s2;
    s32 s4;
    s32 s6;
    s32 v14;
    s32 cnt;
    s32 nx;
    s32 sa3;
    s32 st1;
    s32 st3;

    s4 = a0 & 0xFF;
    s0 = (s32)(t1 + 0x7200);
    s1 = (s32)(t0 + 0x7000);
    s2 = a3;
    s6 = a1;

    s3 = (u8 *)Dma_BeginDirect();
    *(s64 *)(s3 + 0x00) = ((s64)0x10000000 << 32) | 0x800A;
    *(s64 *)(s3 + 0x08) = 14;
    s3 += 0x10;
    *(s64 *)(s3 + 0x00) = 0x30000;
    *(s64 *)(s3 + 0x08) = 71;
    s3 += 0x10;
    *(s64 *)(s3 + 0x00) = 0;
    *(s64 *)(s3 + 0x08) = 70;
    s3 += 0x10;
    *(s64 *)(s3 + 0x00) = (s64)s2;
    *(s64 *)(s3 + 0x08) = 66;
    s3 += 0x10;
    *(s64 *)(s3 + 0x00) = 0;
    *(s64 *)(s3 + 0x08) = 63;
    s3 += 0x10;
    *(s64 *)(s3 + 0x00) = 0x8000;
    *(s64 *)(s3 + 0x08) = 59;
    s3 += 0x10;
    *(s64 *)(s3 + 0x00) = s1 | ((s64)s0 << 32);
    *(s64 *)(s3 + 0x08) = 24;
    s3 += 0x10;
    s2 = 0;
    s1 = 0;
    if (s4 != 0) {
        *(s64 *)(s3 + 0x00) = 0x60;
        *(s64 *)(s3 + 0x08) = 0x14;
    } else {
        *(s64 *)(s3 + 0x00) = 0;
        *(s64 *)(s3 + 0x08) = 0x14;
    }
    s3 += 0x10;

    *(s64 *)(s3 + 0x00) = (u32)(s6 | 0x25B20000) | ((s64)a2 << 37) | 0x2000000E40000000LL;
    *(s64 *)(s3 + 0x08) = 6;
    s3 += 0x10;
    *(s64 *)(s3 + 0x00) = 0x156;
    *(s64 *)(s3 + 0x08) = 0;
    s3 += 0x10;
    s6 = 0x1C00000;
    *(s64 *)(s3 + 0x00) = 0x3F80000080808080LL;
    *(s64 *)(s3 + 0x08) = 1;
    s3 += 0x10;
    s5 = s3;
    s3 += 0x10;

    v14 = 0;
    cnt = 15;
    do {
        nx = v14 + 0x20;
        sa3 = (s16)v14;
        st1 = (s16)nx;
        st3 = s2;
        v14 = nx;
        s2 += 0x20;
        cnt -= 1;
        GfxPostQuad_Set(frame + 0x20, 0x700, 0x720, sa3, 0, st1, s6 >> 16, st3,
                        0, 32, 0x1C0, s4);
        *(s64 *)(s3 + 0x00) = (s64)*(s32 *)(frame + 0x40) | ((s64)*(s32 *)(frame + 0x44) << 16);
        *(s64 *)(s3 + 0x08) = (s64)*(s32 *)(frame + 0x30) | ((s64)*(s32 *)(frame + 0x34) << 16);
        s3 += 0x10;
        *(s64 *)(s3 + 0x00) = (s64)*(s32 *)(frame + 0x48) | ((s64)*(s32 *)(frame + 0x4C) << 16);
        *(s64 *)(s3 + 0x08) = (s64)*(s32 *)(frame + 0x38) | ((s64)*(s32 *)(frame + 0x3C) << 16);
        s3 += 0x10;
    } while (cnt >= 0);

    *(s64 *)(s5 + 0x08) = 0x5353;
    *(s64 *)(s5 + 0x00) = ((s64)0x44000000 << 32) | 0x8010;
    return Dma_EndDirect(s3);
}
