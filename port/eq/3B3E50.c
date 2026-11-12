#include "common.h"

extern u8 *D_00421380 __attribute__((section(".data")));

s32 func_1018B8(u8 *arg0);
void func_2493C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_26E9E8(u8 *arg0);

/* 0x003B3E50: for j in 0..2: func_26E9E8(G + 0x28*j + 0x10) (G = D_00421380). Then, if G->0xEC == 8 and G->0xFC != 0
 * and func_1018B8(G) == 5: G->0xEC = G->0xE8 + 9; G->0xF4 = (G->0xE8 ^ 1) & 1; func_2493C0(G->0xC, 0x36DC, 0x3AF5, 0,
 * G->0xEC) (tail). */
void func_003B3E50(void) {
    s32 j;
    u8 *g;

    for (j = 0; j < 3; j++) {
        func_26E9E8(D_00421380 + j * 0x28 + 0x10);
    }

    g = D_00421380;
    if (*(s32 *)(g + 0xEC) != 8) {
        return;
    }
    if (*(s32 *)(g + 0xFC) == 0) {
        return;
    }
    if (func_1018B8(g) != 5) {
        return;
    }

    *(s32 *)(g + 0xEC) = *(s32 *)(g + 0xE8) + 9;
    *(s32 *)(g + 0xF4) = (*(s32 *)(g + 0xE8) ^ 1) & 1;
    func_2493C0(*(s32 *)(g + 0xC), 0x36DC, 0x3AF5, 0, *(s32 *)(g + 0xEC));
}
