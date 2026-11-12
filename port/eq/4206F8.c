#include "common.h"

extern u8 *D_0042FD78 __attribute__((section(".data")));
extern u8 *D_004213AC __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));
extern s32 D_00430528[] __attribute__((section(".data")));

u8 *func_28BAA8(s32 a0);
u8 *func_2B24C8(u8 *a0, u8 *a1, s32 a2);
void Res_RelocateOffsets(u8 *a0, u8 *a1, u8 *a2);
void func_26E7F0(u8 *a0, u8 *a1, u8 *a2);
void func_26EAE0(u8 *a0, s32 a1);
void func_0041FAD8(s32 a0, u8 *a1);

/* 0x004206F8: builds the 0xF0-byte object at D_0042FD78 for table index idx: P->0 and P->4 from the D_004213AC
 * table, five relocations of P + 0x68 + 4 * i (i = 0..4, word order from D_00430528), then the P->0x7C..0xB0 slots,
 * two func_26E7F0 calls, func_26EAE0(P + 0x18, 0x3C) and func_0041FAD8(G->0x30, P). */
void func_004206F8(s32 idx) {
    s32 ord[5];
    u8 *P;
    u8 *Q;
    u8 *v;
    u32 w;
    s32 i;

    memcpy(ord, D_00430528, 0x14);
    P = func_28BAA8(0xF0);
    D_0042FD78 = P;
    memset(P, 0, 0xF0);

    Q = D_004213AC;
    w = *(u32 *)(Q + idx * 4);
    *(u8 **)(P + 0x0) = Q + (w & ~3u);
    *(u8 **)(P + 0x4) = func_2B24C8(*(u8 **)(P + 0x0), 0, 0);

    for (i = 0; i < 5; i++) {
        v = *(u8 **)(P + 0x4);
        w = *(u32 *)(v + ord[i] * 4);
        Res_RelocateOffsets(P + 0x68 + i * 4, v + (w & ~3u), v + (w & ~3u));
    }

    *(u8 **)(P + 0x7C) = *(u8 **)(*(u8 **)(P + 0x6C) + 0x10) + 0x40;
    *(u8 **)(P + 0x80) = *(u8 **)(*(u8 **)(P + 0x70) + 0x10);
    *(u8 **)(P + 0x8C) = *(u8 **)(*(u8 **)(P + 0x6C) + 0x10);
    *(u8 **)(P + 0x90) = *(u8 **)(*(u8 **)(P + 0x78) + 0x10) + 0x40;
    *(u8 **)(P + 0x94) = *(u8 **)(*(u8 **)(P + 0x78) + 0x10);
    *(u8 **)(P + 0xA4) = *(u8 **)(*(u8 **)(P + 0x68) + 0x10);
    *(u8 **)(P + 0xA8) = *(u8 **)(*(u8 **)(P + 0x68) + 0x10) + 0x40;
    *(u8 **)(P + 0xAC) = *(u8 **)(*(u8 **)(P + 0x68) + 0x10) + 0x80;
    *(u8 **)(P + 0xB0) = *(u8 **)(*(u8 **)(P + 0x68) + 0x10) + 0xC0;

    v = *(u8 **)(P + 0x4);
    func_26E7F0(P + 0x40, v + (*(u32 *)(v + 0x4) & ~3u), P + 0x7C);
    v = *(u8 **)(P + 0x4);
    func_26E7F0(P + 0x18, v + (*(u32 *)(v + 0x8) & ~3u), P + 0xA4);
    func_26EAE0(P + 0x18, 0x3C);

    v = *(u8 **)(P + 0x4);
    *(u8 **)(P + 0x8) = v + (*(u32 *)(v + 0x20) & ~3u);
    v = *(u8 **)(P + 0x4);
    *(u8 **)(P + 0x14) = v + (*(u32 *)(v + 0x24) & ~3u) + 4;

    func_0041FAD8(*(s32 *)(D_3876A4 + 0x30), P);
}
