#include "common.h"

void *memset(void *arg0, s32 arg1, s32 arg2);

extern u8 *D_00427330 __attribute__((section(".data")));
extern u8 *D_004213A4 __attribute__((section(".data")));
extern u32 D_004274F0[12] __attribute__((section(".data")));

u8 *func_28BAA8(s32);
u8 *func_2B24C8(u8 *, s32, s32);
void Res_RelocateOffsets(void *, void *, void *);
void func_26E7F0(void *, void *, void *);
void func_26EAE0(void *, s32);
s32 Font_GetGlyphHeight(void);
s32 func_2A0EA8(void *);

u8 *func_003DEC38(s32 arg0) {
    u8 *g;
    u8 *g4;
    s32 i;
    u32 t;

    g = func_28BAA8(0x108);
    D_00427330 = g;
    memset(g, 0, 0x108);
    *(u8 **)g = D_004213A4 + (*(u32 *)(D_004213A4 + 4 * arg0) & ~3u);
    *(u8 **)(g + 4) = func_2B24C8(*(u8 **)g, 0, 0);

    for (i = 0; i < 12; i++) {
        t = D_004274F0[i];
        g4 = *(u8 **)(D_00427330 + 4);
        Res_RelocateOffsets(D_00427330 + (4 * i) + 0x64,
                            g4 + (*(u32 *)(g4 + 4 * t) & ~3u),
                            g4 + (*(u32 *)(g4 + 4 * t) & ~3u));
    }

    g = D_00427330;
    *(u32 *)(g + 0x98) = *(u32 *)(*(u8 **)(g + 0x68) + 0x10);
    *(u32 *)(g + 0x94) = *(u32 *)(*(u8 **)(g + 0x68) + 0x10) + 0x40;
    *(u32 *)(g + 0x9C) = *(u32 *)(*(u8 **)(g + 0x90) + 0x10);
    *(u32 *)(g + 0xA0) = *(u32 *)(*(u8 **)(g + 0x6C) + 0x10);
    *(u32 *)(g + 0xA8) = *(u32 *)(*(u8 **)(g + 0x74) + 0x10);
    *(u32 *)(g + 0xAC) = *(u32 *)(*(u8 **)(g + 0x70) + 0x10);
    *(u32 *)(g + 0xB0) = *(u32 *)(*(u8 **)(g + 0x70) + 0x10) + 0x40;
    *(u32 *)(g + 0xB4) = *(u32 *)(*(u8 **)(g + 0x78) + 0x10);
    *(u32 *)(g + 0xB8) = *(u32 *)(*(u8 **)(g + 0x7C) + 0x10);
    *(u32 *)(g + 0xC0) = *(u32 *)(*(u8 **)(g + 0x64) + 0x10);
    *(u32 *)(g + 0xBC) = *(u32 *)(*(u8 **)(g + 0x64) + 0x10) + 0x40;
    *(u32 *)(g + 0xC4) = *(u32 *)(*(u8 **)(g + 0x8C) + 0x10);
    *(u32 *)(g + 0xC8) = *(u32 *)(*(u8 **)(g + 0x88) + 0x10) + 0x40;
    *(u32 *)(g + 0xCC) = *(u32 *)(*(u8 **)(g + 0x88) + 0x10);
    *(u32 *)(g + 0xD0) = *(u32 *)(*(u8 **)(g + 0x84) + 0x10);
    *(u32 *)(g + 0xD4) = *(u32 *)(*(u8 **)(g + 0x84) + 0x10);
    *(u32 *)(g + 0xD8) = *(u32 *)(*(u8 **)(g + 0x84) + 0x10);

    g4 = *(u8 **)(g + 4);
    func_26E7F0(g + 0x14, g4 + (*(u32 *)(g4 + 4) & ~3u), g + 0x94);
    func_26EAE0(g + 0x14, 0x3C);

    g = D_00427330;
    g4 = *(u8 **)(g + 4);
    func_26E7F0(g + 0x3C, g4 + (*(u32 *)(g4 + 0x18) & ~3u), g + 0xC4);

    g = D_00427330;
    g4 = *(u8 **)(g + 4);
    *(u8 **)(g + 0xC) = g4 + (*(u32 *)(g4 + 0x40) & ~3u);
    *(u8 **)(g + 0x8) = g4 + (*(u32 *)(g4 + 0x3C) & ~3u);
    *(u8 **)(g + 0x10) = g4 + (*(u32 *)(g4 + 0x24) & ~3u);
    *(u32 *)(g + 0x100) = Font_GetGlyphHeight() + 2;

    g = D_00427330;
    *(u32 *)(g + 0x104) = func_2A0EA8(*(u8 **)(g + 0x10)
        + (*(u32 *)(*(u8 **)(g + 0x10) + 4 * *(u32 *)(g + 0xE4) + 0x414) & ~3u));
    *(u32 *)(g + 0xF8) = 0;
    *(u32 *)(g + 0xFC) = 0;
    return g;
}
