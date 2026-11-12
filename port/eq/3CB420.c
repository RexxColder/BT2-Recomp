#include "common.h"

extern s32 func_0028BAA8();
extern s32 func_002B24C8();
extern s32 Res_RelocateOffsets();
extern s32 func_0024BED8();
extern s32 func_0026E7F0();
extern s32 func_0026EAE0();
extern s64 GetTimerSystemTime();
extern s32 func_00325370();
extern s32 rand(void);

extern u8 *D_00423118 __attribute__((section(".data")));
extern u8 *D_00421390 __attribute__((section(".data")));
extern u8 *D_003876A4 __attribute__((section(".data")));
extern u8 *D_00387F2C __attribute__((section(".data")));

#define G (D_00423118)
#define W(p, o) (*(s32 *)((p) + (o)))
#define N(p, o) (*(u8 **)((p) + (o)))
#define PTR(t, o) ((t) + (((u32)W((t), (o)) >> 2) << 2))
/* relocate the sub-block at table offset o of G->4 into sp0 (a pointer held on the stack) */
#define REL(o) do { u8 *t_ = N(G, 4); sp0 = PTR(t_, (o)); Res_RelocateOffsets(&sp0, sp0, sp0); } while (0)

s32 func_003CB420(s32 arg0) {
    u8 *sp0;
    s32 i;
    u8 *t, *b;

    sp0 = 0;
    G = (u8 *)func_0028BAA8(0x370);
    __builtin_memset(G, 0, 0x370);
    b = D_00421390;
    N(G, 0) = b + (((u32)W(b, arg0 * 4) >> 2) << 2);
    N(G, 4) = (u8 *)func_002B24C8(N(G, 0), 0, 0);

    REL(0x58);
    W(G, 0x108) = W(sp0, 0x10);
    REL(0x54);
    W(G, 0x104) = W(sp0, 0x10);
    W(G, 0x10C) = W(sp0, 0x10) + 0x40;
    REL(0x50);
    W(G, 0x100) = W(sp0, 0x10);
    REL(0x18);
    W(G, 0xF0) = W(sp0, 0x10);
    W(G, 0xF8) = W(sp0, 0x10) + 0x40;
    REL(0x14);
    W(G, 0xFC) = W(sp0, 0x10);
    W(G, 0xF4) = W(sp0, 0x10) + 0x40;
    REL(0x40);
    W(G, 0xE8) = W(sp0, 0x10);
    REL(0x3C);
    W(G, 0xEC) = W(sp0, 0x10);
    REL(0x24);
    W(G, 0xD8) = W(sp0, 0x10);
    REL(0x20);
    W(G, 0xE0) = W(sp0, 0x10);
    W(G, 0xDC) = W(sp0, 0x10) + 0x40;
    REL(0x10);
    W(G, 0xC0) = W(sp0, 0x10);
    REL(0x44);
    W(G, 0xBC) = W(sp0, 0x10);
    W(G, 0xB8) = W(sp0, 0x10) + 0x40;
    REL(0x48);
    t = N(G, 4);
    func_0024BED8(PTR(t, 0x98), W(sp0, 0x10));
    REL(0x30);
    W(G, 0xB0) = W(sp0, 0x10);
    REL(0x28);
    W(G, 0xB4) = W(sp0, 0x10);
    REL(0x2C);
    W(G, 0xC4) = W(sp0, 0x10);
    W(G, 0xC8) = W(sp0, 0x10) + 0x40;
    REL(0x1C);
    W(G, 0xCC) = W(sp0, 0x10);
    W(G, 0xD0) = W(sp0, 0x10);
    W(G, 0xD4) = W(sp0, 0x10);
    REL(0x9C);
    W(G, 0xE4) = W(sp0, 0x10);

    t = N(G, 4);
    func_0026E7F0(G + 0x88, PTR(t, 4), G + 0xB0);
    func_0026EAE0(G + 0x88, 0x3C);
    REL(8);
    W(G, 0x118) = W(sp0, 0x10);
    W(G, 0x11C) = W(sp0, 0x10) + 0x40;
    W(G, 0x114) = W(sp0, 0x10) + 0x80;
    t = N(G, 4);
    func_0026E7F0(G + 0x10, PTR(t, 0xC), G + 0x114);
    func_0026EAE0(G + 0x10, 0x3C);
    REL(0x34);
    W(G, 0x120) = W(sp0, 0x10);
    W(G, 0x124) = W(sp0, 0x10) + 0x40;
    t = N(G, 4);
    func_0026E7F0(G + 0x60, PTR(t, 0x38), G + 0x120);
    func_0026EAE0(G + 0x60, 0x3C);
    REL(0x7C);
    W(G, 0x128) = W(sp0, 0x10);
    W(G, 0x12C) = W(sp0, 0x10) + 0x80;
    W(G, 0x130) = W(sp0, 0x10) + 0x40;
    t = N(G, 4);
    func_0026E7F0(G + 0x38, PTR(t, 0x80), G + 0x128);
    func_0026EAE0(G + 0x38, 0x3C);

    t = N(G, 4);
    N(G, 8) = PTR(t, 0x4C);
    t = N(G, 4);
    N(G, 0xC) = PTR(t, 0x84);

    if (*(s16 *)(D_00387F2C + 0x424) < 4) {
        W(G, 0x144) = 0;
    } else {
        s32 tm = GetTimerSystemTime(D_00387F2C);
        func_00325370(tm);
        if ((rand() & 1) != 0) {
            W(G, 0x144) = 1;
        } else {
            W(G, 0x144) = 0;
        }
    }
    W(G, 0x140) = 1;
    W(G, 0x138) = W(D_003876A4, 0x8C);
    __builtin_memcpy(G + 0x170, D_00387F2C + 0x408, 0x200);

    W(G, 0x134) |= 0x10;
    for (i = 0; i < 2; i++) {
        if (*(s16 *)(D_00387F2C + 0x27EC + i * 4 + 2) != 0) {
            W(G, 0x134) |= 0x20 << i;
        }
    }
    for (i = 0; i < 3; i++) {
        if (W(G, 0x134) & (0x10 << i)) {
            W(G, 0x14C) = W(G, 0x14C) + 1;
        }
    }
    W(G, 0x134) |= 0xC00;
    for (i = 0; i < 2; i++) {
        if (*(s16 *)(D_00387F2C + 0x27F4 + i * 4 + 2) != 0) {
            W(G, 0x134) |= 0x1000 << i;
        }
    }
    for (i = 0; i < 4; i++) {
        if (W(G, 0x134) & (0x400 << i)) {
            W(G, 0x150) = W(G, 0x150) + 1;
        }
    }
    W(G, 0x168) = -0x32;
    W(G, 0x16C) = 0x14;
    return (s32)G;
}
