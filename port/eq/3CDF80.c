#include "common.h"

extern u8 *D_0042311C __attribute__((section(".data")));
extern u8 *D_00421390 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));
extern u8 *D_387F2C __attribute__((section(".data")));
extern u8 D_00424D98[] __attribute__((section(".data")));
extern u8 D_00424DA8[] __attribute__((section(".data")));
extern u8 D_00424DB8[] __attribute__((section(".data")));
extern u8 D_00424DE8[] __attribute__((section(".data")));

u8 *func_0028BAA8(s32 size);
u8 *func_002B24C8(u8 *a0, s32 a1, s32 a2);
void Res_RelocateOffsets(void *arg0, u8 *arg1, u8 *arg2);
void func_0026E7F0(u8 *a0, u8 *a1, u8 *a2);
void func_0026EAE0(u8 *a0, s32 a1);
void func_0026EB78(u8 *a0, u8 *a1);
void func_0024BED8(u8 *a0, s32 a1);
void func_0029BB88(u8 *a0, u8 *a1);
void func_002984E0(s32 a0);
void func_0028A0B8(u8 *a0, u8 *a1, s32 a2, s32 a3, s32 a4);
s32 func_003CD988(void);
void func_003CDBC8(void);
s32 McCard_Checksum(u8 *a0, s32 a1, s32 a2);

/* 0x003CDF80(idx): builds the result-screen object G = *D_0042311C (0x580 bytes): loads the resource table
   whose offset sits at D_00421390[idx], relocates its sub-blocks (offsets in G4 + (*(u32*)(G4+off) >> 2 << 2)) and
   sets up the layouts, then updates the save data (D_387F2C) counters for the win / second place cases. */
s32 func_003CDF80(s32 arg0) {
    u8 *sp0;
    u8 *G;
    u8 *G4;
    s32 v;
    s32 idx;
    u8 *F;

#define REL(off) (G4 + ((*(u32 *)(G4 + (off)) >> 2) << 2))

    sp0 = 0;
    D_0042311C = func_0028BAA8(0x580);
    G = D_0042311C;
    __builtin_memset(G, 0, 0x580);
    {
        u8 *t = D_00421390 + arg0 * 4;
        *(u8 **)G = D_00421390 + ((*(u32 *)t >> 2) << 2);
    }
    *(u8 **)(G + 4) = func_002B24C8(*(u8 **)G, 0, 0);
    v = *(s32 *)(D_3876A4 + 0x88);
    if (v & 2) {
        *(s32 *)(G + 0x118) = *(s32 *)(G + 0x118) | 4;
    } else if (v & 4) {
        *(s32 *)(G + 0x118) = *(s32 *)(G + 0x118) | 8;
    }

    G4 = *(u8 **)(G + 4);
    sp0 = REL(8);
    Res_RelocateOffsets(&sp0, sp0, sp0);
    *(s32 *)(G + 0xFC) = *(s32 *)(sp0 + 0x10);
    *(s32 *)(G + 0x100) = *(s32 *)(sp0 + 0x10) + 0x40;
    *(s32 *)(G + 0xF8) = *(s32 *)(sp0 + 0x10) + 0x80;

    G4 = *(u8 **)(G + 4);
    func_0026E7F0(G + 0x14, REL(0xC), G + 0xF8);
    func_0026EAE0(G + 0x14, 0x3C);

    if (*(s32 *)(G + 0x118) & 4) {
        G4 = *(u8 **)(G + 4);
        sp0 = REL(0x70);
        Res_RelocateOffsets(&sp0, sp0, sp0);
        *(s32 *)(G + 0x104) = *(s32 *)(sp0 + 0x10);
    } else {
        G4 = *(u8 **)(G + 4);
        sp0 = REL(0x34);
        Res_RelocateOffsets(&sp0, sp0, sp0);
        *(s32 *)(G + 0x104) = *(s32 *)(sp0 + 0x10);
        *(s32 *)(G + 0x108) = *(s32 *)(sp0 + 0x10) + 0x40;
    }

    G4 = *(u8 **)(G + 4);
    if (*(s32 *)(G + 0x118) & 4) {
        v = *(s32 *)(G4 + 0x74);
    } else {
        v = *(s32 *)(G4 + 0x38);
    }
    func_0026E7F0(G + 0x64, G4 + (((u32)v >> 2) << 2), G + 0x104);
    func_0026EAE0(G + 0x64, 0x3C);

    G4 = *(u8 **)(G + 4);
    sp0 = REL(0x7C);
    Res_RelocateOffsets(&sp0, sp0, sp0);
    *(s32 *)(G + 0x10C) = *(s32 *)(sp0 + 0x10);
    *(s32 *)(G + 0x110) = *(s32 *)(sp0 + 0x10) + 0x80;
    *(s32 *)(G + 0x114) = *(s32 *)(sp0 + 0x10) + 0x40;

    G4 = *(u8 **)(G + 4);
    func_0026E7F0(G + 0x3C, REL(0x80), G + 0x10C);
    func_0026EAE0(G + 0x3C, 0x3C);

    G4 = *(u8 **)(G + 4);
    if (*(s32 *)(G + 0x118) & 4) {
        v = *(s32 *)(G4 + 0x88);
    } else {
        v = *(s32 *)(G4 + 0x1C);
    }
    sp0 = G4 + (((u32)v >> 2) << 2);
    Res_RelocateOffsets(&sp0, sp0, sp0);
    *(s32 *)(G + 0xB4) = *(s32 *)(sp0 + 0x10);
    *(s32 *)(G + 0xB8) = *(s32 *)(sp0 + 0x10);
    *(s32 *)(G + 0xBC) = *(s32 *)(sp0 + 0x10);

    G4 = *(u8 **)(G + 4);
    sp0 = REL(0x44);
    Res_RelocateOffsets(&sp0, sp0, sp0);
    *(s32 *)(G + 0xC0) = *(s32 *)(sp0 + 0x10);
    *(s32 *)(G + 0xC4) = *(s32 *)(sp0 + 0x10) + 0x40;

    G4 = *(u8 **)(G + 4);
    sp0 = REL(0x48);
    Res_RelocateOffsets(&sp0, sp0, sp0);
    G4 = *(u8 **)(G + 4);
    func_0024BED8(REL(0x98), *(s32 *)(sp0 + 0x10));

    G4 = *(u8 **)(G + 4);
    sp0 = REL(0x94);
    Res_RelocateOffsets(&sp0, sp0, sp0);
    *(s32 *)(G + 0xEC) = *(s32 *)(sp0 + 0x10);

    G4 = *(u8 **)(G + 4);
    sp0 = REL(0x6C);
    Res_RelocateOffsets(&sp0, sp0, sp0);
    *(s32 *)(G + 0xC8) = *(s32 *)(sp0 + 0x10);
    *(s32 *)(G + 0xD8) = *(s32 *)(sp0 + 0x10) + 0x40;
    *(s32 *)(G + 0xE0) = *(s32 *)(sp0 + 0x10) + 0x80;
    *(s32 *)(G + 0xE4) = *(s32 *)(sp0 + 0x10) + 0xC0;

    G4 = *(u8 **)(G + 4);
    sp0 = REL(0x60);
    Res_RelocateOffsets(&sp0, sp0, sp0);
    *(s32 *)(G + 0xCC) = *(s32 *)(sp0 + 0x10);
    *(s32 *)(G + 0xDC) = *(s32 *)(sp0 + 0x10) + 0x40;

    G4 = *(u8 **)(G + 4);
    sp0 = REL(0x68);
    Res_RelocateOffsets(&sp0, sp0, sp0);
    *(s32 *)(G + 0xD0) = *(s32 *)(sp0 + 0x10);
    *(s32 *)(G + 0xD4) = *(s32 *)(sp0 + 0x10) + 0x40;

    G4 = *(u8 **)(G + 4);
    sp0 = REL(0x64);
    Res_RelocateOffsets(&sp0, sp0, sp0);
    *(s32 *)(G + 0xF4) = *(s32 *)(sp0 + 0x10);
    *(s32 *)(G + 0xE8) = *(s32 *)(sp0 + 0x10) + 0x40;
    *(s32 *)(G + 0xF0) = 0;

    G4 = *(u8 **)(G + 4);
    func_0026E7F0(G + 0x8C, REL(0x5C), G + 0xB4);
    func_0026EAE0(G + 0x8C, 0x3C);

    G4 = *(u8 **)(G + 4);
    *(u8 **)(G + 8) = REL(0x4C);
    *(u8 **)(G + 0xC) = REL(0x84);
    *(u8 **)(G + 0x10) = REL(0x8C);
    *(u8 **)(G + 0x140) = REL(0x90) + 4;
    *(u8 **)(G + 0x13C) = REL(0x78);

    v = *(s32 *)(G + 0x118);
    if (v & 4) {
        u16 *p;
        s32 *q;
        *(s32 *)(G + 0x134) = func_003CD988();
        func_003CDBC8();
        F = D_387F2C;
        p = (u16 *)(F + *(s32 *)(D_3876A4 + 0x8C) * 2 + 0x40C);
        *p = *p + 1;
        p = (u16 *)(D_387F2C + *(s32 *)(D_3876A4 + 0x8C) * 2 + 0x40C);
        if (*p >= 0x2710) {
            *p = 0x270F;
        }
        q = (s32 *)(D_387F2C + *(s32 *)(D_3876A4 + 0x8C) * 4 + 0x418);
        *q = *q + *(s32 *)(G + 0x134);
        q = (s32 *)(D_387F2C + *(s32 *)(D_3876A4 + 0x8C) * 4 + 0x418);
        if ((u32)0x3B9AC9FF < (u32)*q) {
            *q = 0x3B9AC9FF;
        }
        func_002984E0(*(s32 *)(G + 0x134));
        F = D_387F2C;
        *(s32 *)(F + 0x408) = *(s32 *)(F + 0x408) |
            (1 << ((*(s32 *)(D_3876A4 + 0x8C) * 4 + *(s32 *)(D_3876A4 + 0x90)) & 31));
        if (*(s16 *)(D_387F2C + 0x424) < 4) {
            *(s32 *)(G + 0x120) = 9;
        } else {
            *(s32 *)(G + 0x120) = 10;
        }
    } else if (v & 8) {
        u16 *p;
        s32 *q;
        *(s32 *)(G + 0x134) = func_003CD988();
        p = (u16 *)(D_387F2C + *(s32 *)(D_3876A4 + 0x8C) * 2 + 0x412);
        *p = *p + 1;
        p = (u16 *)(D_387F2C + *(s32 *)(D_3876A4 + 0x8C) * 2 + 0x412);
        if (*p >= 0x2710) {
            *p = 0x270F;
        }
        q = (s32 *)(D_387F2C + *(s32 *)(D_3876A4 + 0x8C) * 4 + 0x418);
        *q = *q + *(s32 *)(G + 0x134);
        q = (s32 *)(D_387F2C + *(s32 *)(D_3876A4 + 0x8C) * 4 + 0x418);
        if ((u32)0x3B9AC9FF < (u32)*q) {
            *q = 0x3B9AC9FF;
        }
        func_002984E0(*(s32 *)(G + 0x134));
        *(s32 *)(G + 0x120) = 8;
        func_0026EB78(G + 0x8C, D_00424D98);
    } else {
        *(s32 *)(G + 0x120) = 7;
        func_0026EB78(G + 0x8C, D_00424DA8);
    }

    *(s32 *)(G + 0x11C) = -1;
    G4 = *(u8 **)(G + 4);
    *(u8 **)(G + 0x14C) = REL(0xA4);
    G4 = *(u8 **)(G + 4);
    func_0029BB88(REL(0xA0), *(u8 **)(G + 0x14C));
    *(s32 *)(G + 0x150) = 0;
    *(s32 *)(G + 0x158) = -1;
    G4 = *(u8 **)(G + 4);
    *(u8 **)(G + 0x160) = REL(0xA8);
    *(s32 *)(G + 0x16C) = 0xD74E;
    __builtin_memcpy(G + 0x478, D_00424DB8, 0x2D);
    *(s32 *)(G + 0x57C) = 0x18;
    func_0028A0B8(G + 0x160, D_00424DE8, -1, -1, 1);
    return McCard_Checksum(D_387F2C, 0x4000, 1);
#undef REL
}
