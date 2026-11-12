#include "common.h"

extern u8 *D_0042A570 __attribute__((section(".data")));
extern u8 *D_0042139C __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));

u8 *func_0028BAA8(s32 size);
u8 *func_002B24C8(u8 *a0, s32 a1, s32 a2);
void Res_RelocateOffsets(void *arg0, u8 *arg1, u8 *arg2);
void func_0026E7F0(u8 *a0, u8 *a1, u8 *a2);
void func_0026EAE0(u8 *a0, s32 a1);
void func_00248708(u8 *a0, u8 *a1, u8 *a2, u8 *a3);
s32 func_0024ACB8(s32 arg0, s32 arg1);
void func_003F0748(s32 a0);

/* 0x003F0BF8(idx): builds object G = *D_0042A570 (0x36D4 bytes) from the resource table at D_0042139C[idx]:
   relocates sub-blocks (REL(off) = G4 + ((*(u32*)(G4+off) >> 2) << 2)), fills the sprite/layout pointers, allocates
   the four work buffers, validates the two D_3876A4 slots (stride 0x14) and seeds the two selections. */
s32 func_003F0BF8(s32 arg0) {
    u8 *sp0;
    u8 *G;
    u8 *G4;
    s32 i, s1, s3, v;

#define REL(off) (G4 + ((*(u32 *)(G4 + (off)) >> 2) << 2))

    sp0 = 0;
    D_0042A570 = func_0028BAA8(0x36D4);
    G = D_0042A570;
    __builtin_memset(G, 0, 0x36D4);
    {
        u8 *t = D_0042139C + arg0 * 4;
        *(u8 **)G = D_0042139C + ((*(u32 *)t >> 2) << 2);
    }
    *(u8 **)(G + 4) = func_002B24C8(*(u8 **)G, 0, 0);
    G4 = *(u8 **)(G + 4);
    sp0 = REL(0x10);
    Res_RelocateOffsets(&sp0, sp0, sp0);
    *(u8 **)(G + 0x114) = sp0;
    G4 = *(u8 **)(G + 4);
    sp0 = REL(0x8);
    Res_RelocateOffsets(&sp0, sp0, sp0);
    *(s32 *)(G + 0x138) = *(s32 *)(sp0 + 0x10);
    G4 = *(u8 **)(G + 4);
    sp0 = REL(0x60);
    Res_RelocateOffsets(&sp0, sp0, sp0);
    *(s32 *)(G + 0x120) = *(s32 *)(sp0 + 0x10);
    G4 = *(u8 **)(G + 4);
    sp0 = REL(0x58);
    Res_RelocateOffsets(&sp0, sp0, sp0);
    *(s32 *)(G + 0x12C) = *(s32 *)(sp0 + 0x10);
    G4 = *(u8 **)(G + 4);
    sp0 = REL(0x5C);
    Res_RelocateOffsets(&sp0, sp0, sp0);
    *(s32 *)(G + 0x118) = *(s32 *)(sp0 + 0x10);
    G4 = *(u8 **)(G + 4);
    sp0 = REL(0x14);
    Res_RelocateOffsets(&sp0, sp0, sp0);
    *(s32 *)(G + 0x11C) = *(s32 *)(sp0 + 0x10);
    G4 = *(u8 **)(G + 4);
    sp0 = REL(0x1C);
    Res_RelocateOffsets(&sp0, sp0, sp0);
    *(s32 *)(G + 0x128) = *(s32 *)(sp0 + 0x10);
    G4 = *(u8 **)(G + 4);
    func_0026E7F0(G + 0x4C, REL(0x4), G + 0x118);
    func_0026EAE0(G + 0x4C, 0x3C);
    G4 = *(u8 **)(G + 4);
    sp0 = REL(0x34);
    Res_RelocateOffsets(&sp0, sp0, sp0);
    *(s32 *)(G + 0x160) = *(s32 *)(sp0 + 0x10);
    *(s32 *)(G + 0x168) = *(s32 *)(sp0 + 0x10) + 0x40;
    *(s32 *)(G + 0x164) = *(s32 *)(sp0 + 0x10) + 0x80;
    *(s32 *)(G + 0x16C) = *(s32 *)(sp0 + 0x10) + 0xC0;
    G4 = *(u8 **)(G + 4);
    func_0026E7F0(G + 0x24, REL(0x38), G + 0x160);
    func_0026EAE0(G + 0x24, 0x3C);
    G4 = *(u8 **)(G + 4);
    sp0 = REL(0x18);
    Res_RelocateOffsets(&sp0, sp0, sp0);
    *(s32 *)(G + 0x148) = *(s32 *)(sp0 + 0x10);
    *(s32 *)(G + 0x14C) = *(s32 *)(sp0 + 0x10) + 0x40;
    *(s32 *)(G + 0x150) = *(s32 *)(sp0 + 0x10) + 0x80;
    G4 = *(u8 **)(G + 4);
    sp0 = REL(0x68);
    Res_RelocateOffsets(&sp0, sp0, sp0);
    *(s32 *)(G + 0x154) = *(s32 *)(sp0 + 0x10);
    G4 = *(u8 **)(G + 4);
    sp0 = REL(0x64);
    Res_RelocateOffsets(&sp0, sp0, sp0);
    *(s32 *)(G + 0x158) = *(s32 *)(sp0 + 0x10);
    *(s32 *)(G + 0x15C) = *(s32 *)(sp0 + 0x10) + 0x40;
    G4 = *(u8 **)(G + 4);
    func_0026E7F0(G + 0xC4, REL(0x20), G + 0x148);
    func_0026EAE0(G + 0xC4, 0x3C);
    G4 = *(u8 **)(G + 4);
    func_0026E7F0(G + 0xEC, REL(0x24), G + 0x148);
    func_0026EAE0(G + 0xEC, 0x3C);
    G4 = *(u8 **)(G + 4);
    sp0 = REL(0x48);
    Res_RelocateOffsets(&sp0, sp0, sp0);
    *(s32 *)(G + 0x178) = *(s32 *)(sp0 + 0x10);
    *(s32 *)(G + 0x170) = *(s32 *)(sp0 + 0x10) + 0x40;
    G4 = *(u8 **)(G + 4);
    sp0 = REL(0x50);
    Res_RelocateOffsets(&sp0, sp0, sp0);
    *(s32 *)(G + 0x1C8) = *(s32 *)(sp0 + 0x10);
    *(s32 *)(G + 0x1C0) = *(s32 *)(sp0 + 0x10) + 0x40;
    G4 = *(u8 **)(G + 4);
    sp0 = REL(0x40);
    Res_RelocateOffsets(&sp0, sp0, sp0);
    *(s32 *)(G + 0x174) = *(s32 *)(sp0 + 0x10);
    *(s32 *)(G + 0x1C4) = *(s32 *)(sp0 + 0x10);
    G4 = *(u8 **)(G + 4);
    sp0 = REL(0x3C);
    Res_RelocateOffsets(&sp0, sp0, sp0);
    *(s32 *)(G + 0x19C) = *(s32 *)(sp0 + 0x10);
    *(s32 *)(G + 0x1A0) = *(s32 *)(sp0 + 0x10) + 0x40;
    *(s32 *)(G + 0x198) = *(s32 *)(sp0 + 0x10) + 0x80;
    *(s32 *)(G + 0x1EC) = *(s32 *)(sp0 + 0x10);
    *(s32 *)(G + 0x1F0) = *(s32 *)(sp0 + 0x10) + 0x40;
    *(s32 *)(G + 0x1E8) = *(s32 *)(sp0 + 0x10) + 0x80;
    G4 = *(u8 **)(G + 4);
    func_0026E7F0(G + 0x74, REL(0x44), G + 0x170);
    func_0026EAE0(G + 0x74, 0x3C);
    G4 = *(u8 **)(G + 4);
    func_0026E7F0(G + 0x9C, REL(0x4C), G + 0x1C0);

    G4 = *(u8 **)(G + 4);
    *(u8 **)(G + 0x18) = func_002B24C8(REL(0xC), 0, 0);
    i = 0;
    do {
        u8 *b = *(u8 **)(G + 0x18);
        u8 *p = b + ((*(u32 *)(b + i * 4 + 4) >> 2) << 2);
        i++;
        sp0 = p;
        Res_RelocateOffsets(&sp0, p, p);
    } while (i < 0x86);

    G4 = *(u8 **)(G + 4);
    *(u8 **)(G + 0x258) = REL(0x28) + 4;
    *(s32 *)(G + 0x254) = *(s32 *)REL(0x28);
    func_00248708(G + 0x260, G + 0x264, G + 0x254, G + 0x258);
    *(s32 *)(G + 0x254) = *(s32 *)(G + 0x260);
    *(u8 **)(G + 0x258) = G + 0x264;
    *(u8 **)(G + 0x25C) = G + 0x1A74;
    *(s32 *)(G + 0x36B4) = *(s32 *)(G + 0x254) / 7;
    G4 = *(u8 **)(G + 4);
    *(u8 **)(G + 0x1C) = REL(0x2C);
    *(u8 **)(G + 0x20) = REL(0x30);
    *(u8 **)(G + 0x36D0) = REL(0x54) + 4;
    *(u8 **)(G + 8) = func_0028BAA8(0x17800);
    *(u8 **)(G + 0xC) = func_0028BAA8(0x17800);
    *(u8 **)(G + 0x10) = func_0028BAA8(0x20560);
    *(u8 **)(G + 0x14) = func_0028BAA8(0x20560);
    *(s32 *)(G + 0x36B8) = 1;
    *(s32 *)(G + 0x218) = *(s32 *)(G + 0x218) | 2;

    s1 = 0;
    s3 = 1;
    do {
        s32 off = s1 + 0x390;
        v = func_0024ACB8(*(s32 *)(D_0042A570 + 0x258), *(s32 *)(D_3876A4 + off));
        s3--;
        if (v == 0) {
            *(s32 *)(D_3876A4 + off) = 0;
            *(s32 *)(D_3876A4 + s1 + 0x3B8) = 0;
            *(s32 *)(D_3876A4 + s1 + 0x408) = 0;
            *(s32 *)(D_3876A4 + s1 + 0x430) = 0;
        }
        s1 += 0x14;
    } while (s3 >= 0);

    G = D_0042A570;
    *(s32 *)(G + 0x21C) = *(s32 *)(D_3876A4 + 0x390) % 7;
    *(s32 *)(G + 0x220) = *(s32 *)(D_3876A4 + 0x3A4) % 7;
    *(s32 *)(G + 0x224) = *(s32 *)(D_3876A4 + 0x390) / 7;
    *(s32 *)(G + 0x228) = *(s32 *)(D_3876A4 + 0x3A4) / 7;
    *(s32 *)(G + 0x22C) = *(s32 *)(D_3876A4 + 0x408);
    *(s32 *)(G + 0x230) = *(s32 *)(D_3876A4 + 0x41C);
    *(s32 *)(G + 0x23C) = *(s32 *)(D_3876A4 + 0x430);
    *(s32 *)(G + 0x240) = *(s32 *)(D_3876A4 + 0x444);
    *(s32 *)(G + 0x244) = *(s32 *)(D_3876A4 + 0x430);
    *(s32 *)(G + 0x248) = *(s32 *)(D_3876A4 + 0x444);
    func_003F0748(0);
    func_003F0748(1);

    G = D_0042A570;
    i = 0;
    do {
        s32 row = *(s32 *)(G + 0x224 + i * 4);
        s32 col = *(s32 *)(G + 0x21C + i * 4);
        s32 sel = *(s32 *)(G + 0x22C + i * 4);
        u8 *base = *(u8 **)(G + 0x258 + i * 4) + (row * 7 + col) * 44;
        s32 cur = i;
        i++;
        *(s32 *)base = *(s32 *)(base + 8 + sel * 4);
        func_003F0748(cur);
        G = D_0042A570;
    } while (i < 2);

    {
        u8 *t = D_0042A570;
        u8 *e = *(u8 **)(t + 0x36D0) + *(s32 *)(D_3876A4 + 0x64) * 56;
        if (*(s32 *)(e + 0xC) != 2) {
            *(s32 *)(t + 0x218) = *(s32 *)(t + 0x218) | 0x800;
            return *(s32 *)(t + 0x218);
        }
        return *(s32 *)(e + 0xC);
    }
#undef REL
}
