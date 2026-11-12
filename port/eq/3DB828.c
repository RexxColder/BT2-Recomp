#include "common.h"

extern u8 *D_004263EC __attribute__((section(".data")));
extern u8 *D_003876AC __attribute__((section(".data")));
extern u8 *D_003876A4 __attribute__((section(".data")));
extern u8 *D_00387F2C __attribute__((section(".data")));

u8 *func_28BAA8(s32);
u8 *func_2B24C8(u8 *, s32, s32);
void Res_RelocateOffsets(void *, void *, void *);
void func_26E7F0(void *, void *, void *);
void func_26EAE0(void *, s32);
void func_24BED8(void *, s32);
void *memset(void *arg0, s32 arg1, s32 arg2);

u8 *func_003DB828(s32 arg0) {
    u8 *g;
    u8 *g4;
    u8 *tmp;
    u8 *dp;
    u8 *t;

    g = func_28BAA8(0x84);
    D_004263EC = g;
    memset(g, 0, 0x84);
    *(u8 **)g = D_003876AC + (*(u32 *)(D_003876AC + 4 * arg0) & ~3u);
    *(u8 **)(g + 4) = func_2B24C8(*(u8 **)g, 0, 0);

    g4 = *(u8 **)(g + 4);
    tmp = g4 + (*(u32 *)(g4 + 0x8) & ~3u);
    Res_RelocateOffsets(&tmp, tmp, tmp);
    *(u8 **)(g + 0x38) = tmp;

    g4 = *(u8 **)(g + 4);
    tmp = g4 + (*(u32 *)(g4 + 0x14) & ~3u);
    Res_RelocateOffsets(&tmp, tmp, tmp);
    *(u32 *)(g + 0x58) = *(u32 *)(tmp + 0x10);

    g4 = *(u8 **)(g + 4);
    tmp = g4 + (*(u32 *)(g4 + 0x1C) & ~3u);
    Res_RelocateOffsets(&tmp, tmp, tmp);
    *(u32 *)(g + 0x40) = *(u32 *)(tmp + 0x10);

    g4 = *(u8 **)(g + 4);
    tmp = g4 + (*(u32 *)(g4 + 0x18) & ~3u);
    Res_RelocateOffsets(&tmp, tmp, tmp);
    *(u32 *)(g + 0x54) = *(u32 *)(tmp + 0x10);
    *(u32 *)(g + 0x5C) = *(u32 *)(tmp + 0x10) + 0x40;

    g4 = *(u8 **)(g + 4);
    tmp = g4 + (*(u32 *)(g4 + 0xC) & ~3u);
    Res_RelocateOffsets(&tmp, tmp, tmp);
    *(u32 *)(g + 0x48) = *(u32 *)(tmp + 0x10);

    g4 = *(u8 **)(g + 4);
    tmp = g4 + (*(u32 *)(g4 + 0x24) & ~3u);
    Res_RelocateOffsets(&tmp, tmp, tmp);
    func_24BED8(g4 + (*(u32 *)(g4 + 0x34) & ~3u), *(s32 *)(tmp + 0x10));

    g4 = *(u8 **)(g + 4);
    tmp = g4 + (*(u32 *)(g4 + 0x20) & ~3u);
    Res_RelocateOffsets(&tmp, tmp, tmp);
    *(u32 *)(g + 0x44) = *(u32 *)(tmp + 0x10);
    *(u32 *)(g + 0x3C) = *(u32 *)(tmp + 0x10) + 0x40;

    g4 = *(u8 **)(g + 4);
    tmp = g4 + (*(u32 *)(g4 + 0x10) & ~3u);
    Res_RelocateOffsets(&tmp, tmp, tmp);
    *(u32 *)(g + 0x4C) = *(u32 *)(tmp + 0x10);
    *(u32 *)(g + 0x50) = *(u32 *)(tmp + 0x10);

    g4 = *(u8 **)(g + 4);
    func_26E7F0(g + 0x10, g4 + (*(u32 *)(g4 + 0x4) & ~3u), g + 0x3C);
    func_26EAE0(g + 0x10, 0x3C);

    g4 = *(u8 **)(g + 4);
    *(u8 **)(g + 0xC) = g4 + (*(u32 *)(g4 + 0x30) & ~3u);
    *(u8 **)(g + 0x8) = g4 + (*(u32 *)(g4 + 0x2C) & ~3u);

    dp = D_00387F2C;
    if ((*(u32 *)(dp + 0xA08) & 1u) != 0) {
        *(s32 *)(g + 0x6C) = 3;
    } else {
        *(s32 *)(g + 0x6C) = 2;
        if (*(s16 *)(dp + 0x2356) != 0) {
            *(s32 *)(g + 0x74) = 1;
            *(s32 *)(g + 0x78) = 0x33;
            *(u32 *)(dp + 0xA08) = *(u32 *)(dp + 0xA08) | 1u;
        }
    }

    t = D_003876A4;
    *(u32 *)(g + 0x64) = *(u32 *)(t + 0x490);
    return t;
}
