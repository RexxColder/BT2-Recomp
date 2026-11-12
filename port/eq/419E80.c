#include "common.h"

extern u8 *D_0042BB80 __attribute__((section(".data")));

void func_26E9E8(u8 *arg0);
void func_00419040(u8 *arg0, u8 *arg1);
void func_003B46A0(void);
s32 func_003B5128(s32 arg0);
void func_003B4FF8(s32 arg0);

/* 0x00419E80: func_26E9E8(G + 0x28*j + 8) for j = 0, 1 (G = D_0042BB80). If G->0xD0 has bit 4: G->0xC8 -= 1; when that
 * reaches -1: G->0xD0 ^= 4, G->0xC8 = 0, func_00419040(G, G). Then func_003B46A0(); G->0xC4 = func_003B5128(G->0xC0);
 * if G->0xC4 == 0: tail func_003B4FF8(G->0xC0). */
void func_00419E80(void) {
    s32 j;
    s32 v;

    for (j = 0; j < 2; j++) {
        func_26E9E8(D_0042BB80 + j * 0x28 + 8);
    }

    if (*(s32 *)(D_0042BB80 + 0xD0) & 4) {
        v = *(s32 *)(D_0042BB80 + 0xC8) - 1;
        *(s32 *)(D_0042BB80 + 0xC8) = v;
        if (v == -1) {
            *(s32 *)(D_0042BB80 + 0xD0) = *(s32 *)(D_0042BB80 + 0xD0) ^ 4;
            *(s32 *)(D_0042BB80 + 0xC8) = 0;
            func_00419040(D_0042BB80, D_0042BB80);
        }
    }

    func_003B46A0();
    *(s32 *)(D_0042BB80 + 0xC4) = func_003B5128(*(s32 *)(D_0042BB80 + 0xC0));
    if (*(s32 *)(D_0042BB80 + 0xC4) != 0) {
        return;
    }
    func_003B4FF8(*(s32 *)(D_0042BB80 + 0xC0));
}
