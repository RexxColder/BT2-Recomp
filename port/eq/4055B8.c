#include "common.h"

extern u8 *D_0042BB74 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));

void func_00248708(u8 *a0, u8 *a1, u8 *a2, u8 *a3);
void func_00405500(s32 a0, s32 a1, s32 a2, s32 a3);

/* 0x004055B8: setup of the state block G = D_0042BB74. G->0x260 = G->4 + (G->4->0x2C & ~3) + 4 and G->0x25C = *(G->4 +
 * (G->4->0x2C & ~3)), then func_00248708(G+0x268, G+0x26C, G+0x25C, G+0x260), G->0x25C = G->0x268, G->0x260 = G+0x26C,
 * G->0x264 = G+0x1A7C, G->0x36BC = ceil(G->0x25C / 7), G->0x210 flags cleared (&~0x40, &~0x80) and |= 2, G->0x36C0 = 1,
 * G->0x20C = 0. Then two passes (index s5 = 0, 1) over the 7-entry tables at G+0x390/0x3B0/0x400/0x430 (stride 0x14 in
 * s3), writing G+0x210.. (per pass record), and a call func_00405500(s5, a1, a2, a3) with a3 stored at G+0x3280 + ... */
void func_004055B8(void) {
    u8 *g;
    u8 *a0p;
    s32 s3;
    s32 s5;
    s32 s6;
    s32 t0;
    s32 t1;
    s32 t2;
    s32 t3;
    s32 t4;
    s32 a2;
    s32 a3;
    s32 v;

    g = D_0042BB74;
    *(u8 **)(g + 0x260) = *(u8 **)(g + 4) + (((u32)*(s32 *)(*(u8 **)(g + 4) + 0x2C) >> 2) * 4) + 4;
    a0p = *(u8 **)(g + 4);
    *(s32 *)(g + 0x25C) = *(s32 *)(a0p + (((u32)*(s32 *)(a0p + 0x2C) >> 2) * 4));
    func_00248708(g + 0x268, g + 0x26C, g + 0x25C, g + 0x260);
    *(s32 *)(g + 0x25C) = *(s32 *)(g + 0x268);
    *(u8 **)(g + 0x260) = g + 0x26C;
    *(u8 **)(g + 0x264) = g + 0x1A7C;
    *(s32 *)(g + 0x36BC) = *(s32 *)(g + 0x25C) / 7;
    if ((*(s32 *)(g + 0x25C) % 7) != 0) {
        *(s32 *)(g + 0x36BC) = *(s32 *)(g + 0x36BC) + 1;
    }
    *(s32 *)(g + 0x210) = *(s32 *)(g + 0x210) & ~0x40;
    s5 = 0;
    s6 = 0;
    s3 = 0;
    *(s32 *)(g + 0x210) = *(s32 *)(g + 0x210) & ~0x80;
    *(s32 *)(g + 0x36C0) = 1;
    *(s32 *)(g + 0x20C) = 0;
    *(s32 *)(g + 0x210) = *(s32 *)(g + 0x210) | 2;

    do {
        t3 = s3 + 0x3B0;
        t4 = s3 + 0x400;
        t0 = s3 + 0x430;
        a2 = s3 + 0x390;
        *(s32 *)(D_3876A4 + a2) = s5;
        t1 = s5 * 4 + 0x210;
        t2 = s5 * 4 + 0x220;
        v = s5 * 4 + 0x230;
        a3 = s5;
        s5 += 1;
        *(s32 *)(D_3876A4 + t3 + 8) = 0;
        *(s32 *)(D_3876A4 + t4 + 8) = 0;
        *(s32 *)(D_3876A4 + t0) = 0;
        s3 += 0x14;
        *(s32 *)(g + t1 + 4) = *(s32 *)(D_3876A4 + a2) % 7;
        *(s32 *)(g + t1 + 0xC) = *(s32 *)(D_3876A4 + a2) / 7;
        *(s32 *)(g + t2 + 0xC) = *(s32 *)(D_3876A4 + t3 + 8);
        *(s32 *)(g + t2 + 4) = *(s32 *)(D_3876A4 + t4 + 8);
        *(s32 *)(g + v + 4) = *(s32 *)(D_3876A4 + t0);
        *(s32 *)(g + v + 0xC) = *(s32 *)(D_3876A4 + t0);
        {
            s32 b1 = *(s32 *)(g + 0xC + t1);
            s32 b2 = *(s32 *)(g + 4 + t1);
            s32 b3 = *(s32 *)(g + 4 + t2);
            *(s32 *)(g + 0x3280 + 0xC + (((b1 * 7 + s6) + b2) * 4)) = b3;
            func_00405500(a3, b1, b2, b3);
            s6 += 0x86;
        }
    } while (s5 < 2);
}
