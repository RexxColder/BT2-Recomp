#include "common.h"

extern u8 *D_00421398 __attribute__((section(".data")));
extern u8 *D_004279D4 __attribute__((section(".data")));
extern u8 D_00428C68[] __attribute__((section(".data")));
extern u8 *D_00387F2C;

s32 func_0028BAA8(s32 arg0);
u8 *func_002B24C8(u8 *a0, u8 *a1, s32 a2);
void Res_RelocateOffsets(u8 *a0, u8 *a1, u8 *a2);
void func_0026E7F0(u8 *a0, u8 *a1, u8 *a2);
void func_0026EAE0(u8 *a0, s32 a1);
void func_0029BB88(u8 *a0, u8 *a1);

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

/* 0x003E84B0 (arg0 = index): allocates the 0x2F8-byte block at D_004279D4, sets its pointers from
   the table at D_00421398 and from P = block->4; 13 slots at block+0x38 are relocated through the
   words of D_00428C68. Finally copies 0xA0 + 12 bytes out of D_00387F2C and sets block+0xC4 = -1. */
void func_003E84B0(s32 arg0) {
    u8 sp[0x40];
    u8 *G;
    u8 *P;
    u8 *X;
    s32 i;
    s32 idx;

    D_004279D4 = (u8 *)func_0028BAA8(0x2F8);
    G = D_004279D4;
    blob_clear(G, 0x2F8);

    *(u8 **)(G + 0x0) = D_00421398 + (*(s32 *)(D_00421398 + (arg0 << 2)) & ~3);
    *(u8 **)(G + 0x4) = func_002B24C8(*(u8 **)(G + 0x0), 0, 0);

    blob_copy(sp, D_00428C68, 0x34);
    i = 0;
    do {
        G = D_004279D4;
        P = *(u8 **)(G + 0x4);
        idx = *(s32 *)(sp + 4 * i);
        X = P + (*(s32 *)(P + 4 * idx) & ~3);
        Res_RelocateOffsets(G + 0x38 + 4 * i, X, X);
        i++;
    } while (i < 13);

    G = D_004279D4;
    *(s32 *)(G + 0x6C) = *(s32 *)(*(u8 **)(G + 0x54) + 0x10);
    *(s32 *)(G + 0x70) = *(s32 *)(*(u8 **)(G + 0x54) + 0x10);
    *(s32 *)(G + 0x74) = *(s32 *)(*(u8 **)(G + 0x54) + 0x10);
    *(s32 *)(G + 0x78) = *(s32 *)(*(u8 **)(G + 0x58) + 0x10);
    *(s32 *)(G + 0x7C) = *(s32 *)(*(u8 **)(G + 0x58) + 0x10) + 0x40;
    *(s32 *)(G + 0x80) = *(s32 *)(*(u8 **)(G + 0x5C) + 0x10);
    *(s32 *)(G + 0x84) = *(s32 *)(*(u8 **)(G + 0x4C) + 0x10);
    *(s32 *)(G + 0x88) = *(s32 *)(*(u8 **)(G + 0x60) + 0x10);
    *(s32 *)(G + 0x8C) = *(s32 *)(*(u8 **)(G + 0x3C) + 0x10);
    *(s32 *)(G + 0x90) = *(s32 *)(*(u8 **)(G + 0x40) + 0x10);
    *(s32 *)(G + 0x94) = *(s32 *)(*(u8 **)(G + 0x60) + 0x10) + 0x40;
    *(s32 *)(G + 0x98) = *(s32 *)(*(u8 **)(G + 0x40) + 0x10) + 0x40;
    *(s32 *)(G + 0x9C) = *(s32 *)(*(u8 **)(G + 0x44) + 0x10) + 0x40;
    *(s32 *)(G + 0xA0) = *(s32 *)(*(u8 **)(G + 0x44) + 0x10);
    *(s32 *)(G + 0xA4) = *(s32 *)(*(u8 **)(G + 0x64) + 0x10);
    *(s32 *)(G + 0xA8) = *(s32 *)(*(u8 **)(G + 0x68) + 0x10);
    *(s32 *)(G + 0xAC) = *(s32 *)(*(u8 **)(G + 0x48) + 0x10);
    *(s32 *)(G + 0xB0) = *(s32 *)(*(u8 **)(G + 0x64) + 0x10) + 0x40;
    *(s32 *)(G + 0xB4) = *(s32 *)(*(u8 **)(G + 0x48) + 0x10) + 0x40;
    *(s32 *)(G + 0xB8) = *(s32 *)(*(u8 **)(G + 0x50) + 0x10) + 0x80;
    *(s32 *)(G + 0xBC) = *(s32 *)(*(u8 **)(G + 0x50) + 0x10);
    *(s32 *)(G + 0xC0) = *(s32 *)(*(u8 **)(G + 0x50) + 0x10) + 0x40;

    P = *(u8 **)(G + 0x4);
    func_0026E7F0(G + 0x10, P + (*(s32 *)(P + 0x1C) & ~3), G + 0x6C);
    func_0026EAE0(G + 0x10, 0x3C);

    P = *(u8 **)(G + 0x4);
    *(u8 **)(G + 0x8) = P + (*(s32 *)(P + 0x38) & ~3);
    *(u8 **)(G + 0xC) = P + (*(s32 *)(P + 0x3C) & ~3);
    func_0029BB88(P + (*(s32 *)(P + 0x44) & ~3), *(u8 **)(G + 0x8));

    blob_copy(G + 0xE8, D_00387F2C + 0x1008, 0xA0);
    blob_copy(G + 0x188, D_00387F2C + 0x10A8, 12);

    G = D_004279D4;
    *(s32 *)(G + 0xC4) = -1;
}
