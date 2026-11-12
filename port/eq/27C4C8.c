#include "common.h"

extern u8 gGfx[] __attribute__((section(".data")));
extern u8 *D_003876A0;

extern void *Dma_BeginDirect(void);
extern void Dma_EndDirect(void *end);
extern s32 Tex_Log2Size(s32 arg0);

/* GIF packet writer: every entry is two u64 (data, register address) appended to the DMA buffer. */
#define QW(lo, hi) do { w[0] = (s64)(lo); w[1] = (s64)(hi); w += 2; } while (0)

/* Builds the full-screen "fade / vignette / badge" overlay packet. col = gray level of the fade quad, flag = draw the
 * round badge, badge_z = its Z, has_a = tint quad present with colour rgba[4], arg4 selects the badge texture set. */
void func_0027C4C8(s32 unused, s32 col, u8 flag, s32 badge_z, s32 arg4, u8 has_a, s32 *rgba)
{
    s64 *w;
    s32 tex_a;
    s32 tex_b;
    s32 i;
    s32 ra;
    s32 rb;

    if (arg4) {
        tex_a = 0x1FC;
        tex_b = 0x3F80;
    } else {
        tex_a = 0x1FA;
        tex_b = 0x3F40;
    }
    w = (s64 *)Dma_BeginDirect();

    QW(0x100000000000000DULL, 14);
    QW(1, 70);
    QW(0, 74);
    QW(0, 75);
    QW(0x40150, 76);
    QW(0x1310000E0ULL, 78);
    QW(0x780000007800ULL, 24);
    QW(0xFF000000FF0000ULL, 64);
    QW(0x6FC007FC00AULL, 8);
    QW(0x8000000064ULL, 66);
    QW(96, 20);
    QW(196608, 71);
    QW(70, 0);
    QW(0x3F80000080000000ULL, 1);
    QW(0x2400000000000001ULL, 85);
    QW(2013296640, 2281736192LL);
    QW(0x1000000000000006ULL, 14);
    QW(0, 63);
    QW((gGfx[0x234] & 1) ? 0x2000000664020000ULL : 0x2000000664020E00ULL, 6);
    QW(68, 66);
    QW(196608, 71);
    QW(342, 0);
    QW(0x3F80000080808080ULL, 1);
    QW(0x4400000000000010ULL, 21331);
    for (i = 0; i < 16; i++) {
        QW(i << 9, (0x7800 + 256 * i) | 0x78000000);
        QW((512 + 512 * i) | 0x1C000000, (0x7900 + 256 * i) | 0x88000000LL);
    }

    QW(0x1000000000000009ULL, 14);
    QW(0x1310000E0ULL, 78);
    QW(131440, 76);
    QW(0x7C0000007C00ULL, 24);
    QW(0x7F0000007F0000ULL, 64);
    QW(0x3FC003FC00AULL, 8);
    QW(0, 63);
    ra = Tex_Log2Size(256);
    rb = Tex_Log2Size(256);
    QW(((s64)ra << 26) | ((s64)rb << 30) | 0x12A00, 6);
    QW(342, 0);
    QW(0x3F80000080808080ULL, 1);
    QW(0x4400000000000008ULL, 21331);
    for (i = 0; i < 8; i++) {
        QW(i << 9, (0x7C00 + 256 * i) | 0x7C000000);
        QW((512 + 512 * i) | 0x10000000, (0x7D00 + 256 * i) | 0x84000000LL);
    }

    QW(0x100000000000000AULL, 14);
    QW(0x1310000E0ULL, 78);
    QW(66038, 76);
    QW(0x7E0000007E00ULL, 24);
    QW(0x3F0000003F0000ULL, 64);
    QW(0x1FC001FC00AULL, 8);
    QW(68, 66);
    QW(0, 63);
    ra = Tex_Log2Size(128);
    rb = Tex_Log2Size(128);
    QW(((s64)ra << 26) | ((s64)rb << 30) | 0xAE00, 6);
    QW(342, 0);
    QW(0x3F80000080808080ULL, 1);
    QW(0x4400000000000002ULL, 21331);
    QW(0, 2113961472);
    QW(134219776, 2181071360LL);
    QW(0x100010, 2113961472);
    QW(135268368, 2181071360LL);

    QW(0x100000000000000FULL, 14);
    QW(66040, 77);
    QW(0x1310000E0ULL, 79);
    QW(0x3F0000003F0000ULL, 65);
    QW(0x7E0000007E00ULL, 25);
    QW(0x8000000064ULL, 67);
    ra = Tex_Log2Size(64);
    rb = Tex_Log2Size(64);
    QW(((s64)ra << 26) | ((s64)rb << 30) | 0x7F00, 6);
    ra = Tex_Log2Size(64);
    rb = Tex_Log2Size(64);
    QW(((s64)ra << 26) | ((s64)rb << 30) | 0x7EC0, 7);
    QW(0xFC000FC00AULL, 8);
    QW(0xFC000FC00AULL, 9);
    QW(96, 21);
    QW(96, 20);
    QW(0x8000000064ULL, 66);
    QW(0x8000000064ULL, 67);
    QW(196608, 71);
    QW(196608, 72);

    QW(0x640000000000000AULL, 5460752);
    for (i = 0; i < 10; i++) {
        s32 odd = i & 1;
        s32 gx = odd ? 0 : 16;
        s32 gy = odd ? 0 : 16;
        QW(odd ? 342 : 854, 0x3F80000080808080ULL);
        QW(gx | ((s64)gy << 16), 2113961472);
        QW((s64)(gx + 1024) | ((s64)(gy + 1024) << 16), 2181071360LL);
    }

    QW(0x100000000000000AULL, 14);
    QW(131440, 76);
    QW(0x1310000E0ULL, 78);
    QW(0x7C0000007C00ULL, 24);
    QW(0x7F0000007F0000ULL, 64);
    QW(0xFC000FC00AULL, 8);
    QW(196608, 71);
    QW(0x8000000064ULL, 66);
    QW((s64)col | 0x3F80000000000000ULL | ((s64)col << 16) | 0x80000000LL | ((s64)col << 8), 1);
    QW(96, 20);
    QW(342, 0);
    QW(0x4400000000000001ULL, 21331);
    QW(262148, 2080406528);
    QW(67372036, 2214626304LL);

    if (flag) {
        QW(0x1000000000000005ULL, 14);
        QW(342, 0);
        QW(0x3F80000080808080ULL, 1);
        QW(((s64)badge_z << 32) | 0x64, 66);
        QW(0, 63);
        ra = Tex_Log2Size(64);
        rb = Tex_Log2Size(64);
        QW((s64)tex_b | 0x4000 | ((s64)ra << 26) | ((s64)rb << 30), 6);
        QW(0x4400000000000001ULL, 21331);
        QW(262148, 2080406528);
        QW(67372036, 2214626304LL);
    }

    if (has_a) {
        QW(0x1000000000000003ULL, 14);
        QW(70, 0);
        QW(68, 66);
        QW((s64)rgba[0] | 0x3F80000000000000ULL | ((s64)rgba[2] << 16) | ((s64)rgba[1] << 8) | ((s64)rgba[3] << 24), 1);
        QW(0x2400000000000001ULL, 85);
        QW(2080406528, 2214626304LL);
    }

    if (!(*(s64 *)(D_003876A0 + 0x4D8) & 0x100) && flag) {
        QW(0x100000000000000BULL, 14);
        QW(tex_a | 0x10000, 76);
        QW(0x7E0000007E00ULL, 24);
        QW(0x3F0000003F0000ULL, 64);
        QW(0x1FC001FC00AULL, 8);
        QW(0, 63);
        ra = Tex_Log2Size(128);
        rb = Tex_Log2Size(128);
        QW(((s64)ra << 26) | ((s64)rb << 30) | 0xAE00, 6);
        QW(196608, 71);
        QW(0x8000000064ULL, 66);
        QW(0x3F80000080808080ULL, 1);
        QW(96, 20);
        QW(342, 0);
        QW(0x4400000000000001ULL, 21331);
        QW(0x100010, 2113961472);
        QW(135268368, 2181071360LL);
    }

    QW(0x100000000000000CULL, 14);
    QW(0x40150, 76);
    QW(0x1310000E0ULL, 78);
    QW(0x780000007800ULL, 24);
    QW(0xFF000000FF0000ULL, 64);
    QW(0x1FC001FC00AULL, 8);
    QW(196608, 71);
    QW(0x8000000064ULL, 66);
    QW(0x3F80000080808080ULL, 1);
    QW(96, 20);
    QW(342, 0);
    QW(0, 63);
    ra = Tex_Log2Size(128);
    rb = Tex_Log2Size(128);
    QW(((s64)ra << 26) | ((s64)rb << 30) | 0xAE00, 6);
    QW(0x4400000000000004ULL, 21331);
    for (i = 0; i < 4; i++) {
        QW((8 + 512 * i) | 0x80000, (0x7800 + 1024 * i) | 0x78000000);
        QW((0x208 + 512 * i) | 0x8080000, (0x7C00 + 1024 * i) | 0x88000000LL);
    }

    QW(0x100000000000000AULL, 14);
    QW(0x3F80000080808080ULL, 1);
    QW((gGfx[0x234] & 1) ? 0x80000 : 524400, 76);
    QW(0x1310000E0ULL, 78);
    QW(0x720000007000ULL, 24);
    QW(0x1BF000001FF0000ULL, 64);
    QW(196608, 71);
    QW(0x3FC003FC00AULL, 8);
    ra = Tex_Log2Size(256);
    rb = Tex_Log2Size(256);
    QW(((s64)ra << 26) | ((s64)rb << 30) | 0x12A00, 6);
    QW(0, 63);
    QW(0x8000000068ULL, 66);
    QW(0x4400000000000008ULL, 21331);
    for (i = 0; i < 8; i++) {
        QW((8 + 512 * i) | 0x80000, (0x7000 + 1024 * i) | 0x72000000);
        QW((0x208 + 512 * i) | 0x10080000, (0x7400 + 1024 * i) | 0x8E000000LL);
    }

    QW(0x1000000000008006ULL, 14);
    QW((gGfx[0x234] & 1) ? 0x80000 : 524400, 76);
    QW(0x720000007000ULL, 24);
    QW(0x1BF000001FF0000ULL, 64);
    QW(458752, 71);
    QW(0x1310000E0ULL, 78);
    QW(0, 8);
    Dma_EndDirect(w);
}
