#include "common.h"

extern u8 *D_004213A4 __attribute__((section(".data")));
extern u8 *D_0042732C __attribute__((section(".data")));
extern u8 D_00427348[] __attribute__((section(".data")));

s32 func_0028BAA8(s32 arg0);
u8 *func_002B24C8(u8 *a0, u8 *a1, s32 a2);
void Res_RelocateOffsets(u8 *a0, u8 *a1, u8 *a2);
void func_0026E7F0(u8 *a0, u8 *a1, u8 *a2);
void func_0026EAE0(u8 *a0, s32 a1);
s32 Font_GetGlyphHeight();
void func_003DC998(void);
void func_001050A8(void);

/* byte copy (no libc); optnone so clang does not turn the loops into memcpy/memset on 4-byte game pointers,
 * which the PC build cannot lower */
__attribute__((noinline, optnone)) static void blob_copy(u8 *d, u8 *s, u32 n) {
    u32 i;
    for (i = 0; i < n; i++) {
        d[i] = s[i];
    }
}

__attribute__((noinline, optnone)) static void blob_clear(u8 *d, u32 n) {
    u32 i;
    for (i = 0; i < n; i++) {
        d[i] = 0;
    }
}

/* 0x003DCAE0 (arg0 = index): allocates the 0x774-byte block at D_0042732C, sets its pointers
   from the table at D_004213A4 and from P = block->4; 16 slots at block+0x54 are relocated
   through the 16 words of D_00427348. */
void func_003DCAE0(s32 arg0) {
    u8 sp[0x40];
    u8 *G;
    u8 *P;
    u8 *X;
    u8 *t;
    s32 i;
    s32 idx;

    D_0042732C = (u8 *)func_0028BAA8(0x774);
    G = D_0042732C;
    blob_clear(G, 0x774);

    *(u8 **)(G + 0x0) = D_004213A4 + (*(s32 *)(D_004213A4 + (arg0 << 2)) & ~3);
    *(u8 **)(G + 0x4) = func_002B24C8(*(u8 **)(G + 0x0), 0, 0);

    blob_copy(sp, D_00427348, 0x40);
    i = 0;
    do {
        G = D_0042732C;
        P = *(u8 **)(G + 0x4);
        idx = *(s32 *)(sp + 4 * i);
        X = P + (*(s32 *)(P + 4 * idx) & ~3);
        Res_RelocateOffsets(G + 0x54 + 4 * i, X, X);
        i++;
    } while (i < 16);

    G = D_0042732C;
    *(s32 *)(G + 0x94) = *(s32 *)(*(u8 **)(G + 0x7C) + 0x10);
    *(s32 *)(G + 0x98) = *(s32 *)(*(u8 **)(G + 0x88) + 0x10);
    *(s32 *)(G + 0x9C) = *(s32 *)(*(u8 **)(G + 0x88) + 0x10);
    *(s32 *)(G + 0xA0) = *(s32 *)(*(u8 **)(G + 0x88) + 0x10);
    *(s32 *)(G + 0xA4) = *(s32 *)(*(u8 **)(G + 0x8C) + 0x10);
    *(s32 *)(G + 0xA8) = *(s32 *)(*(u8 **)(G + 0x8C) + 0x10) + 0x40;
    *(s32 *)(G + 0xAC) = *(s32 *)(*(u8 **)(G + 0x68) + 0x10);
    *(s32 *)(G + 0xB0) = *(s32 *)(*(u8 **)(G + 0x84) + 0x10);
    *(s32 *)(G + 0xB4) = *(s32 *)(*(u8 **)(G + 0x90) + 0x10);
    *(s32 *)(G + 0xB8) = *(s32 *)(*(u8 **)(G + 0x64) + 0x10);
    *(s32 *)(G + 0xBC) = *(s32 *)(*(u8 **)(G + 0x64) + 0x10) + 0x40;
    *(s32 *)(G + 0xC8) = *(s32 *)(*(u8 **)(G + 0x54) + 0x10);
    *(s32 *)(G + 0xCC) = *(s32 *)(*(u8 **)(G + 0x60) + 0x10);
    *(s32 *)(G + 0xD0) = *(s32 *)(*(u8 **)(G + 0x74) + 0x10) + 0x40;
    *(s32 *)(G + 0xD4) = *(s32 *)(*(u8 **)(G + 0x74) + 0x10);
    *(s32 *)(G + 0xD8) = *(s32 *)(*(u8 **)(G + 0x6C) + 0x10);
    *(s32 *)(G + 0xDC) = *(s32 *)(*(u8 **)(G + 0x5C) + 0x10);
    *(s32 *)(G + 0xE0) = *(s32 *)(*(u8 **)(G + 0x58) + 0x10);
    *(s32 *)(G + 0xF8) = *(s32 *)(*(u8 **)(G + 0x78) + 0x10);
    *(s32 *)(G + 0xFC) = *(s32 *)(*(u8 **)(G + 0x70) + 0x10) + 0x40;
    *(s32 *)(G + 0x100) = *(s32 *)(*(u8 **)(G + 0x70) + 0x10);

    P = *(u8 **)(G + 0x4);
    X = P + (*(s32 *)(P + 0x64) & ~3);
    Res_RelocateOffsets(G + 0x104, X, X);

    P = *(u8 **)(G + 0x4);
    func_0026E7F0(G + 0x2C, P + (*(s32 *)(P + 0x4) & ~3), G + 0x94);
    func_0026EAE0(G + 0x2C, 0x3C);

    P = *(u8 **)(G + 0x4);
    *(u8 **)(G + 0x14) = P + (*(s32 *)(P + 0x5C) & ~3);
    *(u8 **)(G + 0x10) = P + (*(s32 *)(P + 0x58) & ~3);
    *(u8 **)(G + 0x20) = P + (*(s32 *)(P + 0x3C) & ~3);
    *(u8 **)(G + 0x24) = P + (*(s32 *)(P + 0x40) & ~3);
    *(u8 **)(G + 0x28) = P + (*(s32 *)(P + 0x44) & ~3);
    t = P + (*(s32 *)(P + 0x38) & ~3);
    *(u8 **)(G + 0x18) = *(u8 **)t;
    *(u8 **)(G + 0x1C) = t + 4;

    *(u8 **)(G + 0x8) = (u8 *)func_0028BAA8(0xB000);
    *(u8 **)(G + 0xC) = (u8 *)func_0028BAA8(0x10560);

    *(s32 *)(G + 0x10C) = 4;
    *(s32 *)(G + 0x75C) = Font_GetGlyphHeight() + 2;
    func_003DC998();
    func_001050A8();
    G = D_0042732C;
    *(s32 *)(G + 0x74C) = 4;
}
