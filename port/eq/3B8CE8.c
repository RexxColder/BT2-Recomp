#include "common.h"

extern u8 *D_004213B0 __attribute__((section(".data")));

void func_26E9E8(u8 *arg0);
s32 func_26EB70(u8 *arg0);
void func_297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

/* 0x003B8CE8 (G = D_004213B0): func_26E9E8(G+0x10) and func_26E9E8(G+0x28+0x10). If func_26EB70(G+0x10) has bit 8,
 * func_297FE0(2,1,0x20,0x20,1); bit 0x10: func_297FE0(2,0,0x40,0x40,1); bit 0x20: func_297FE0(2,2,0x40,0x40,1).
 * If G->0xCC & 0x30 and func_26EB70(G+0x38) & 0x200: if G->0xCC & 0x10 { G->0xD0--, if < 0 G->0xD0 = G->0xD4 - 1;
 * G->0xCC ^= 0x10 } else if G->0xCC & 0x20 { G->0xD0++, if G->0xD4 - 1 < G->0xD0 then G->0xD0 = 0; G->0xCC ^= 0x20 }. */
void func_003B8CE8(void) {
    s32 i;

    for (i = 0; i < 2; i++) {
        func_26E9E8(D_004213B0 + i * 0x28 + 0x10);
    }
    if (func_26EB70(D_004213B0 + 0x10) & 0x8) {
        func_297FE0(2, 1, 0x20, 0x20, 1);
    }
    if (func_26EB70(D_004213B0 + 0x10) & 0x10) {
        func_297FE0(2, 0, 0x40, 0x40, 1);
    }
    if (func_26EB70(D_004213B0 + 0x10) & 0x20) {
        func_297FE0(2, 2, 0x40, 0x40, 1);
    }

    if (!(*(s32 *)(D_004213B0 + 0xCC) & 0x30)) {
        return;
    }
    if (!(func_26EB70(D_004213B0 + 0x38) & 0x200)) {
        return;
    }
    if (*(s32 *)(D_004213B0 + 0xCC) & 0x10) {
        *(s32 *)(D_004213B0 + 0xD0) = *(s32 *)(D_004213B0 + 0xD0) - 1;
        if (*(s32 *)(D_004213B0 + 0xD0) < 0) {
            *(s32 *)(D_004213B0 + 0xD0) = *(s32 *)(D_004213B0 + 0xD4) - 1;
        }
        *(s32 *)(D_004213B0 + 0xCC) = *(s32 *)(D_004213B0 + 0xCC) ^ 0x10;
    } else if (*(s32 *)(D_004213B0 + 0xCC) & 0x20) {
        *(s32 *)(D_004213B0 + 0xD0) = *(s32 *)(D_004213B0 + 0xD0) + 1;
        if (*(s32 *)(D_004213B0 + 0xD4) - 1 < *(s32 *)(D_004213B0 + 0xD0)) {
            *(s32 *)(D_004213B0 + 0xD0) = 0;
        }
        *(s32 *)(D_004213B0 + 0xCC) = *(s32 *)(D_004213B0 + 0xCC) ^ 0x20;
    }
}
