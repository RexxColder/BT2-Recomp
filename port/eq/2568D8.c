#include "common.h"

extern u8 *D_003879E8;
extern u8 *D_00387F2C;
extern u8 D_003879F0[] __attribute__((section(".data")));
extern u8 D_003B0B00[] __attribute__((section(".data")));
extern s32 D_003B0C34 __attribute__((section(".data")));

void func_00251030(s32 arg0, s32 arg1, s32 arg2);
void func_00251088(s32 arg0, s32 arg1);
void func_0026EB78(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_00298460(s32 arg0, s32 arg1, s32 arg2);

#define G(off) (*(s32 *)(D_003879E8 + (off)))

void func_002568D8(s32 arg0) {
    s32 s0;
    s32 s1;
    s32 s2;
    s32 v0;
    s32 a1;
    s32 a3;
    s32 bit;
    s32 i;
    s32 t144;

    if (!(G(0x4C) & 1)) {
        return;
    }

    if (G(0x4C) & 8) {
        if (D_003B0C34 & 0x1000) {
            G(0x54) = G(0x50);
            func_00251088(arg0, (s32)D_003879E8);
            func_00297FE0(0, 2, 0x40, 0x40, 1);
            G(0x4C) = G(0x4C) & ~8;
        } else if (D_003B0C34 & 0x4000) {
            func_00251088(arg0, (s32)D_003879E8);
            func_00297FE0(0, 1, 0x40, 0x40, 1);
            G(0x4C) = G(0x4C) & ~8;
            G(0x60) = G(0x60) | (1 << G(0x50));
            G(0x54) = G(0x50);
            a1 = G(0x5C);
            a3 = G(0x60);
            s0 = 0;
            do {
                bit = 1 << s0;
                s0 += 1;
                if (a3 & bit) {
                    a1 = a1 - 1;
                }
            } while (s0 < 7);
            if (a1 != 0) {
                G(0x50) = 0;
                if (G(0x60) & (1 << G(0x50))) {
                    v0 = G(0x50);
loop_22:
                    G(0x50) = v0 + 1;
                    if (G(0x50) >= 7) {
                        G(0x50) = 0;
                    }
                    if (G(0x60) & (1 << G(0x50))) {
                        v0 = G(0x50);
                        goto loop_22;
                    }
                }
            } else {
                func_0026EB78((s32)D_003879E8 + 4, (s32)D_003879F0, (s32)D_003879E8, a3);
                G(0x4C) = G(0x4C) & ~2;
                if (*(s16 *)(D_00387F2C + 0x2526) != 0) {
                    *(s16 *)(D_00387F2C + 0x2526) = (s16)((u16)*(s16 *)(D_00387F2C + 0x2526) - 1);
                }
                s0 = 0;
                s2 = 1;
                s1 = 0x60;
                do {
                    bit = s2 << s0;
                    s0 += 1;
                    if (G(0x60) & bit) {
                        v0 = *(s32 *)(D_003879E8 + s1 + 4);
                        func_00298460(v0,
                                      *(s32 *)(G(0x58) + v0 * 0x30 + 0x10), 1);
                    }
                    s1 += 4;
                } while (s0 < 7);
                s0 = 0;
                i = 0x24C0;
                do {
                    s0 += 1;
                    *(s16 *)(D_00387F2C + i + 2) = 0;
                    i += 4;
                } while (s0 < 7);
            }
        }
        return;
    }

    t144 = *(s32 *)(D_003B0B00 + 0x144);
    if (t144 & 0x10) {
        v0 = G(0x50);
        for (;;) {
            G(0x50) = v0 - 1;
            if (G(0x50) < 0) {
                G(0x50) = 6;
            }
            if (!(G(0x60) & (1 << G(0x50)))) {
                break;
            }
            v0 = G(0x50);
        }
        func_00297FE0(0, 0, 0x40, 0x40, 1);
    } else if (!(t144 & 0x40)) {
        if (*(s32 *)(D_003B0B00 + 0x134) & 0x4000) {
            G(0x4C) = G(0x4C) | 8;
            func_00251030(0x1E, (s32)D_003879E8, (s32)D_003879E8);
            func_00297FE0(0, 1, 0x40, 0x40, 1);
        }
    } else {
        v0 = G(0x50);
        for (;;) {
            G(0x50) = v0 + 1;
            if (G(0x50) >= 7) {
                G(0x50) = 0;
            }
            if (!(G(0x60) & (1 << G(0x50)))) {
                break;
            }
            v0 = G(0x50);
        }
        func_00297FE0(0, 0, 0x40, 0x40, 1);
    }
}
