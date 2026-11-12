#include "common.h"

extern u8 *D_00427330 __attribute__((section(".data")));

void func_26E9E8(u8 *arg0);

/* 0x003DF4A8: G = D_00427330, p = G->0xF8 * G->0x100 (32-bit), k = 0.2f (bits 0x3E4CCCCC), fc = G->0xFC.
 * If p < fc: fc -= (s32)(G->0x100 * k), and if fc < p then fc = p. If p > fc: fc += (s32)(G->0x100 * k), and if p < fc
 * then fc = p. Store fc to G->0xFC. Then func_26E9E8(G + 0x28*j + 0x14) for j = 0, 1. */
void func_003DF4A8(void) {
    f32 k;
    s32 p;
    s32 fc;
    s32 d;
    s32 j;
    u8 *g;

    *(u32 *)&k = 0x3E4CCCCCu;

    g = D_00427330;
    p = (s32)((u32)*(s32 *)(g + 0xF8) * (u32)*(s32 *)(g + 0x100));
    fc = *(s32 *)(g + 0xFC);

    if (p < fc) {
        d = (s32)((f32)*(s32 *)(g + 0x100) * k);
        fc = fc - d;
        if (fc < p) {
            fc = p;
        }
        *(s32 *)(g + 0xFC) = fc;
    } else if (p > fc) {
        d = (s32)((f32)*(s32 *)(g + 0x100) * k);
        fc = fc + d;
        if (p < fc) {
            fc = p;
        }
        *(s32 *)(g + 0xFC) = fc;
    }

    for (j = 0; j < 2; j++) {
        func_26E9E8(D_00427330 + j * 0x28 + 0x14);
    }
}
