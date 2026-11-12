#include "common.h"

extern u8 *D_004279CC __attribute__((section(".data")));
extern u8 D_00427D60[] __attribute__((section(".data")));

s32 rand(void);
s32 func_1018B8(void);
void func_297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_2493C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_26E9E8(u8 *arg0);
void func_26EBC0(u8 *arg0, u8 *arg1, s32 *arg2);
void func_26EFC8(u8 *arg0, s32 *arg1, s32 arg2);

/* 0x003E4B80 (G = D_004279CC): G->0x4540 -= 1; if it went negative, func_297FE0(2, 0, 0x40, 0x40, 1) and
 * G->0x4540 = rand() % 0xE10 + 0x708. If G->0xD8 == 0 and G->0xEC != 0 and func_1018B8() == 5:
 * G->0xD8 = G->0xD4 + 1, func_2493C0(G->8, 0x36EF, 0x3B08, 0, G->0xD8). Then func_26EBC0(G+0x3C, &D_00427D60, sp)
 * and func_26EFC8(G+0x3C, sp, G->0xD0 & 4 ? 2 : 1). Finally func_26E9E8(G + 0x14) and func_26E9E8(G + 0x28 + 0x14). */
void func_003E4B80(void) {
    s32 sp[4];
    s32 i;

    *(s32 *)(D_004279CC + 0x4540) = *(s32 *)(D_004279CC + 0x4540) - 1;
    if (*(s32 *)(D_004279CC + 0x4540) < 0) {
        func_297FE0(2, 0, 0x40, 0x40, 1);
        *(s32 *)(D_004279CC + 0x4540) = rand() % 0xE10 + 0x708;
    }

    if (*(s32 *)(D_004279CC + 0xD8) == 0) {
        if (*(s32 *)(D_004279CC + 0xEC) != 0) {
            if (func_1018B8() == 5) {
                *(s32 *)(D_004279CC + 0xD8) = *(s32 *)(D_004279CC + 0xD4) + 1;
                func_2493C0(*(s32 *)(D_004279CC + 0x8), 0x36EF, 0x3B08, 0, *(s32 *)(D_004279CC + 0xD8));
            }
        }
    }

    if (*(s32 *)(D_004279CC + 0xD0) & 0x4) {
        func_26EBC0(D_004279CC + 0x3C, D_00427D60, sp);
        func_26EFC8(D_004279CC + 0x3C, sp, 2);
    } else {
        func_26EBC0(D_004279CC + 0x3C, D_00427D60, sp);
        func_26EFC8(D_004279CC + 0x3C, sp, 1);
    }

    for (i = 0; i < 2; i++) {
        func_26E9E8(D_004279CC + i * 0x28 + 0x14);
    }
}
