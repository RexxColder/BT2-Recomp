#include "common.h"

extern u8 *D_00427334 __attribute__((section(".data")));

s32 func_1018B8(void);
void func_2493C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_249510(s32 arg0, s32 arg1);
void func_26E9E8(u8 *arg0);

/* 0x003E06A0: if G->0xA0 == 0 and G->0xA8 != 0 and func_1018B8() == 5: G->0xA0 = G->0x9C + 1 and
 * func_2493C0(G->0xC, 0x3422, 0x383B, 0, G->0xA0). Then G->0xBC -= 1; if that is negative: func_249510(4, -0x50) and
 * G->0xBC = rand() % 3600 + 0x708. Finally func_26E9E8(G + 0x28*j + 0x10) for j = 0, 1 (G = D_00427334). */
void func_003E06A0(void) {
    s32 v;
    s32 j;

    if (*(s32 *)(D_00427334 + 0xA0) == 0 && *(s32 *)(D_00427334 + 0xA8) != 0) {
        if (func_1018B8() == 5) {
            *(s32 *)(D_00427334 + 0xA0) = *(s32 *)(D_00427334 + 0x9C) + 1;
            func_2493C0(*(s32 *)(D_00427334 + 0xC), 0x3422, 0x383B, 0, *(s32 *)(D_00427334 + 0xA0));
        }
    }

    v = *(s32 *)(D_00427334 + 0xBC) - 1;
    *(s32 *)(D_00427334 + 0xBC) = v;
    if (v < 0) {
        func_249510(4, -0x50);
        *(s32 *)(D_00427334 + 0xBC) = rand() % 3600 + 0x708;
    }

    for (j = 0; j < 2; j++) {
        func_26E9E8(D_00427334 + j * 0x28 + 0x10);
    }
}
