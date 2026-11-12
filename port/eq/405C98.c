#include "common.h"

extern u8 *D_0042BB74;   /* menu work area (0xBB14 bytes) */
extern u8 *D_003876A4;   /* player data */
extern u8 *D_00387F2C;   /* default 0x4000-byte buffer */
extern u8 *D_00421394;   /* resource table (normal) */
extern u8 *D_004213A0;   /* resource table (mode 0x3F) */
extern u8 D_0042D928[45] __attribute__((aligned(1)));
extern u8 D_0042D958[];  /* name string ("DBZT2") */
extern u8 gMcCardPort[] __attribute__((section(".data")));

void Res_RelocateOffsets(void *arg0, void *arg1, void *arg2);
u8 *func_0028BAA8(s32 size);
u8 *func_002B24C8(u8 *arg0, u8 *arg1, s32 *arg2);
void func_0026E7F0(u8 *dst, u8 *src, u8 *tbl);
void func_0026EAE0(u8 *dst, s32 n);
void func_0029BB88(u8 *a0, u8 *a1);
void func_0028A0B8(u8 *a0, u8 *name, s32 a2, s32 a3, s32 t0);
void McCard_GetInfoSync(s32 port);
s32 func_00288348(void);
void func_0029C550(s32 a0);
void func_0029C820(s32 a0);
void func_0029C7E0(s32 a0);
void func_0029C810(s32 a0);
void func_00248708(u8 *a0, u8 *a1, u8 *a2, u8 *a3);
s32 func_0024ACB8(s32 a0, s32 a1);
void func_00405500(s32 a0);
void func_00405BA0(s32 a0);

#define W32(base, off)  (*(s32 *)((base) + (off)))
#define WPTR(base, off) (*(u8 **)((base) + (off)))
/* start of the chunk whose (4-aligned) offset is stored at res+off */
#define CHUNK(res, off) ((res) + ((*(u32 *)((res) + (off)) >> 2) << 2))

void func_00405C98(s32 stage) {
    u8 *g;       /* work area */
    u8 *res;     /* resource pack */
    u8 *chunk;   /* current chunk (Res_RelocateOffsets takes its address) */
    u8 *tbl;
    u8 *pd;      /* player data */
    s32 i;
    s32 loaded;

    chunk = 0;
    g = func_0028BAA8(0xBB14);
    D_0042BB74 = g;
    __builtin_memset(g, 0, 0xBB14);

    pd = D_003876A4;
    if (W32(pd, 0x1C) == 0x3F) {
        W32(pd, 0x458) = 0;
    }
    W32(D_0042BB74, 0x36C4) = W32(D_003876A4, 0x458);

    tbl = (W32(D_003876A4, 0x1C) == 0x3F) ? D_004213A0 : D_00421394;
    WPTR(D_0042BB74, 0) = tbl + ((*(u32 *)(tbl + 4 * stage) >> 2) << 2);

    g = D_0042BB74;
    WPTR(g, 4) = func_002B24C8(WPTR(g, 0), 0, 0);
    res = WPTR(g, 4);
    WPTR(g, 0x118) = res + ((*(u32 *)(res + 0xC) >> 2) << 2);
    Res_RelocateOffsets(g + 0x118, WPTR(g, 0x118), WPTR(g, 0x118));

    chunk = CHUNK(res, 0x28);
    Res_RelocateOffsets(&chunk, chunk, chunk);
    WPTR(g, 0x13C) = WPTR(chunk, 0x10);
    WPTR(g, 0x140) = WPTR(chunk, 0x10) + 0x40;

    chunk = CHUNK(res, 0x10);
    Res_RelocateOffsets(&chunk, chunk, chunk);
    WPTR(g, 0x11C) = WPTR(chunk, 0x10);

    chunk = CHUNK(res, 0x18);
    Res_RelocateOffsets(&chunk, chunk, chunk);
    WPTR(g, 0x128) = WPTR(chunk, 0x10);

    func_0026E7F0(g + 0x50, CHUNK(res, 8), g + 0x11C);
    func_0026EAE0(g + 0x50, 0x3C);

    chunk = CHUNK(res, 0x14);
    Res_RelocateOffsets(&chunk, chunk, chunk);
    WPTR(g, 0x144) = WPTR(chunk, 0x10);
    WPTR(g, 0x148) = WPTR(chunk, 0x10) + 0x40;
    WPTR(g, 0x14C) = WPTR(chunk, 0x10) + 0x80;

    chunk = CHUNK(res, 0x78);
    Res_RelocateOffsets(&chunk, chunk, chunk);
    WPTR(g, 0x150) = WPTR(chunk, 0x10);

    chunk = CHUNK(res, 0x74);
    Res_RelocateOffsets(&chunk, chunk, chunk);
    WPTR(g, 0x154) = WPTR(chunk, 0x10);
    WPTR(g, 0x158) = WPTR(chunk, 0x10) + 0x40;

    func_0026E7F0(g + 0xC8, CHUNK(res, 0x20), g + 0x144);
    func_0026EAE0(g + 0xC8, 0x3C);
    func_0026E7F0(g + 0xF0, CHUNK(res, 0x24), g + 0x144);
    func_0026EAE0(g + 0xF0, 0x3C);

    chunk = CHUNK(res, 0x3C);
    Res_RelocateOffsets(&chunk, chunk, chunk);
    WPTR(g, 0x15C) = WPTR(chunk, 0x10);
    WPTR(g, 0x164) = WPTR(chunk, 0x10) + 0x40;
    WPTR(g, 0x160) = WPTR(chunk, 0x10) + 0x80;
    WPTR(g, 0x168) = WPTR(chunk, 0x10) + 0xC0;

    func_0026E7F0(g + 0x28, CHUNK(res, 0x40), g + 0x15C);
    func_0026EAE0(g + 0x28, 0x3C);

    chunk = CHUNK(res, 0x50);
    Res_RelocateOffsets(&chunk, chunk, chunk);
    WPTR(g, 0x174) = WPTR(chunk, 0x10);
    WPTR(g, 0x16C) = WPTR(chunk, 0x10) + 0x40;

    chunk = CHUNK(res, 0x58);
    Res_RelocateOffsets(&chunk, chunk, chunk);
    WPTR(g, 0x1C4) = WPTR(chunk, 0x10);
    WPTR(g, 0x1BC) = WPTR(chunk, 0x10) + 0x40;

    chunk = CHUNK(res, 0x48);
    Res_RelocateOffsets(&chunk, chunk, chunk);
    WPTR(g, 0x170) = WPTR(chunk, 0x10);
    WPTR(g, 0x1C0) = WPTR(chunk, 0x10);

    chunk = CHUNK(res, 0x44);
    Res_RelocateOffsets(&chunk, chunk, chunk);
    WPTR(g, 0x198) = WPTR(chunk, 0x10);
    WPTR(g, 0x19C) = WPTR(chunk, 0x10) + 0x40;
    WPTR(g, 0x194) = WPTR(chunk, 0x10) + 0x80;
    WPTR(g, 0x1E8) = WPTR(chunk, 0x10);
    WPTR(g, 0x1EC) = WPTR(chunk, 0x10) + 0x40;
    WPTR(g, 0x1E4) = WPTR(chunk, 0x10) + 0x80;

    func_0026E7F0(g + 0x78, CHUNK(res, 0x4C), g + 0x16C);
    func_0026EAE0(g + 0x78, 0x3C);
    func_0026E7F0(g + 0xA0, CHUNK(res, 0x54), g + 0x1BC);
    func_0026EAE0(g + 0xA0, 0x3C);

    WPTR(g, 0x24) = CHUNK(res, 0x70);
    func_0029BB88(CHUNK(res, 0x6C), WPTR(g, 0x24));

    W32(g, 0x36E4) = -1;
    __builtin_memcpy(g + 0x3A0C, D_0042D928, 45);
    W32(g, 0x3B10) = 0x18;
    func_0028A0B8(g + 0x36F4, D_0042D958, -1, -1, 1);

    __builtin_memcpy(D_0042BB74 + 0x3B14, D_00387F2C, 0x4000);
    __builtin_memcpy(D_0042BB74 + 0x7B14, D_00387F2C, 0x4000);

    g = D_0042BB74;
    loaded = W32(g, 0x36C4);
    if (loaded == 1) {
        pd = D_003876A4;
        if (W32(pd, 0x18) & 0x1000) {
            McCard_GetInfoSync(1);
            if (W32(gMcCardPort, 0x30) == 2 && (u32)(W32(gMcCardPort, 0x2C) + 1) < 2) {
                W32(D_0042BB74, 0x36E8) = loaded;
                func_0029C550(0);
                func_0029C820(1);
                func_0029C7E0(1);
                func_0029C810(1);
                func_00288348();
                W32(D_0042BB74, 0x36EC) = 0x78;
            } else {
                func_00288348();
                W32(D_0042BB74, 0x36E8) = 0;
                WPTR(D_003876A4, 0x4C8) = D_0042BB74 + 0x3B14;
                WPTR(D_003876A4, 0x4CC) = D_0042BB74 + 0x7B14;
            }
        } else if (W32(pd, 0x18) & 0x2000) {
            __builtin_memcpy(D_0042BB74 + 0x8F1C, WPTR(pd, 0x4D0), 0xB28);
            __builtin_memcpy(D_0042BB74 + 0x9A44, WPTR(D_003876A4, 0x4D4), 0x90C);
            WPTR(D_003876A4, 0x4C8) = D_0042BB74 + 0x3B14;
            WPTR(D_003876A4, 0x4CC) = D_0042BB74 + 0x7B14;
        } else {
            WPTR(pd, 0x4C8) = D_0042BB74 + 0x3B14;
            WPTR(D_003876A4, 0x4CC) = D_0042BB74 + 0x7B14;
        }
        W32(D_003876A4, 0x18) &= ~0x1000;
    } else {
        WPTR(D_003876A4, 0x4C8) = 0;
        WPTR(D_003876A4, 0x4CC) = 0;
    }

    g = D_0042BB74;
    res = WPTR(g, 4);
    WPTR(g, 0x18) = func_002B24C8(CHUNK(res, 4), 0, 0);
    for (i = 0; i < 0x86; i++) {
        u8 *tab = WPTR(D_0042BB74, 0x18);
        chunk = tab + ((*(u32 *)(tab + 4 * i + 4) >> 2) << 2);
        Res_RelocateOffsets(&chunk, chunk, chunk);
    }

    g = D_0042BB74;
    res = WPTR(g, 4);
    WPTR(g, 0x260) = CHUNK(res, 0x2C) + 4;
    res = WPTR(g, 4);
    W32(g, 0x25C) = *(s32 *)CHUNK(res, 0x2C);
    func_00248708(g + 0x268, g + 0x26C, g + 0x25C, g + 0x260);

    g = D_0042BB74;
    W32(g, 0x25C) = W32(g, 0x268);
    WPTR(g, 0x260) = g + 0x26C;
    WPTR(g, 0x264) = g + 0x1A7C;
    g = D_0042BB74;
    W32(g, 0x36BC) = W32(g, 0x25C) / 7;
    if (W32(g, 0x25C) % 7 != 0) {
        W32(g, 0x36BC) = W32(g, 0x36BC) + 1;
    }

    g = D_0042BB74;
    res = WPTR(g, 4);
    WPTR(g, 0x1C) = CHUNK(res, 0x34);
    WPTR(g, 0x20) = CHUNK(res, 0x38);
    WPTR(g, 0x36DC) = CHUNK(res, 0x68) + 4;
    WPTR(g, 0x36E0) = CHUNK(res, 0x64) + 4;
    WPTR(D_0042BB74, 8) = func_0028BAA8(0x17800);
    WPTR(D_0042BB74, 0xC) = func_0028BAA8(0x17800);
    WPTR(D_0042BB74, 0x10) = func_0028BAA8(0x20560);
    WPTR(D_0042BB74, 0x14) = func_0028BAA8(0x20560);
    W32(D_0042BB74, 0x36C0) = 1;
    W32(D_0042BB74, 0x210) = W32(D_0042BB74, 0x210) | 2;

    /* validate the two saved selections */
    for (i = 0; i < 2; i++) {
        s32 off = 0x14 * i;
        if (!func_0024ACB8(W32(D_0042BB74, 0x260 + 4 * i), W32(D_003876A4, 0x390 + off))) {
            W32(D_003876A4, 0x390 + off) = i;
            W32(D_003876A4, 0x3B8 + off) = 0;
            W32(D_003876A4, 0x408 + off) = 0;
            W32(D_003876A4, 0x430 + off) = 0;
        }
    }

    pd = D_003876A4;
    g = D_0042BB74;
    W32(g, 0x214) = W32(pd, 0x390) % 7;
    W32(D_0042BB74, 0x218) = W32(D_003876A4, 0x3A4) % 7;
    W32(D_0042BB74, 0x21C) = W32(D_003876A4, 0x390) / 7;
    W32(D_0042BB74, 0x220) = W32(D_003876A4, 0x3A4) / 7;
    W32(D_0042BB74, 0x22C) = W32(D_003876A4, 0x3B8);
    W32(D_0042BB74, 0x230) = W32(D_003876A4, 0x3CC);
    W32(D_0042BB74, 0x224) = W32(D_003876A4, 0x408);
    W32(D_0042BB74, 0x228) = W32(D_003876A4, 0x41C);
    W32(D_0042BB74, 0x234) = W32(D_003876A4, 0x430);
    W32(D_0042BB74, 0x238) = W32(D_003876A4, 0x444);
    W32(D_0042BB74, 0x23C) = W32(D_003876A4, 0x430);
    W32(D_0042BB74, 0x240) = W32(D_003876A4, 0x444);

    g = D_0042BB74;
    W32(g, 0x328C + 4 * (W32(g, 0x214) + 7 * W32(g, 0x21C))) = W32(g, 0x224);
    g = D_0042BB74;
    W32(g, 0x34A4 + 4 * (W32(g, 0x218) + 7 * W32(g, 0x220))) = W32(g, 0x228);
    func_00405500(0);
    func_00405500(1);
    func_00405BA0(0);
    func_00405BA0(1);
}
