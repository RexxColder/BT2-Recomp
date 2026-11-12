#include "common.h"

extern u8 *D_00421C98 __attribute__((section(".data")));

void func_26E9E8(u8 *arg0);
void func_2493C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_1018B8(s32 arg0, s32 arg1);

/* 0x003C1AA0: if G->0x12C == 0 (G = D_00421C98) and t = G->0x13C != 0: t == 1: func_2493C0(G->8, 0x33E9, 0x3802, 0, 0)
 * and G->0x13C += 1; else if func_1018B8(t, 0x33E9) == 5: G->0x12C = G->0x128 + 1 and
 * func_2493C0(G->8, 0x33E9, 0x3802, 0, G->0x12C). Then func_26E9E8(G + 0x28*j + 0x18) for j = 0..2. */
void func_003C1AA0(void) {
    s32 j;

    if (*(s32 *)(D_00421C98 + 0x12C) == 0) {
        s32 t = *(s32 *)(D_00421C98 + 0x13C);

        if (t != 0) {
            if (t == 1) {
                func_2493C0(*(s32 *)(D_00421C98 + 8), 0x33E9, 0x3802, 0, 0);
                *(s32 *)(D_00421C98 + 0x13C) = *(s32 *)(D_00421C98 + 0x13C) + 1;
            } else if (func_1018B8(t, 0x33E9) == 5) {
                *(s32 *)(D_00421C98 + 0x12C) = *(s32 *)(D_00421C98 + 0x128) + 1;
                func_2493C0(*(s32 *)(D_00421C98 + 8), 0x33E9, 0x3802, 0, *(s32 *)(D_00421C98 + 0x12C));
            }
        }
    }

    for (j = 0; j < 3; j++) {
        func_26E9E8(D_00421C98 + j * 0x28 + 0x18);
    }
}
