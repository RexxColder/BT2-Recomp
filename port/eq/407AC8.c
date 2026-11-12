#include "common.h"

extern u8 *D_0042BB74 __attribute__((section(".data")));
extern u8 D_0042DEB8 __attribute__((section(".data")));

void func_26E9E8(u8 *arg0);
s32 func_26EB70(u8 *arg0);
void func_26EB78(u8 *arg0, u8 *arg1);

/* 0x00407AC8: func_26E9E8(G + 0x28*j + 0x28) for j = 0..5 (G = D_0042BB74). Then by v = G->0x36D8: 1 -> func_26EB78(G+0x50,
 * &D_0042DEB8), v += 1, then the case-2 code; 2 -> if func_26EB70(G+0x50) & 0x200, v += 1; 3 -> v = 0; others nothing. */
void func_00407AC8(void) {
    s32 j;
    s32 v;

    for (j = 0; j < 6; j++) {
        func_26E9E8(D_0042BB74 + j * 0x28 + 0x28);
    }

    v = *(s32 *)(D_0042BB74 + 0x36D8);
    switch (v) {
    case 1:
        func_26EB78(D_0042BB74 + 0x50, &D_0042DEB8);
        *(s32 *)(D_0042BB74 + 0x36D8) = *(s32 *)(D_0042BB74 + 0x36D8) + 1;
        /* fallthrough */
    case 2:
        if (func_26EB70(D_0042BB74 + 0x50) & 0x200) {
            *(s32 *)(D_0042BB74 + 0x36D8) = *(s32 *)(D_0042BB74 + 0x36D8) + 1;
        }
        return;
    case 3:
        *(s32 *)(D_0042BB74 + 0x36D8) = 0;
        break;
    default:
        break;
    }
}
