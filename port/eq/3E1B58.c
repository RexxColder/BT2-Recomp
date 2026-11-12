#include "common.h"

extern u8 *D_004279C8 __attribute__((section(".data")));
extern u8 *D_00421398 __attribute__((section(".data")));
extern u8 D_004279E0[] __attribute__((section(".data")));
extern u8 *D_00387F2C __attribute__((section(".data")));

u8 *func_0028BAA8(s32 a0);
u8 *func_002B24C8(u8 *a0, u8 *a1, s32 *a2);
void Res_RelocateOffsets(u8 *a0, u8 *a1, u8 *a2);
void func_0026E7F0(u8 *a0, u8 *a1, u8 *a2);
void func_0026EAE0(u8 *a0, s32 a1);
void func_0029BB88(u8 *a0, u8 *a1);

#define G (D_004279C8)
#define W(off) (*(u32 *)(G + (off)))
/* *(*(G + off) + 0x10) */
#define P(off) (*(s32 *)(*(u8 **)(G + (off)) + 0x10))

/* Loads resource arg0 (index into the D_00421398 offset table), builds the 5x8 table at G+0xCC (read from the jump
 * tables 0x427A40..0x427AC0, values below), relocates 14 sub resources and caches pointers into G. */
void func_003E1B58(s32 arg0) {
    static const s32 tab[5][8] = {
        {2, 1, 0, 3, 4, 5, 6, 7},
        {3, 2, 0, 1, 4, 5, 6, 7},
        {2, 0, 1, 3, 6, 7, 4, 5},
        {3, 2, 0, 1, 6, 4, 7, 5},
        {5, 7, 4, 6, 2, 1, 0, 3},
    };
    u8 sp[0x40];
    s32 i;
    s32 j;
    u8 *a1;
    u8 *a0;

    G = func_0028BAA8(900);
    __builtin_memset(G, 0, 900);
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 8; j++) {
            *(s32 *)(G + 0xCC + ((i * 8 + j) << 2)) = tab[i][j];
        }
    }

    a0 = D_00421398;
    *(u8 **)(G + 0) = a0 + (*(u32 *)(a0 + arg0 * 4) & ~3u);
    *(u8 **)(G + 4) = func_002B24C8(*(u8 **)G, 0, 0);

    __builtin_memcpy(sp, D_004279E0, 0x38);
    for (i = 0; i < 14; i++) {
        a1 = *(u8 **)(G + 4);
        a1 = a1 + (*(u32 *)(a1 + *(s32 *)(sp + i * 4) * 4) & ~3u);
        Res_RelocateOffsets(G + i * 4 + 0x38, a1, a1);
    }

    *(s32 *)(G + 0x70) = P(0x64);
    *(s32 *)(G + 0x74) = P(0x6C);
    *(s32 *)(G + 0x78) = P(0x6C) + 0x40;
    *(s32 *)(G + 0x7C) = P(0x44);
    *(s32 *)(G + 0x80) = P(0x58);
    *(s32 *)(G + 0x84) = P(0x48);
    *(s32 *)(G + 0x88) = P(0x40);
    *(s32 *)(G + 0x8C) = P(0x5C);
    *(s32 *)(G + 0x90) = P(0x58) + 0x40;
    *(s32 *)(G + 0x94) = P(0x5C) + 0x40;
    *(s32 *)(G + 0x98) = P(0x50);
    *(s32 *)(G + 0x9C) = P(0x4C);
    *(s32 *)(G + 0xA0) = P(0x54);
    *(s32 *)(G + 0xA4) = P(0x68);
    *(s32 *)(G + 0xA8) = P(0x60);
    *(s32 *)(G + 0xAC) = P(0x60) + 0x40;
    *(s32 *)(G + 0xB0) = P(0x40) + 0x40;
    *(s32 *)(G + 0xB4) = P(0x68) + 0x40;
    *(s32 *)(G + 0xB8) = P(0x3C);

    a1 = *(u8 **)(G + 4);
    func_0026E7F0(G + 0x10, a1 + (*(u32 *)(a1 + 4) & ~3u), G + 0x70);
    func_0026EAE0(G + 0x10, 0x3C);

    a1 = *(u8 **)(G + 4);
    *(u8 **)(G + 8) = a1 + (*(u32 *)(a1 + 0x40) & ~3u);
    a1 = *(u8 **)(G + 4);
    *(u8 **)(G + 0xC) = a1 + (*(u32 *)(a1 + 0x44) & ~3u);
    a1 = *(u8 **)(G + 4);
    func_0029BB88(a1 + (*(u32 *)(a1 + 0x48) & ~3u), *(u8 **)(G + 8));

    *(s32 *)(G + 0x36C) = -1;
    __builtin_memcpy(G + 0x16C, D_00387F2C + 0x1008, 0xAC);
    *(s32 *)(G + 0xBC) = -1;
}
