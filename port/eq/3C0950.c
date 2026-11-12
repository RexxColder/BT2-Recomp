#include "common.h"

extern u8 *D_00421C98 __attribute__((section(".data")));
extern u8 *D_004213A8 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));
extern u8 D_00421EF0[] __attribute__((section(".data")));
extern u8 D_00421F28[] __attribute__((section(".data")));
extern u8 D_00421F58[] __attribute__((section(".data")));
extern u8 D_00421F60[] __attribute__((section(".data")));
extern u8 D_00421F90[] __attribute__((section(".data")));

extern u8 *func_28BAA8();
extern u8 *func_2B24C8();
extern s32 Res_RelocateOffsets();
extern s32 func_24BED8();
extern s32 func_26E7F0();
extern s32 func_26EAE0();
extern s32 func_29BB88();
extern s32 func_28A0B8();

/* GP(p, off): resource pointer stored in the word at p+off, offset by the 4-aligned self-relative value */
#define REL(base, off) ((base) + (*(u32 *)((base) + (off)) >> 2 << 2))
#define G D_00421C98
#define R4 (*(u8 **)(G + 4))
#define PUT(dst, src, add) (*(s32 *)(G + (dst)) = *(s32 *)(*(u8 **)(G + (src)) + 0x10) + (add))

/* 0x003C0950: allocates the 0x9B8-byte menu context G (D_00421C98), loads the resource pack index arg0 from
 * D_004213A8, relocates 14 sub-resources into G+0x90.., fills the texture/palette pointers (G+0xC8..), sets up three
 * display objects, two name buffers (G+0x47C, G+0x89C) and registers them with func_28A0B8. */
void func_003C0950(s32 arg0) {
    u8 sp[0x40] __attribute__((aligned(16)));
    u8 *p;
    s32 i;
    u8 *a1;
    u8 *a0;

    G = func_28BAA8(0x9B8);
    __builtin_memset(G, 0, 0x9B8);
    if (*(s32 *)(D_3876A4 + 0x4B4) & 1) {
        *(s32 *)(G + 0x134) = 1;
    }
    p = D_004213A8;
    a1 = p + (*(u32 *)(p + arg0 * 4) >> 2 << 2);
    *(u8 **)G = a1;
    *(u8 **)(G + 4) = func_2B24C8(*(u8 **)G, 0, 0);

    i = 0;
    do {
        __builtin_memcpy(sp, D_00421EF0, 0x38);
        a0 = G;
        a1 = R4;
        a1 = a1 + (*(u32 *)(a1 + *(s32 *)(sp + i * 4) * 4) >> 2 << 2);
        Res_RelocateOffsets(a0 + i * 4 + 0x90, a1, a1);
        i++;
    } while (i < 0xE);

    PUT(0xC8, 0xB0, 0x40);
    PUT(0xCC, 0x98, 0);
    PUT(0xD0, 0x98, 0);
    PUT(0xD4, 0x98, 0);
    PUT(0xE4, 0xA4, 0);
    PUT(0xE8, 0xA0, 0);
    PUT(0xEC, 0xB0, 0);
    PUT(0xF0, 0x94, 0);
    PUT(0xF4, 0xA8, 0);
    PUT(0xF8, 0xA8, 0x40);
    PUT(0xD8, 0x9C, 0);
    PUT(0xDC, 0x9C, 0);
    PUT(0xE0, 0x9C, 0);
    PUT(0xFC, 0xB8, 0);
    PUT(0x100, 0xC4, 0);
    PUT(0x104, 0xC0, 0);
    PUT(0x108, 0xBC, 0);
    PUT(0x110, 0xC4, 0x40);
    PUT(0x114, 0xB4, 0);
    PUT(0x120, 0x90, 0x40);
    PUT(0x11C, 0x90, 0);
    PUT(0x118, 0x90, 0x80);

    func_24BED8(REL(R4, 0x58), *(s32 *)(*(u8 **)(G + 0xAC) + 0x10));
    func_26E7F0(G + 0x68, REL(R4, 8), G + 0xC8);
    func_26EAE0(G + 0x68, 0x3C);
    func_26E7F0(G + 0x40, REL(R4, 0x3C), G + 0x114);
    func_26EAE0(G + 0x40, 0x3C);
    func_26E7F0(G + 0x18, REL(R4, 0x40), G + 0x118);
    func_26EAE0(G + 0x18, 0x3C);

    *(u8 **)(G + 8) = REL(R4, 0x34);
    *(u8 **)(G + 0xC) = REL(R4, 0x30);
    *(u8 **)(G + 0x10) = REL(R4, 0x50);
    *(u8 **)(G + 0x14) = REL(R4, 0x44);
    func_29BB88(REL(R4, 0x4C), *(s32 *)(G + 0x10));
    if (*(s32 *)(D_3876A4 + 0x4B4) & 1) {
        *(s32 *)(G + 0x134) = 1;
    } else {
        *(s32 *)(G + 0x134) = 0;
    }

    *(u8 **)(G + 0x164) = REL(R4, 0x5C);
    *(s32 *)(G + 0x170) = 0xD74E;
    __builtin_memcpy(G + 0x47C, D_00421F28, 0x2D);
    *(s32 *)(G + 0x580) = 0x18;
    func_28A0B8(G + 0x164, D_00421F58, -1, -1, 1);

    __builtin_memcpy(G + 0x89C, D_00421F60, 0x2B);
    *(s32 *)(G + 0x9A0) = 0x18;
    func_28A0B8(G + 0x584, D_00421F90, -1, -1, 0);

    *(u8 **)(G + 0x9B0) = REL(R4, 0x54) + 4;
    *(s32 *)(G + 0x128) = *(s32 *)(D_3876A4 + 0x4B8);
}
