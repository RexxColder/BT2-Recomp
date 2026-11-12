#include "common.h"

extern u8 *D_00421394 __attribute__((section(".data")));
extern u8 *D_0042BB84 __attribute__((section(".data")));
extern u8 D_0042F4C8[] __attribute__((section(".data")));
extern u8 *D_003876A4;
extern s32 D_003B0D84 __attribute__((section(".data")));

s32 func_0028BAA8(s32 arg0);
u8 *func_002B24C8(u8 *a0, u8 *a1, s32 a2);
void Res_RelocateOffsets(u8 *a0, u8 *a1, u8 *a2);
void func_0024BED8(u8 *a0, s32 a1);
void func_0026E7F0(u8 *a0, u8 *a1, u8 *a2);
void func_0026EAE0(u8 *a0, s32 a1);
s32 rand(void);
s32 func_0028C4B8(s32 arg0);
void func_00101508(s32 a0);
s32 func_0041A928(void);
void func_001014E8(s32 a0);

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

/* 0x0041A988 (arg0 = index): allocates the 0x140-byte block at D_0042BB84, sets its pointers from
   the table at D_00421394 and from P = block->4; 15 slots at block+0x60 are relocated through the
   words of D_0042F4C8; then three rand() % 4 words at block+0x118.. and a few flag/init calls. */
void func_0041A988(s32 arg0) {
    u8 sp[0x40];
    u8 *G;
    u8 *P;
    u8 *X;
    s32 i;
    s32 idx;
    s32 s1;
    s32 n;

    D_0042BB84 = (u8 *)func_0028BAA8(0x140);
    G = D_0042BB84;
    blob_clear(G, 0x140);

    *(u8 **)(G + 0x0) = D_00421394 + (*(s32 *)(D_00421394 + (arg0 << 2)) & ~3);
    *(u8 **)(G + 0x4) = func_002B24C8(*(u8 **)(G + 0x0), 0, 0);

    blob_copy(sp, D_0042F4C8, 0x3C);
    i = 0;
    do {
        G = D_0042BB84;
        P = *(u8 **)(G + 0x4);
        idx = *(s32 *)(sp + 4 * i);
        X = P + (*(s32 *)(P + 4 * idx) & ~3);
        Res_RelocateOffsets(G + 0x60 + 4 * i, X, X);
        i++;
    } while (i < 15);

    G = D_0042BB84;
    *(s32 *)(G + 0xA0) = *(s32 *)(*(u8 **)(G + 0x94) + 0x10);
    *(s32 *)(G + 0x9C) = *(s32 *)(*(u8 **)(G + 0x94) + 0x10) + 0x40;
    *(s32 *)(G + 0xAC) = *(s32 *)(*(u8 **)(G + 0x6C) + 0x10);
    *(s32 *)(G + 0xB0) = *(s32 *)(*(u8 **)(G + 0x6C) + 0x10) + 0x40;
    *(s32 *)(G + 0xA4) = *(s32 *)(*(u8 **)(G + 0x74) + 0x10);
    *(s32 *)(G + 0xB4) = *(s32 *)(*(u8 **)(G + 0x78) + 0x10);
    *(s32 *)(G + 0xA8) = *(s32 *)(*(u8 **)(G + 0x7C) + 0x10) + 0x40;
    *(s32 *)(G + 0xC8) = *(s32 *)(*(u8 **)(G + 0x80) + 0x10);
    *(s32 *)(G + 0xCC) = *(s32 *)(*(u8 **)(G + 0x80) + 0x10);
    *(s32 *)(G + 0xD0) = *(s32 *)(*(u8 **)(G + 0x80) + 0x10);
    *(s32 *)(G + 0xD8) = *(s32 *)(*(u8 **)(G + 0x80) + 0x10) + 0x140;
    *(s32 *)(G + 0xC4) = *(s32 *)(*(u8 **)(G + 0x7C) + 0x10);
    *(s32 *)(G + 0xD4) = *(s32 *)(*(u8 **)(G + 0x84) + 0x10);
    *(s32 *)(G + 0xB8) = *(s32 *)(*(u8 **)(G + 0x74) + 0x10) + 0x40;
    *(s32 *)(G + 0xBC) = *(s32 *)(*(u8 **)(G + 0x78) + 0x10) + 0x40;
    *(s32 *)(G + 0xC0) = *(s32 *)(*(u8 **)(G + 0x88) + 0x10);
    *(s32 *)(G + 0xDC) = *(s32 *)(*(u8 **)(G + 0x8C) + 0x10);
    *(s32 *)(G + 0xE0) = *(s32 *)(*(u8 **)(G + 0x90) + 0x10);
    *(s32 *)(G + 0xE4) = *(s32 *)(*(u8 **)(G + 0x98) + 0x10);
    *(s32 *)(G + 0xE8) = *(s32 *)(*(u8 **)(G + 0x64) + 0x10);
    *(s32 *)(G + 0xEC) = *(s32 *)(*(u8 **)(G + 0x68) + 0x10);

    P = *(u8 **)(G + 0x4);
    func_0024BED8(P + (*(s32 *)(P + 0x7C) & ~3), *(s32 *)(*(u8 **)(G + 0x70) + 0x10));

    G = D_0042BB84;
    P = *(u8 **)(G + 0x4);
    func_0026E7F0(G + 0x10, P + (*(s32 *)(P + 0x8) & ~3), G + 0xE8);
    func_0026EAE0(G + 0x10, 0x3C);

    G = D_0042BB84;
    P = *(u8 **)(G + 0x4);
    func_0026E7F0(G + 0x38, P + (*(s32 *)(P + 0x4) & ~3), G + 0x9C);
    func_0026EAE0(G + 0x38, 0x3C);

    G = D_0042BB84;
    P = *(u8 **)(G + 0x4);
    *(u8 **)(G + 0x8) = P + (*(s32 *)(P + 0x44) & ~3);
    *(u8 **)(G + 0xC) = P + (*(s32 *)(P + 0x78) & ~3);

    *(s32 *)(G + 0xF4) = *(s32 *)(D_003876A4 + 0x458);
    *(s32 *)(G + 0xFC) = *(s32 *)(D_003876A4 + 0x464);

    s1 = 0x118;
    n = 2;
    do {
        n--;
        *(s32 *)(G + s1 + 8) = rand() % 4;
        s1 += 4;
    } while (n >= 0);

    if (D_003B0D84 != 1 || func_0028C4B8(1) != 0) {
        G = D_0042BB84;
        *(s32 *)(G + 0xF0) |= 8;
    }

    func_00101508(0x3E0C);
    func_001014E8(func_0041A928());
}
