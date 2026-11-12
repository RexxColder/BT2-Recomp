#include "common.h"

/* 0x00243E38: creates the 0x128C-byte menu resource block (D_00387958): loads the resource pack, relocates its 33
 * sub-resources (offset table D_003720A0) into the block at +0xB0, derives the per-resource pointers at +0x134..,
 * initialises the sub-menu objects and picks the initial page (+0x1284) from the pad-state shorts. Returns 1. */
extern u8 *D_00387958;
extern u8 *D_003876A4;
extern u8 *D_00387F2C;
extern s32 D_003720A0[33];

u8 *func_0028BAA8(s32 size);
void Res_RelocateOffsets(u8 *dst, u8 *base, u8 *base2);
u8 *func_00100D58(s32 a, s32 b, s32 c);
u8 *func_002B24C8(u8 *a, s32 b, s32 c);
void func_00298158(s32 a);
void Vu0Cur_RotateZXYTranslate(s32 a, s32 b);
void func_0024BED8(u8 *a, u8 *b);
void func_0026E7F0(u8 *a, u8 *b, u8 *c);
void func_0026EAE0(u8 *a, s32 n);
void func_00250BF0(u8 *a);

/* g[dst] = *(g[src] + 0x10) + delta : pointers into the relocated sub-resources */
typedef struct {
    u16 dst;
    u16 src;
    u16 delta;
} PtrSlot;

static const PtrSlot kSlots[] = {
    {0x134, 0xe4, 0x40},
    {0x138, 0xe4, 0x0},
    {0x13c, 0xbc, 0x140},
    {0x140, 0xbc, 0x0},
    {0x144, 0xbc, 0x0},
    {0x148, 0xbc, 0x0},
    {0x14c, 0x104, 0x40},
    {0x150, 0x104, 0x0},
    {0x154, 0x12c, 0x0},
    {0x158, 0xb4, 0x0},
    {0x15c, 0xb4, 0x0},
    {0x160, 0xb4, 0x0},
    {0x164, 0xf0, 0x0},
    {0x1c0, 0xf8, 0x0},
    {0x168, 0xf4, 0x0},
    {0x16c, 0x10c, 0x0},
    {0x170, 0xf4, 0x40},
    {0x174, 0xd8, 0x0},
    {0x178, 0xec, 0x0},
    {0x17c, 0xd0, 0x0},
    {0x180, 0xd0, 0x40},
    {0x184, 0xb8, 0x0},
    {0x188, 0xb8, 0x0},
    {0x18c, 0xb8, 0x0},
    {0x190, 0x118, 0x0},
    {0x194, 0x100, 0x0},
    {0x19c, 0xe0, 0x0},
    {0x1a0, 0xe8, 0x0},
    {0x1a8, 0xc0, 0x0},
    {0x1ac, 0x114, 0x0},
    {0x1b0, 0xd4, 0x0},
    {0x1b4, 0x11c, 0x0},
    {0x1b8, 0xdc, 0x0},
    {0x1bc, 0xc4, 0x0},
    {0x198, 0x130, 0x0},
    {0x1c4, 0x110, 0x0},
    {0x1c8, 0xc8, 0x0},
    {0x1cc, 0xc8, 0x40},
    {0x1d0, 0xc8, 0x80},
    {0x1d4, 0x120, 0x0},
    {0x1d8, 0x124, 0x0},
    {0x1dc, 0x128, 0x0},
    {0x1e0, 0xfc, 0x0},
    {0x1e4, 0xcc, 0x0},
    {0x1e8, 0xf8, 0x0}
};

/* word of the relocated header (A4[off]) rounded to 4 bytes, as an address inside the pack */
#define PACK_PTR(pack, off) ((pack) + ((*(u32 *)((pack) + (off)) >> 2) << 2))

s32 func_00243E38(void) {
    u8 *g;
    u8 *pack;
    u8 *p;
    s32 i;
    s16 *pad;

    g = func_0028BAA8(0x128C);
    D_00387958 = g;
    __builtin_memset(g, 0, 0x128C);
    *(s32 *)(D_00387958 + 0x1258) = 1;
    *(s32 *)(D_00387958 + 0x125C) = 100;
    *(s32 *)(D_00387958 + 0x1260) = 2;
    *(s32 *)(D_00387958 + 0x1264) = 90;
    *(s32 *)(D_00387958 + 0x1268) = 3;
    *(s32 *)(D_00387958 + 0x126C) = 80;
    *(s32 *)(D_00387958 + 0x1270) = 4;
    *(s32 *)(D_00387958 + 0x1274) = 50;

    g = D_00387958;
    if (*(s32 *)(g + 0xA0) == 0) {
        func_00100D58(*(s32 *)(D_003876A4 + 4) + 0xD, 0, 1);
        do {
            p = func_00100D58(0, 0, 0);
            *(u8 **)(D_00387958 + 0xA0) = p;
        } while (p == 0);
        g = D_00387958;
    }
    *(u8 **)(D_00387958 + 0xA4) = func_002B24C8(*(u8 **)(g + 0xA0), 0, 0);

    if (*(s32 *)(D_003876A4 + 0x1C) == 5) {
        func_00298158(0);
    } else {
        Vu0Cur_RotateZXYTranslate(0, 17);
    }

    i = 0;
    do {
        g = D_00387958;
        pack = *(u8 **)(g + 0xA4);
        p = PACK_PTR(pack, D_003720A0[i] * 4);
        i++;
        Res_RelocateOffsets(g + 0xB0 + (i - 1) * 4, p, p);
    } while (i < 33);

    for (i = 0; i < (s32)(sizeof(kSlots) / sizeof(kSlots[0])); i++) {
        g = D_00387958;
        *(s32 *)(g + kSlots[i].dst) = *(s32 *)(*(u8 **)(g + kSlots[i].src) + 0x10) + kSlots[i].delta;
    }

    g = D_00387958;
    pack = *(u8 **)(g + 0xA4);
    func_0024BED8(PACK_PTR(pack, 0xB8), *(u8 **)(*(u8 **)(g + 0x108) + 0x10));
    g = D_00387958;
    pack = *(u8 **)(g + 0xA4);
    *(u8 **)(g + 0x1278) = PACK_PTR(pack, 0xAC);
    g = D_00387958;
    pack = *(u8 **)(g + 0xA4);
    *(u8 **)(g + 0x127C) = PACK_PTR(pack, 0xA8);
    g = D_00387958;
    pack = *(u8 **)(g + 0xA4);
    *(u8 **)(g + 0x1280) = PACK_PTR(pack, 0xA4);
    g = D_00387958;
    pack = *(u8 **)(g + 0xA4);
    func_0026E7F0(g + 0x28, PACK_PTR(pack, 4), g + 0x134);
    g = D_00387958;
    func_0026EAE0(g + 0x28, 0x3C);
    g = D_00387958;
    pack = *(u8 **)(g + 0xA4);
    func_0026E7F0(g, PACK_PTR(pack, 0x18), g + 0x1C8);
    g = D_00387958;
    func_0026EAE0(g, 0x3C);
    g = D_00387958;
    pack = *(u8 **)(g + 0xA4);
    func_0026E7F0(g + 0x50, PACK_PTR(pack, 0xBC), g + 0x1E0);
    g = D_00387958;
    pack = *(u8 **)(g + 0xA4);
    func_0026E7F0(g + 0x78, PACK_PTR(pack, 0x80), g + 0x1D4);
    g = D_00387958;
    pack = *(u8 **)(g + 0xA4);
    *(u8 **)(g + 0xA8) = PACK_PTR(pack, 0x90);
    g = D_00387958;
    pack = *(u8 **)(g + 0xA4);
    *(u8 **)(g + 0xAC) = PACK_PTR(pack, 0xA0);
    g = D_00387958;
    pack = *(u8 **)(g + 0xA4);
    *(u8 **)(g + 0x1254) = PACK_PTR(pack, 0x9C);
    g = D_00387958;
    pack = *(u8 **)(g + 0xA4);
    p = PACK_PTR(pack, 0x94);
    *(s32 *)(g + 0x124C) = *(s32 *)p;
    *(u8 **)(D_00387958 + 0x1250) = p + 4;
    g = D_00387958;
    pack = *(u8 **)(g + 0xA4);
    func_00250BF0(PACK_PTR(pack, 0x98));

    pad = (s16 *)D_00387F2C;
    if (*(s16 *)((u8 *)pad + 0x24EA) > 0) {
        *(s32 *)(D_00387958 + 0x1284) = 3;
        g = D_00387958;
    } else if (*(s16 *)((u8 *)pad + 0x24E6) > 0) {
        *(s32 *)(D_00387958 + 0x1284) = 2;
        g = D_00387958;
    } else if (*(s16 *)((u8 *)pad + 0x24E2) > 0) {
        *(s32 *)(D_00387958 + 0x1284) = 1;
        g = D_00387958;
    } else {
        g = D_00387958;
        if (*(s16 *)((u8 *)pad + 0x24DE) > 0) {
            *(s32 *)(D_00387958 + 0x1284) = 0;
            g = D_00387958;
        }
    }
    *(s32 *)(g + 0x1288) = 1;
    return 1;
}
