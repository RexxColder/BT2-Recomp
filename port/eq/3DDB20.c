#include "common.h"

extern u8 *D_0042732C __attribute__((section(".data")));
extern u8 *D_00387F2C __attribute__((section(".data")));
extern s32 D_003B0C34 __attribute__((section(".data")));

s32 rand(void);
s32 func_1011A0(s32 arg0);
void func_101608(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

/* 0x003DDB20: G = D_0042732C. If G->0x764 == 0 return. s0 = G->0x114 advanced G->0x110 times along +8 (stopping at
 * 0). If s0 == 0 return. mode = G->0x764: 1 -> G->0x768 = rand() % 40; idx = s0->4 * 100 + G->0x768 +
 * ((*(D_00387F2C+0x1008) & 1) ? 0x74F3 : 0x3E43); if (*0x3B0C34 & 0x1C00) G->0x764 = 0; else if
 * func_1011A0(idx) >= 0x801, G->0x764 = 0xA; 0xA -> func_101608(0, s0->4, G->0x768, 0, 0), G->0x764 = 0. */
void func_003DDB20(void) {
    u8 *s0;
    s32 n;
    s32 mode;
    s32 a1;
    s32 idx;

    if (*(s32 *)(D_0042732C + 0x764) == 0) {
        return;
    }
    s0 = *(u8 **)(D_0042732C + 0x114);
    n = *(s32 *)(D_0042732C + 0x110);
    if (n > 0) {
        do {
            if (s0 != 0) {
                s0 = *(u8 **)(s0 + 8);
            }
            n = n - 1;
        } while (n != 0);
    }
    if (s0 == 0) {
        return;
    }

    mode = *(s32 *)(D_0042732C + 0x764);
    if (mode == 1) {
        *(s32 *)(D_0042732C + 0x768) = rand() % 40;
        a1 = *(s32 *)(s0 + 4);
        idx = a1 * 100 + *(s32 *)(D_0042732C + 0x768);
        if (*(s32 *)(D_00387F2C + 0x1008) & 1) {
            idx = idx + 0x74F3;
        } else {
            idx = idx + 0x3E43;
        }
        if (D_003B0C34 & 0x1C00) {
            *(s32 *)(D_0042732C + 0x764) = 0;
            return;
        }
        if (func_1011A0(idx) >= 0x801) {
            *(s32 *)(D_0042732C + 0x764) = 0xA;
        }
    } else if (mode == 0xA) {
        func_101608(0, *(s32 *)(s0 + 4), *(s32 *)(D_0042732C + 0x768), 0, 0);
        *(s32 *)(D_0042732C + 0x764) = 0;
    }
}
