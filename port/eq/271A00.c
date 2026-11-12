#include "common.h"

#define SD(p, off, v) (*(s64 *)((u8 *)(p) + (off)) = (s64)(v))

s32 Dma_BeginDirect(s32 arg0, s32 arg1, s32 arg2);
void Dma_EndDirect(s32 arg0, s32 arg1, s32 arg2);

/* 0x00271A00: builds a GS packet of the direct DMA buffer: a fixed header (six 16-byte quadwords with the
 * registers 0x44/0x42/0x47/0x4A/0x1 and arg4/arg5), a tag for arg2 rounded up to 32-word units (its count, with
 * 0x8000 and a 0x9000 flag), and one quadword pair per unit (arg0 and arg1+arg3 scaled by 16 and 0x200 apart).
 * The buffer is closed with Dma_EndDirect. */
void func_00271A00(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s64 arg5) {
    s32 cnt;
    s32 n;
    u8 *t;
    u8 *tag;
    s64 s0;
    s64 lo;
    s64 hi;
    s64 a0v;
    s64 a1v;
    s64 a3v;
    s64 t1v;
    s32 k;

    cnt = arg2;
    if (cnt < 0) {
        cnt += 31;
    }
    n = cnt >> 5;

    t = (u8 *)(s32)Dma_BeginDirect(arg0, arg1, cnt);

    SD(t, 0x00, (s64)0x1000000000000005LL);
    SD(t, 0x08, 0xE);
    t += 0x10;
    SD(t, 0x00, 0x44);
    SD(t, 0x08, 0x42);
    t += 0x10;
    SD(t, 0x00, 0x30000);
    SD(t, 0x08, 0x47);
    t += 0x10;
    SD(t, 0x00, 0);
    SD(t, 0x08, 0x4A);
    t += 0x10;
    s0 = ((s64)(arg4 & 0xFF)) << 6;
    SD(t, 0x00, s0 | 6);
    SD(t, 0x08, 0);
    t += 0x10;
    SD(t, 0x00, arg5);
    SD(t, 0x08, 1);
    t += 0x10;

    tag = t;
    t += 0x10;

    if (n > 0) {
        a0v = (s64)(s32)(arg0 << 4);
        t1v = a0v;
        a1v = (s64)(s32)(arg1 << 4) << 16;
        a3v = (s64)(s32)((arg1 + arg3) << 4) << 16;
        a0v = a0v + 0x200;
        for (k = 0; k < n; k++) {
            lo = t1v | a1v;
            hi = a0v | a3v;
            SD(t, 0x00, lo);
            SD(t, 0x08, hi);
            t1v += 0x200;
            a0v += 0x200;
            t += 0x10;
        }
    }

    lo = ((s64)(n | 0x8000)) | (s64)0x2400000000000000LL;
    SD(tag, 0x00, lo);
    SD(tag, 0x08, 0x55);

    Dma_EndDirect((s32)(s32)t, 0, 0);
}
