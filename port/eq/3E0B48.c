#include "common.h"

extern u8 *D_00427338 __attribute__((section(".data")));
extern u8 *D_004213A4 __attribute__((section(".data")));
extern u8 D_004278F0[] __attribute__((section(".data")));

u8 *func_28BAA8(s32 arg0);
u8 *func_2B24C8(u8 *arg0, u8 *arg1, s32 arg2);
void Res_RelocateOffsets(void *arg0, void *arg1, void *arg2);
void func_26E7F0(u8 *a0, u8 *a1, u8 *a2);
void func_26EAE0(u8 *a0, s32 a1);
void *memset(void *dst, s32 c, u32 n);
void *memcpy(void *dst, const void *src, u32 n);

/* srl then sll by 2 (logical), as in the asm: clears the low two bits and the top two bits. */
#define ALIGN4X(v) ((s32)(((u32)(v) >> 2) << 2))

/* 0x003E0B48: allocates the 0xEC-byte object G = D_00427338 and fills it. G[0] = T + align(T[arg0]) where T = D_004213A4,
 * G[4] = func_2B24C8(G[0], 0, 0). Then for k = 0..12 (table tbl = copy of D_004278F0, 0x34 bytes), call
 * Res_RelocateOffsets(G + 0x58 + 4k, Q + align(Q[tbl[k]]), same) with Q = G[4]. Then G[0x8C..0xC8] take
 * values from the sub-blocks G[0x58..0x88] (each +0x40 or +0x80 where noted), func_26E7F0 and func_26EAE0 on G + 8 and
 * G + 0x30 with the Q + align(Q[4]) and Q + align(Q[0x14]) offsets, and G[0xE4] / G[0xE8] come from Q + align(Q[0x28]). */
void func_003E0B48(s32 arg0) {
    s32 tbl[13];
    s32 k;
    s32 x;
    s32 y;
    u8 *g;
    u8 *q;
    u8 *t;
    u8 *z;

    D_00427338 = func_28BAA8(0xEC);
    memset(D_00427338, 0, 0xEC);

    t = D_004213A4;
    x = *(s32 *)(t + 4 * arg0);
    *(u8 **)(D_00427338 + 0x0) = t + ALIGN4X(x);
    *(u8 **)(D_00427338 + 0x4) = func_2B24C8(*(u8 **)(D_00427338 + 0x0), 0, 0);

    memcpy(tbl, D_004278F0, 0x34);
    for (k = 0; k < 13; k++) {
        q = *(u8 **)(D_00427338 + 0x4);
        y = *(s32 *)(q + 4 * tbl[k]);
        Res_RelocateOffsets(D_00427338 + 0x58 + 4 * k, q + ALIGN4X(y), q + ALIGN4X(y));
    }

    g = D_00427338;
    *(s32 *)(g + 0x8C) = *(s32 *)(*(u8 **)(g + 0x6C) + 0x10);
    *(s32 *)(g + 0x90) = *(s32 *)(*(u8 **)(g + 0x68) + 0x10) + 0x40;
    *(s32 *)(g + 0x94) = *(s32 *)(*(u8 **)(g + 0x68) + 0x10);
    *(s32 *)(g + 0x98) = *(s32 *)(*(u8 **)(g + 0x64) + 0x10);
    *(s32 *)(g + 0x9C) = *(s32 *)(*(u8 **)(g + 0x60) + 0x10);
    *(s32 *)(g + 0xA0) = *(s32 *)(*(u8 **)(g + 0x60) + 0x10) + 0x40;
    *(s32 *)(g + 0xA4) = *(s32 *)(*(u8 **)(g + 0x64) + 0x10) + 0x40;
    *(s32 *)(g + 0xA8) = *(s32 *)(*(u8 **)(g + 0x88) + 0x10);
    *(s32 *)(g + 0xAC) = *(s32 *)(*(u8 **)(g + 0x58) + 0x10);
    *(s32 *)(g + 0xB0) = *(s32 *)(*(u8 **)(g + 0x5C) + 0x10);
    *(s32 *)(g + 0xB4) = *(s32 *)(*(u8 **)(g + 0x78) + 0x10);
    *(s32 *)(g + 0xB8) = *(s32 *)(*(u8 **)(g + 0x78) + 0x10);
    *(s32 *)(g + 0xBC) = *(s32 *)(*(u8 **)(g + 0x78) + 0x10);
    *(s32 *)(g + 0xC0) = *(s32 *)(*(u8 **)(g + 0x84) + 0x10);
    *(s32 *)(g + 0xC4) = *(s32 *)(*(u8 **)(g + 0x84) + 0x10) + 0x40;
    *(s32 *)(g + 0xC8) = *(s32 *)(*(u8 **)(g + 0x84) + 0x10) + 0x80;

    q = *(u8 **)(g + 0x4);
    func_26E7F0(g + 0x8, q + ALIGN4X(*(s32 *)(q + 0x4)), g + 0x8C);
    func_26EAE0(g + 0x8, 0x3C);
    q = *(u8 **)(g + 0x4);
    func_26E7F0(g + 0x30, q + ALIGN4X(*(s32 *)(q + 0x14)), g + 0xB4);
    func_26EAE0(g + 0x30, 0x3C);

    g = D_00427338;
    q = *(u8 **)(g + 0x4);
    z = q + ALIGN4X(*(s32 *)(q + 0x28));
    *(s32 *)(g + 0xE8) = *(s32 *)z;
    *(u8 **)(g + 0xE4) = z + 4;
}
