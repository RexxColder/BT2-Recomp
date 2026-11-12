#include "common.h"

extern u8 *D_004263EC __attribute__((section(".data")));
extern s32 D_003B0B00 __attribute__((section(".data")));
extern u8 *D_003876A4;

s32 func_0026EB60(u8 *arg0);
void func_003DC050(void *a0, s32 a1);
void func_00243A80(s32 a0, s32 a1, s32 a2);
void func_002493C0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);
void func_00297FE0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);

/* 0x003DC320: menu state step on G = D_004263EC, with the input word D_003B0B00 + 0x134 / + 0x144. The first test is
 * func_0026EB60(G + 0x10) != 0, else return. Path 0x144 & 0x10: G->0x80 = 0, G->0x64 steps back (wrapping to G->0x6C - 1),
 * func_003DC050(&D_003B0B00, 0x3B0000), then func_00297FE0(0, 0, 0x40, 0x40, 1). Path 0x144 & 0x40: G->0x80 = 0, G->0x64
 * steps forward (wrapping to 0 at G->0x6C), func_003DC050(G, 0x3B0000), then func_00297FE0(0, 0, ...). Otherwise: 0x134 &
 * 0x8000 with G->0x78 == 0 and G->0x64 == 0 sets G->0x78 = 1 and calls func_00297FE0(0, 1, ...); 0x134 & 0x4000 sets
 * *(P + 0x1C) from G->0x64 (0 -> 0x36, 1 -> 0x39, 2 -> 0x3A) where P = D_003876A4, sets G->0x60 |= 3, G->0x70 = 0xF and
 * calls func_00297FE0(0, 1, ...); 0x134 & 0x1000 calls func_00243A80(0, 0, 0), *arg0 = 0 and func_00297FE0(0, 2, ...);
 * else G->0x80++ and at 0xE10 sets G->0x68 = 9, calls func_002493C0(G->0xC, 0x36B2, 0x3ACB, 0, 9), G->0x80 = 0. */
void func_003DC320(s32 *arg0) {
    s32 a1;

    if (func_0026EB60(D_004263EC + 0x10) == 0) {
        return;
    }
    if (*(s32 *)((u8 *)&D_003B0B00 + 0x144) & 0x10) {
        *(s32 *)(D_004263EC + 0x80) = 0;
        *(s32 *)(D_004263EC + 0x64) = *(s32 *)(D_004263EC + 0x64) - 1;
        if (*(s32 *)(D_004263EC + 0x64) < 0) {
            *(s32 *)(D_004263EC + 0x64) = *(s32 *)(D_004263EC + 0x6C) - 1;
        }
        func_003DC050((void *)&D_003B0B00, 0x003B0000);
        func_00297FE0(0, 0, 0x40, 0x40, 1);
        return;
    }
    if (*(s32 *)((u8 *)&D_003B0B00 + 0x144) & 0x40) {
        *(s32 *)(D_004263EC + 0x80) = 0;
        *(s32 *)(D_004263EC + 0x64) = *(s32 *)(D_004263EC + 0x64) + 1;
        if (*(s32 *)(D_004263EC + 0x64) >= *(s32 *)(D_004263EC + 0x6C)) {
            *(s32 *)(D_004263EC + 0x64) = 0;
        }
        func_003DC050(D_004263EC, 0x003B0000);
        a1 = 0;
    } else {
        if ((*(s32 *)((u8 *)&D_003B0B00 + 0x134) & 0x8000) && *(s32 *)(D_004263EC + 0x78) == 0 &&
            *(s32 *)(D_004263EC + 0x64) == 0) {
            *(s32 *)(D_004263EC + 0x80) = 0;
            *(s32 *)(D_004263EC + 0x78) = 1;
            func_00297FE0(0, 1, 0x40, 0x40, 1);
            return;
        }
        if (*(s32 *)((u8 *)&D_003B0B00 + 0x134) & 0x4000) {
            *(s32 *)(D_004263EC + 0x80) = 0;
            switch (*(s32 *)(D_004263EC + 0x64)) {
            case 0:
                *(s32 *)(D_003876A4 + 0x1C) = 0x36;
                break;
            case 1:
                *(s32 *)(D_003876A4 + 0x1C) = 0x39;
                break;
            case 2:
                *(s32 *)(D_003876A4 + 0x1C) = 0x3A;
                break;
            }
            *(s32 *)(D_004263EC + 0x60) = *(s32 *)(D_004263EC + 0x60) | 1;
            *(s32 *)(D_004263EC + 0x60) = *(s32 *)(D_004263EC + 0x60) | 2;
            *(s32 *)(D_004263EC + 0x70) = 0xF;
            func_00297FE0(0, 1, 0x40, 0x40, 1);
            return;
        }
        if (*(s32 *)((u8 *)&D_003B0B00 + 0x134) & 0x1000) {
            *(s32 *)(D_004263EC + 0x80) = 0;
            func_00243A80(0, 0, 0);
            *arg0 = 0;
            a1 = 2;
        } else {
            *(s32 *)(D_004263EC + 0x80) = *(s32 *)(D_004263EC + 0x80) + 1;
            if (*(s32 *)(D_004263EC + 0x80) == 0xE10) {
                *(s32 *)(D_004263EC + 0x68) = 9;
                func_002493C0(*(s32 *)(D_004263EC + 0xC), 0x36B2, 0x3ACB, 0, *(s32 *)(D_004263EC + 0x68));
                *(s32 *)(D_004263EC + 0x80) = 0;
            }
            return;
        }
    }
    func_00297FE0(0, a1, 0x40, 0x40, 1);
}
