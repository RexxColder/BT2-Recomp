#include "common.h"

extern u8 *D_0042A584 __attribute__((section(".data")));
extern u8 *D_0042139C __attribute__((section(".data")));
extern u8 D_0042B580[] __attribute__((section(".data")));

u8 *func_28BAA8(s32);
u8 *func_2B24C8(u8 *, s32, s32);
void Res_RelocateOffsets(void *, void *, void *);
void func_26E7F0(void *, void *, void *);
void func_26EAE0(void *, s32);
void *memset(void *arg0, s32 arg1, s32 arg2);

u8 *func_003FA8F0(s32 arg0) {
    u8 *o;
    u8 *g4;
    u8 *tmp;
    u8 *base;
    s32 s2;
    s32 k;
    s32 a3;
    s32 t1;
    s32 t2;
    u32 w;

    o = func_28BAA8(0x134);
    D_0042A584 = o;
    memset(o, 0, 0x134);
    *(u8 **)o = D_0042139C + (*(u32 *)(D_0042139C + 4 * arg0) & ~3u);
    *(u8 **)(o + 4) = func_2B24C8(*(u8 **)o, 0, 0);

    for (s2 = 0; s2 < 11; s2++) {
        o = D_0042A584;
        g4 = *(u8 **)(o + 4);
        Res_RelocateOffsets(o + 4 * s2 + 0x64,
                            g4 + (*(u32 *)(g4 + 4 * *(u32 *)(D_0042B580 + 4 * s2)) & ~3u),
                            g4 + (*(u32 *)(g4 + 4 * *(u32 *)(D_0042B580 + 4 * s2)) & ~3u));
    }

    o = D_0042A584;
    *(u32 *)(o + 0x90) = *(u32 *)(*(u8 **)(o + 0x84) + 0x10);
    *(u32 *)(o + 0x94) = *(u32 *)(*(u8 **)(o + 0x88) + 0x10) + 0x40;
    *(u32 *)(o + 0x98) = *(u32 *)(*(u8 **)(o + 0x88) + 0x10);
    *(u32 *)(o + 0x9C) = *(u32 *)(*(u8 **)(o + 0x80) + 0x10);
    *(u32 *)(o + 0xA0) = *(u32 *)(*(u8 **)(o + 0x7C) + 0x10);
    *(u32 *)(o + 0xE0) = *(u32 *)(*(u8 **)(o + 0x78) + 0x10);
    *(u32 *)(o + 0xE4) = *(u32 *)(*(u8 **)(o + 0x8C) + 0x10);
    *(u32 *)(o + 0xE8) = *(u32 *)(*(u8 **)(o + 0x8C) + 0x10);
    *(u32 *)(o + 0xFC) = *(u32 *)(*(u8 **)(o + 0x74) + 0x10);

    a3 = 0xC4;
    t1 = 0xC8;
    t2 = 0xDC;
    for (k = 0; k < 5; k++) { /* asm 0x3FAA40: li s2,4 + bgez -> 5 passes (class 9) */
        *(u32 *)(o + a3) = 0;
        a3 -= 4;
        *(u32 *)(o + t1) = 0;
        t1 -= 4;
        *(u32 *)(o + t2) = 0;
        t2 -= 4;
    }

    *(u32 *)(o + 0x100) = *(u32 *)(*(u8 **)(o + 0x6C) + 0x10) + 0x40;
    *(u32 *)(o + 0x104) = *(u32 *)(*(u8 **)(o + 0x6C) + 0x10);
    *(u32 *)(o + 0x108) = *(u32 *)(*(u8 **)(o + 0x70) + 0x10);
    *(u32 *)(o + 0x10C) = *(u32 *)(*(u8 **)(o + 0x68) + 0x10);

    g4 = *(u8 **)(o + 4);
    func_26E7F0(o + 0x14, g4 + (*(u32 *)(g4 + 0x28) & ~3u), o + 0x100);
    func_26EAE0(o + 0x14, 0x3C);

    g4 = *(u8 **)(o + 4);
    func_26E7F0(o + 0x3C, g4 + (*(u32 *)(g4 + 0x18) & ~3u), o + 0x90);
    func_26EAE0(o + 0x3C, 0x3C);

    g4 = *(u8 **)(o + 4);
    *(u8 **)(o + 0x8) = g4 + (*(u32 *)(g4 + 0x38) & ~3u);
    *(u8 **)(o + 0xC) = g4 + (*(u32 *)(g4 + 0x3C) & ~3u);
    *(u8 **)(o + 0x130) = g4 + (*(u32 *)(g4 + 0x48) & ~3u) + 4;
    *(u8 **)(o + 0x10) = func_2B24C8(g4 + (*(u32 *)(g4 + 0x44) & ~3u), 0, 0);

    for (s2 = 0; s2 < 0x86; s2++) {
        base = *(u8 **)(D_0042A584 + 0x10);
        w = *(u32 *)(base + 4 * s2 + 4);
        tmp = base + (w & ~3u);
        Res_RelocateOffsets(&tmp, tmp, tmp);
    }

    return D_0042A584;
}
