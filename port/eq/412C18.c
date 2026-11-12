#include "common.h"

/* Menu overlay: character select screen setup (allocates the work area, loads and relocates the
 * resource pack, copies the save buffers, initialises the cursor state). Sibling of 0x00405C98. */
extern u8 *D_0042BB7C;   /* menu work area (0xBB94 bytes) */
extern u8 *D_003876A4;   /* player data */
extern u8 *D_00387F2C;   /* default 0x4000-byte buffer */
extern u8 *D_00421394;   /* resource table */
extern u8 D_0042E648[45] __attribute__((aligned(1)));
extern u8 D_0042E678[];  /* name string ("DBZT2") */
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
void func_004120D0(s32 side);

#define W32(base, off)  (*(s32 *)((base) + (off)))
#define WPTR(base, off) (*(u8 **)((base) + (off)))
/* start of the chunk whose (4-aligned) offset is stored at res+off */
#define CHUNK(res, off) ((res) + ((*(u32 *)((res) + (off)) >> 2) << 2))

s32 func_00412C18(s32 stage) {
    u8 *g;       /* work area */
    u8 *res;     /* resource pack */
    u8 *chunk;   /* current chunk (Res_RelocateOffsets takes its address) */
    u8 *tbl;
    u8 *pd;      /* player data */
    s32 i;
    s32 m;
    s32 loaded;
    s32 off8;
    s32 off20;

    chunk = 0;
    g = func_0028BAA8(0xBB94);
    D_0042BB7C = g;
    __builtin_memset(g, 0, 0xBB94);

    tbl = D_00421394;
    WPTR(D_0042BB7C, 0) = tbl + ((*(u32 *)(tbl + 4 * stage) >> 2) << 2);

    g = D_0042BB7C;
    WPTR(g, 4) = func_002B24C8(WPTR(g, 0), 0, 0);
    res = WPTR(g, 4);
    W32(D_0042BB7C, 0x3740) = W32(D_003876A4, 0x458);

    chunk = CHUNK(res, 0xC);
    Res_RelocateOffsets(&chunk, chunk, chunk);
    WPTR(g, 0x128) = chunk;

    chunk = CHUNK(res, 0x28);
    Res_RelocateOffsets(&chunk, chunk, chunk);
    WPTR(g, 0x154) = WPTR(chunk, 0x10);
    WPTR(g, 0x158) = WPTR(chunk, 0x10) + 0x40;

    chunk = CHUNK(res, 0x10);
    Res_RelocateOffsets(&chunk, chunk, chunk);
    WPTR(g, 0x12C) = WPTR(chunk, 0x10);

    chunk = CHUNK(res, 0x18);
    Res_RelocateOffsets(&chunk, chunk, chunk);
    WPTR(g, 0x138) = WPTR(chunk, 0x10);

    func_0026E7F0(g + 0x60, CHUNK(res, 0x30), g + 0x12C);
    func_0026EAE0(g + 0x60, 0x3C);

    chunk = CHUNK(res, 0x14);
    Res_RelocateOffsets(&chunk, chunk, chunk);
    WPTR(g, 0x15C) = WPTR(chunk, 0x10);
    WPTR(g, 0x160) = WPTR(chunk, 0x10) + 0x40;
    WPTR(g, 0x164) = WPTR(chunk, 0x10) + 0x80;

    chunk = CHUNK(res, 0x78);
    Res_RelocateOffsets(&chunk, chunk, chunk);
    WPTR(g, 0x168) = WPTR(chunk, 0x10);

    chunk = CHUNK(res, 0x74);
    Res_RelocateOffsets(&chunk, chunk, chunk);
    WPTR(g, 0x16C) = WPTR(chunk, 0x10);
    WPTR(g, 0x170) = WPTR(chunk, 0x10) + 0x40;

    func_0026E7F0(g + 0xD8, CHUNK(res, 0x20), g + 0x15C);
    func_0026EAE0(g + 0xD8, 0x3C);
    func_0026E7F0(g + 0x100, CHUNK(res, 0x24), g + 0x15C);
    func_0026EAE0(g + 0x100, 0x3C);

    chunk = CHUNK(res, 0x3C);
    Res_RelocateOffsets(&chunk, chunk, chunk);
    WPTR(g, 0x174) = WPTR(chunk, 0x10);
    WPTR(g, 0x17C) = WPTR(chunk, 0x10) + 0x40;
    WPTR(g, 0x178) = WPTR(chunk, 0x10) + 0x80;
    WPTR(g, 0x180) = WPTR(chunk, 0x10) + 0xC0;

    func_0026E7F0(g + 0x38, CHUNK(res, 0x40), g + 0x174);
    func_0026EAE0(g + 0x38, 0x3C);

    chunk = CHUNK(res, 0x50);
    Res_RelocateOffsets(&chunk, chunk, chunk);
    WPTR(g, 0x18C) = WPTR(chunk, 0x10);
    WPTR(g, 0x184) = WPTR(chunk, 0x10) + 0x40;

    chunk = CHUNK(res, 0x58);
    Res_RelocateOffsets(&chunk, chunk, chunk);
    WPTR(g, 0x1DC) = WPTR(chunk, 0x10);
    WPTR(g, 0x1D4) = WPTR(chunk, 0x10) + 0x40;

    chunk = CHUNK(res, 0x48);
    Res_RelocateOffsets(&chunk, chunk, chunk);
    WPTR(g, 0x188) = WPTR(chunk, 0x10);
    WPTR(g, 0x1D8) = WPTR(chunk, 0x10);

    chunk = CHUNK(res, 0x44);
    Res_RelocateOffsets(&chunk, chunk, chunk);
    WPTR(g, 0x1B0) = WPTR(chunk, 0x10);
    WPTR(g, 0x1B4) = WPTR(chunk, 0x10) + 0x40;
    WPTR(g, 0x1AC) = WPTR(chunk, 0x10) + 0x80;
    WPTR(g, 0x200) = WPTR(chunk, 0x10);
    WPTR(g, 0x204) = WPTR(chunk, 0x10) + 0x40;
    WPTR(g, 0x1FC) = WPTR(chunk, 0x10) + 0x80;

    func_0026E7F0(g + 0x88, CHUNK(res, 0x4C), g + 0x184);
    func_0026EAE0(g + 0x88, 0x3C);
    func_0026E7F0(g + 0xB0, CHUNK(res, 0x54), g + 0x1D4);
    func_0026EAE0(g + 0xB0, 0x3C);

    WPTR(g, 0x34) = CHUNK(res, 0x70);
    func_0029BB88(CHUNK(res, 0x6C), WPTR(g, 0x34));

    W32(g, 0x3764) = -1;
    __builtin_memcpy(g + 0x3A8C, D_0042E648, 45);
    W32(g, 0x3B90) = 0x18;
    func_0028A0B8(g + 0x3774, D_0042E678, -1, -1, 1);

    __builtin_memcpy(D_0042BB7C + 0x3B94, D_00387F2C, 0x4000);
    __builtin_memcpy(D_0042BB7C + 0x7B94, D_00387F2C, 0x4000);

    g = D_0042BB7C;
    loaded = W32(g, 0x3740);
    if (loaded == 1) {
        pd = D_003876A4;
        if (W32(pd, 0x18) & 0x1000) {
            McCard_GetInfoSync(1);
            if (W32(gMcCardPort, 0x30) == 2 && (u32)(W32(gMcCardPort, 0x2C) + 1) < 2) {
                W32(D_0042BB7C, 0x3768) = loaded;
                func_0029C550(0);
                func_0029C820(1);
                func_0029C7E0(1);
                func_0029C810(1);
                func_00288348();
                W32(D_0042BB7C, 0x376C) = 0x78;
            } else {
                func_00288348();
                W32(D_0042BB7C, 0x3768) = 0;
                WPTR(D_003876A4, 0x4C8) = D_0042BB7C + 0x3B94;
                WPTR(D_003876A4, 0x4CC) = D_0042BB7C + 0x7B94;
            }
        } else if (W32(pd, 0x18) & 0x2000) {
            __builtin_memcpy(D_0042BB7C + 0x8F9C, WPTR(pd, 0x4D0), 0xB28);
            __builtin_memcpy(D_0042BB7C + 0x9AC4, WPTR(D_003876A4, 0x4D4), 0x90C);
            WPTR(D_003876A4, 0x4C8) = D_0042BB7C + 0x3B94;
            WPTR(D_003876A4, 0x4CC) = D_0042BB7C + 0x7B94;
        } else {
            WPTR(pd, 0x4C8) = D_0042BB7C + 0x3B94;
            WPTR(D_003876A4, 0x4CC) = D_0042BB7C + 0x7B94;
        }
        W32(D_003876A4, 0x18) &= ~0x1000;
    } else {
        WPTR(D_003876A4, 0x4C8) = 0;
        WPTR(D_003876A4, 0x4CC) = 0;
    }

    g = D_0042BB7C;
    res = WPTR(g, 4);
    WPTR(g, 0x28) = func_002B24C8(CHUNK(res, 4), 0, 0);
    for (i = 0; i < 0x86; i++) {
        u8 *tab = WPTR(D_0042BB7C, 0x28);
        chunk = tab + ((*(u32 *)(tab + 4 * i + 4) >> 2) << 2);
        Res_RelocateOffsets(&chunk, chunk, chunk);
    }

    g = D_0042BB7C;
    res = WPTR(g, 4);
    WPTR(g, 0x2D8) = CHUNK(res, 0x2C) + 4;
    res = WPTR(g, 4);
    W32(g, 0x2D4) = *(s32 *)CHUNK(res, 0x2C);
    func_00248708(g + 0x2E0, g + 0x2E4, g + 0x2D4, g + 0x2D8);

    g = D_0042BB7C;
    W32(g, 0x2D4) = W32(g, 0x2E0);
    WPTR(g, 0x2D8) = g + 0x2E4;
    WPTR(g, 0x2DC) = g + 0x1AF4;
    g = D_0042BB7C;
    W32(g, 0x3734) = W32(g, 0x2D4) / 7;
    if (W32(g, 0x2D4) % 7 != 0) {
        W32(g, 0x3734) = W32(g, 0x3734) + 1;
    }

    g = D_0042BB7C;
    res = WPTR(g, 4);
    WPTR(g, 0x2C) = CHUNK(res, 0x34);
    WPTR(g, 0x30) = CHUNK(res, 0x38);
    WPTR(g, 0x375C) = CHUNK(res, 0x68) + 4;
    WPTR(g, 0x3760) = CHUNK(res, 0x64) + 4;

    for (i = 0; i < 2; i++) {
        for (m = 0; m < 2; m++) {
            WPTR(D_0042BB7C, 8 + 8 * i + 4 * m) = func_0028BAA8(0xB000);
            WPTR(D_0042BB7C, 0x18 + 8 * i + 4 * m) = func_0028BAA8(0x10560);
        }
    }
    W32(D_0042BB7C, 0x373C) = 1;
    W32(D_0042BB7C, 0x230) = W32(D_0042BB7C, 0x230) | 1;

    /* validate the saved selections of both players */
    for (i = 0; i < 2; i++) {
        for (m = 0; m < 2; m++) {
            off20 = 20 * i + 4 * m;
            if (!func_0024ACB8(W32(D_0042BB7C, 0x2D8 + 4 * i), W32(D_003876A4, 0x390 + off20))) {
                W32(D_003876A4, 0x390 + off20) = i;
                W32(D_003876A4, 0x3B8 + off20) = 0;
                W32(D_003876A4, 0x430 + off20) = 0;
                W32(D_003876A4, 0x408 + off20) = 0;
            }
        }
    }

    /* copy the selections into the work area */
    for (i = 0; i < 2; i++) {
        for (m = 0; m < 2; m++) {
            off20 = 20 * i + 4 * m;
            off8 = 8 * i + 4 * m;
            W32(D_0042BB7C, 0x23C + off8) = W32(D_003876A4, 0x390 + off20) % 7;
            W32(D_0042BB7C, 0x24C + off8) = W32(D_003876A4, 0x390 + off20) / 7;
            W32(D_0042BB7C, 0x2B4 + off8) = W32(D_003876A4, 0x3B8 + off20);
            W32(D_0042BB7C, 0x2C4 + off8) = W32(D_003876A4, 0x430 + off20);
            W32(D_0042BB7C, 0x25C + off8) = W32(D_003876A4, 0x408 + off20);
            g = D_0042BB7C;
            W32(g, 0x3304 + 4 * (7 * W32(g, 0x24C + off8) + 134 * i + W32(g, 0x23C + off8))) =
                W32(g, 0x25C + off8);
        }
        W32(D_0042BB7C, 0x27C + 4 * i) = 0;
        W32(D_0042BB7C, 0x284 + 4 * i) = 0;
        func_004120D0(i);
    }

    /* copy each selected entry's variant back into its slot */
    for (i = 0; i < 2; i++) {
        for (m = 1; m >= 0; m--) {
            u8 *entry;
            off8 = 8 * i + 4 * m;
            g = D_0042BB7C;
            entry = WPTR(g, 0x2D8 + 4 * i) + 44 * (7 * W32(g, 0x24C + off8) + W32(g, 0x23C + off8));
            W32(entry, 0) = W32(entry, 8 + 4 * W32(g, 0x25C + off8));
            g = D_0042BB7C;
            entry = WPTR(g, 0x2D8 + 4 * i) + 44 * (7 * W32(g, 0x24C + off8) + W32(g, 0x23C + off8));
            W32(g, 0x26C + off8) = W32(entry, 0);
        }
        func_004120D0(i);
    }
    return 0;
}
