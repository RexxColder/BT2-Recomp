#include "common.h"

extern u8 *D_0042BB84 __attribute__((section(".data")));

s32 func_1018B8(void);
void func_2493C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_26E9E8(u8 *arg0);
s32 func_26EB70(u8 *arg0);
void func_297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

/* 0x0041B6A8: G = D_0042BB84. If G->0xF8 == 0 and G->0x104 != 0 and func_1018B8() == 5: G->0xF8 = G->0xF4 + 1 and
 * func_2493C0(G->8, 0x36A3, 0x3ABC, 0, G->0xF8). Then func_26E9E8(G + 0x28*j + 0x10) for j = 0, 1. If func_26EB70(G+0x38)
 * has bit 8: v = G->0x110: 0 -> func_297FE0(2, 1, 0x40, 0x40, 1); 1 -> func_297FE0(2, 0, 0x40, 0x40, 1); either one then
 * G->0x110 += 1. */
void func_0041B6A8(void) {
    s32 j;
    s32 v1;

    if (*(s32 *)(D_0042BB84 + 0xF8) == 0 && *(s32 *)(D_0042BB84 + 0x104) != 0 && func_1018B8() == 5) {
        *(s32 *)(D_0042BB84 + 0xF8) = *(s32 *)(D_0042BB84 + 0xF4) + 1;
        func_2493C0(*(s32 *)(D_0042BB84 + 8), 0x36A3, 0x3ABC, 0, *(s32 *)(D_0042BB84 + 0xF8));
    }

    for (j = 0; j < 2; j++) {
        func_26E9E8(D_0042BB84 + j * 0x28 + 0x10);
    }

    if (func_26EB70(D_0042BB84 + 0x38) & 8) {
        v1 = *(s32 *)(D_0042BB84 + 0x110);
        if (v1 == 0) {
            func_297FE0(2, 1, 0x40, 0x40, 1);
        } else if (v1 == 1) {
            func_297FE0(2, 0, 0x40, 0x40, 1);
        } else {
            return;
        }
        *(s32 *)(D_0042BB84 + 0x110) = *(s32 *)(D_0042BB84 + 0x110) + 1;
    }
}
