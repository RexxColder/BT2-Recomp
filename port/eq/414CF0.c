#include "common.h"

extern u8 *D_0042BB7C __attribute__((section(".data")));
extern u8 D_0042EC90 __attribute__((section(".data")));

void func_26E9E8(u8 *arg0);
s32 func_26EB70(u8 *arg0);
void func_26EB78(u8 *arg0, u8 *arg1);

/* 0x00414CF0: func_26E9E8(G + 0x28*j + 0x38) for j = 0..5 (G = D_0042BB7C). Then by v = G->0x3738: 1 -> func_26EB78(G+0x60,
 * &D_0042EC90), v += 1, then the case-2 code; 2 -> if func_26EB70(G+0x60) & 0x200, v += 1; 3 -> v = 0; others nothing. */
void func_00414CF0(void) {
    s32 j;
    s32 v;

    for (j = 0; j < 6; j++) {
        func_26E9E8(D_0042BB7C + j * 0x28 + 0x38);
    }

    v = *(s32 *)(D_0042BB7C + 0x3738);
    switch (v) {
    case 1:
        func_26EB78(D_0042BB7C + 0x60, &D_0042EC90);
        *(s32 *)(D_0042BB7C + 0x3738) = *(s32 *)(D_0042BB7C + 0x3738) + 1;
        /* fallthrough */
    case 2:
        if (func_26EB70(D_0042BB7C + 0x60) & 0x200) {
            *(s32 *)(D_0042BB7C + 0x3738) = *(s32 *)(D_0042BB7C + 0x3738) + 1;
        }
        return;
    case 3:
        *(s32 *)(D_0042BB7C + 0x3738) = 0;
        break;
    default:
        break;
    }
}
