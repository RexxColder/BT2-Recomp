#include "common.h"

#define ST64(p, off, v) (*(s64 *)((u8 *)(p) + (off)) = (v))

void *Dma_BeginDirect();
void Dma_EndDirect(void *a0, s64 a1, s64 a2, s64 a3);
void TexFile_UploadOne(void *a0, s32 a1, s32 a2, s32 a3);

void func_002A4940(void *arg0) {
    u8 *a = (u8 *)arg0;
    s32 lh0 = *(s16 *)(a + 0x0);
    s32 lh2 = *(s16 *)(a + 0x2);
    s32 lh4 = *(s16 *)(a + 0x4);
    s32 lh6 = *(s16 *)(a + 0x6);
    s32 s6 = (lh0 + 0x700) << 4;
    s32 s5 = (lh2 + 0x720) << 4;
    s32 fp = (lh4 + 0x700) << 4;
    s32 s7 = (lh6 + 0x720) << 4;
    s32 kind = *(s32 *)(a + 0x14);
    s64 mask = (s64)0x0FFFFFFF00000000LL; /* (-1 << 36) >> 4, logical */
    s64 a3v;
    s64 a2v;
    s64 d;
    u8 *t3;

    if (kind == 0) {
        t3 = (u8 *)Dma_BeginDirect(lh2 + 0x720, lh4 + 0x700, kind);
        ST64(t3, 0x00, 0x1000000000008003LL);
        ST64(t3, 0x08, 0xE);
        ST64(t3, 0x10, (s64)0x310000E0);
        ST64(t3, 0x18, 0x4E);
        ST64(t3, 0x20, (s64)0x50000);
        ST64(t3, 0x28, 0x47);
        ST64(t3, 0x30, 0x44);
        ST64(t3, 0x38, 0x42);
        ST64(t3, 0x40, 0x4400000000008001LL);
        ST64(t3, 0x48, 0x5510);
        ST64(t3, 0x50, 0x46);

        d = (s64)a[0x8] | ((s64)0xFE00 << 46) | ((s64)a[0xA] << 16) | ((s64)a[0x9] << 8) |
            ((s64)a[0xB] << 24);
        a3v = (s64)s6 | ((s64)s5 << 16) | mask;
        a2v = (s64)fp | ((s64)s7 << 16) | mask;
        ST64(t3, 0x58, d);
        ST64(t3, 0x60, a3v);
        ST64(t3, 0x68, a2v);
        Dma_EndDirect(t3 + 0x70, (s64)a[0x9] << 8, a2v, a3v);
        return;
    }

    if (kind == 1) {
        s32 s2;
        s32 s0;
        s32 s3;
        s32 s1;
        s32 addr;
        s64 combo;
        s64 d2;

        TexFile_UploadOne(*(void **)(a + 0x1C), (s32)*(s8 *)(a + 0x1A), 0x2A00, 0x2DC0);
        s2 = (s32)*(s16 *)(a + 0xC) << 4;
        s0 = *(s16 *)(a + 0xE);
        s3 = *(s16 *)(a + 0x10);
        s1 = *(s16 *)(a + 0x12);
        t3 = (u8 *)Dma_BeginDirect();

        ST64(t3, 0x00, 0x1000000000008005LL);
        ST64(t3, 0x08, 0xE);
        ST64(t3, 0x10, (s64)0x310000E0);
        ST64(t3, 0x18, 0x4E);
        ST64(t3, 0x20, (s64)0x50000);
        ST64(t3, 0x28, 0x47);
        ST64(t3, 0x30, 0x60);
        ST64(t3, 0x38, 0x14);
        ST64(t3, 0x40, 0x44);
        ST64(t3, 0x48, 0x42);
        ST64(t3, 0x50, 0x5);
        ST64(t3, 0x58, 0x8);
        ST64(t3, 0x60, (s64)0x8400000000008001ULL);
        ST64(t3, 0x68, (s64)0x535316F0);
        ST64(t3, 0x70, 0x156);
        ST64(t3, 0x78, 0);

        /* combo word read from the table pointed to by arg0+0x1C */
        addr = ((s32)*(s8 *)(a + 0x1A) << 6) + *(s32 *)(*(u8 **)(a + 0x1C) + 0x10);
        combo = *(s64 *)(addr + 0x30) | ((s64)0xB700 << 35) | (s64)0x2A00 | ((s64)0x8000 << 19);
        ST64(t3, 0x80, combo);

        a3v = (s64)s6 | ((s64)s5 << 16) | mask;
        a2v = (s64)fp | ((s64)s7 << 16) | mask;
        ST64(t3, 0x90, (s64)s2 | ((s64)((s32)s0 << 4) << 16));

        d2 = (s64)a[0x8] | ((s64)0xFE00 << 46) | ((s64)a[0xA] << 16) | ((s64)a[0x9] << 8) |
             ((s64)a[0xB] << 24);
        ST64(t3, 0x88, d2);
        ST64(t3, 0x98, a3v);
        ST64(t3, 0xA0, (s64)((s32)s3 << 4) | ((s64)((s32)s1 << 4) << 16));
        ST64(t3, 0xA8, a2v);
        Dma_EndDirect(t3 + 0xB0, (s64)a[0xB] << 24, a2v, a3v);
        return;
    }
}
