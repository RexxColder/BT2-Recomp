#include "common.h"

extern u8 *D_00421398 __attribute__((section(".data")));
extern u8 *D_004279CC __attribute__((section(".data")));
extern u8 D_00427C90[] __attribute__((section(".data")));
extern u8 D_00427CC0[] __attribute__((section(".data")));
extern u8 D_00427CF0[] __attribute__((section(".data")));
extern u8 *D_00387F2C;
extern u8 *D_003876A4;

s32 func_0028BAA8(s32 arg0);
u8 *func_002B24C8(u8 *a0, u8 *a1, s32 a2);
void Res_RelocateOffsets(u8 *a0, u8 *a1, u8 *a2);
void func_0024BED8(u8 *a0, s32 a1);
void func_0026E7F0(u8 *a0, u8 *a1, u8 *a2);
void func_0026EAE0(u8 *a0, s32 a1);
void func_0029BB88(u8 *a0, u8 *a1);
s32 func_0028A0B8(u8 *a0, u8 *a1, s32 a2, s32 a3, s32 t0);
s32 McCard_Checksum(u8 *a0, s32 a1, s32 a2);
void func_0029C820(s32 a0);

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

/* 0x003E3D38 (arg0 = index): allocates the 0x4544-byte block at D_004279CC, sets its pointers from
   the table at D_00421398 and from P = block->4; 11 slots at block+0x64 are relocated through the
   words of D_00427C90; then copies 0x2D bytes of D_00427CC0 to block+0x4438. */
void func_003E3D38(s32 arg0) {
    u8 sp[0x40];
    u8 *G;
    u8 *P;
    u8 *X;
    s32 i;
    s32 idx;

    D_004279CC = (u8 *)func_0028BAA8(0x4544);
    G = D_004279CC;
    blob_clear(G, 0x4544);

    *(u8 **)(G + 0x0) = D_00421398 + (*(s32 *)(D_00421398 + (arg0 << 2)) & ~3);
    *(u8 **)(G + 0x4) = func_002B24C8(*(u8 **)(G + 0x0), 0, 0);

    blob_copy(sp, D_00427C90, 0x2C);
    i = 0;
    do {
        G = D_004279CC;
        P = *(u8 **)(G + 0x4);
        idx = *(s32 *)(sp + 4 * i);
        X = P + (*(s32 *)(P + 4 * idx) & ~3);
        Res_RelocateOffsets(G + 0x64 + 4 * i, X, X);
        i++;
    } while (i < 11);

    G = D_004279CC;
    *(s32 *)(G + 0x90) = *(s32 *)(*(u8 **)(G + 0x80) + 0x10) + 0x40;
    *(s32 *)(G + 0x94) = *(s32 *)(*(u8 **)(G + 0x68) + 0x10);
    *(s32 *)(G + 0x98) = *(s32 *)(*(u8 **)(G + 0x74) + 0x10);
    *(s32 *)(G + 0x9C) = *(s32 *)(*(u8 **)(G + 0x6C) + 0x10);
    *(s32 *)(G + 0xA0) = *(s32 *)(*(u8 **)(G + 0x6C) + 0x10);
    *(s32 *)(G + 0xA4) = *(s32 *)(*(u8 **)(G + 0x6C) + 0x10);
    *(s32 *)(G + 0xA8) = *(s32 *)(*(u8 **)(G + 0x70) + 0x10);
    *(s32 *)(G + 0xAC) = *(s32 *)(*(u8 **)(G + 0x80) + 0x10);
    *(s32 *)(G + 0xB0) = *(s32 *)(*(u8 **)(G + 0x78) + 0x10);
    *(s32 *)(G + 0xB4) = *(s32 *)(*(u8 **)(G + 0x74) + 0x10) + 0x40;
    *(s32 *)(G + 0xB8) = *(s32 *)(*(u8 **)(G + 0x78) + 0x10) + 0x40;
    *(s32 *)(G + 0xBC) = *(s32 *)(*(u8 **)(G + 0x8C) + 0x10);
    *(s32 *)(G + 0xC0) = *(s32 *)(*(u8 **)(G + 0x88) + 0x10);
    *(s32 *)(G + 0xC4) = *(s32 *)(*(u8 **)(G + 0x8C) + 0x10) + 0x40;
    *(s32 *)(G + 0xC8) = *(s32 *)(*(u8 **)(G + 0x88) + 0x10) + 0x40;

    P = *(u8 **)(G + 0x4);
    func_0024BED8(P + (*(s32 *)(P + 0x4C) & ~3), *(s32 *)(*(u8 **)(G + 0x7C) + 0x10));

    G = D_004279CC;
    P = *(u8 **)(G + 0x4);
    func_0026E7F0(G + 0x3C, P + (*(s32 *)(P + 0x4) & ~3), G + 0x90);
    func_0026EAE0(G + 0x3C, 0x3C);

    G = D_004279CC;
    P = *(u8 **)(G + 0x4);
    func_0026E7F0(G + 0x14, P + (*(s32 *)(P + 0x14) & ~3), G + 0xCC);
    func_0026EAE0(G + 0x14, 0x3C);

    G = D_004279CC;
    P = *(u8 **)(G + 0x4);
    *(u8 **)(G + 0xC) = P + (*(s32 *)(P + 0x34) & ~3);
    *(u8 **)(G + 0x8) = P + (*(s32 *)(P + 0x38) & ~3);
    *(u8 **)(G + 0x10) = P + (*(s32 *)(P + 0x40) & ~3);
    func_0029BB88(P + (*(s32 *)(P + 0x3C) & ~3), *(u8 **)(G + 0x10));

    G = D_004279CC;
    *(s32 *)(G + 0x10C) = -1;
    P = *(u8 **)(G + 0x4);
    *(u8 **)(G + 0x4120) = P + (*(s32 *)(P + 0x50) & ~3);
    *(s32 *)(G + 0x412C) = 0xD74E;
    blob_copy(G + 0x4438, D_00427CC0, 0x2D);
    *(s32 *)(G + 0x453C) = 0x18;
    func_0028A0B8(G + 0x4120, D_00427CF0, -1, -1, 1);

    McCard_Checksum(D_00387F2C, 0x4000, 1);

    G = D_004279CC;
    *(s32 *)(G + 0xD4) = *(s32 *)(D_003876A4 + 0x4C0);
    func_0029C820(1);
}
