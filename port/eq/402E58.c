#include "common.h"

extern u8 *D_0042BB70;
extern u8 D_0042BB90[];
extern u8 *D_00421394;
extern u8 *D_00387F2C;
extern s32 func_0028BAA8();
extern s32 func_002B24C8();
extern s32 Res_RelocateOffsets();
extern s32 func_0026E7F0();
extern s32 func_0026EAE0();
extern s32 func_0029BB88();
extern s32 rand();

#define T(d, s, a) *(s32 *)(g + (d)) = *(s32 *)(*(u8 **)(g + (s)) + 0x10) + (a)
#define RB(o) (b + (*(u32 *)(b + (o)) & ~3u))

s32 func_00402E58(s32 arg0) {
    u32 tbl[17];
    u8 *g;
    u8 *t;
    u8 *b;
    u8 *r;
    s32 i;
    s32 s0;
    s32 s2;

    g = (u8 *)func_0028BAA8(0x370);
    D_0042BB70 = g;
    __builtin_memset(g, 0, 0x370);
    t = D_00421394;
    g = D_0042BB70;
    *(u8 **)g = t + (*(u32 *)(t + arg0 * 4) & ~3u);
    g = D_0042BB70;
    *(s32 *)(g + 4) = func_002B24C8(*(s32 *)g, 0, 0); /* asm: lw a0, 0(g): the entry's address, not its first word */
    i = 0;
    do {
        __builtin_memcpy(tbl, D_0042BB90, 0x44);
        g = D_0042BB70;
        b = *(u8 **)(g + 4);
        r = b + (*(u32 *)(b + tbl[i] * 4) & ~3u);
        i++;
        Res_RelocateOffsets(g + 0x60 + (i - 1) * 4, r, r);
    } while (i < 17);
    g = D_0042BB70;
    T(0xC0, 0x70, 0x40);
    T(0xA4, 0x74, 0);
    T(0xA8, 0x78, 0x140);
    T(0xAC, 0x78, 0);
    T(0xB0, 0x78, 0);
    T(0xB4, 0x7C, 0);
    T(0xB8, 0x7C, 0x40);
    T(0xBC, 0x80, 0);
    T(0xC4, 0x84, 0);
    T(0xC8, 0x88, 0);
    T(0xCC, 0x84, 0x40);
    T(0xD0, 0x88, 0x40);
    T(0xD4, 0x8C, 0);
    T(0xD8, 0x90, 0);
    T(0xDC, 0x90, 0x40);
    T(0xE0, 0x8C, 0x40);
    T(0xEC, 0x8C, 0x80);
    T(0xF0, 0x98, 0x80);
    T(0xF4, 0x98, 0);
    T(0xF8, 0x98, 0x40);
    T(0xFC, 0x9C, 0);
    T(0x100, 0x9C, 0x40);
    T(0x104, 0x64, 0);
    T(0x108, 0x68, 0);
    b = *(u8 **)(g + 4);
    func_0026E7F0(g + 0x38, RB(0x48), g + 0xA4);
    g = D_0042BB70;
    func_0026EAE0(g + 0x38, 0x3C);
    g = D_0042BB70;
    b = *(u8 **)(g + 4);
    func_0026E7F0(g + 0x10, RB(8), g + 0x104);
    g = D_0042BB70;
    func_0026EAE0(g + 0x10, 0x3C);
    g = D_0042BB70;
    b = *(u8 **)(g + 4);
    *(u8 **)(g + 8) = RB(0x44);
    g = D_0042BB70;
    b = *(u8 **)(g + 4);
    *(u8 **)(g + 0xC) = RB(0x78);
    g = D_0042BB70;
    b = *(u8 **)(g + 4);
    func_0029BB88(RB(0x84), *(s32 *)(g + 0xC));
    g = D_0042BB70;
    __builtin_memcpy(g + 0x164, D_00387F2C + 0x808, 0x200);
    g = D_0042BB70;
    *(s32 *)(g + 0x120) = 5;
    g = D_0042BB70;
    *(s32 *)(g + 0x118) = 0;
    g = D_0042BB70;
    *(s32 *)(g + 0x11C) = *(s32 *)(g + *(s32 *)(g + 0x118) * 4 + 0x168);
    s0 = 0x13C;
    s2 = 2;
    do {
        s32 v = rand();
        s2--;
        g = D_0042BB70;
        *(s32 *)(g + s0 + 4) = v % 4;
        s0 += 4;
    } while (s2 >= 0);
    g = D_0042BB70;
    *(s32 *)(g + 0x114) = 8;
    return 8;
}
