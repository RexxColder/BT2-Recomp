#include "common.h"

/* menu overlay: character select screen init (arg0 = resource index) */

extern u8 *D_00423114 __attribute__((section(".data")));   /* screen object */
extern u8 *D_00421390 __attribute__((section(".data")));   /* resource pack */
extern u8 D_00423168[0x2D] __attribute__((section(".data"), aligned(1)));
extern char D_00423198[] __attribute__((section(".data")));
extern u8 gMcCardPort[] __attribute__((section(".data")));
extern u8 *D_00387F2C;   /* save data */
extern u8 *D_003876A4;   /* game settings */

void *func_0028BAA8(s32 size);
void *memset(void *p, s32 v, u32 n);
u8 *func_002B24C8(u8 *a, s32 b, s32 c);
void Res_RelocateOffsets(u8 *a0, u8 *a1, u8 *a2);
void func_0026E7F0(u8 *obj, u8 *data, u8 *table);
void func_0026EAE0(u8 *obj, s32 v);
void func_0029BB88(u8 *a, u8 *b);
s32 func_0028A0B8(u8 *dst, const char *name, s32 a, s32 b, s32 c);
void McCard_GetInfoSync(s32 port);
void func_00288348(void);
void func_0029C550(s32 v);
void func_0029C820(s32 v);
void func_0029C7E0(s32 v);
void func_0029C810(s32 v);
void func_00248708(u8 *a, u8 *b, u8 *c, u8 *d);
s32 func_0024ACB8(u8 *tbl, s32 idx);
void func_003C6408(s32 v);
s32 func_003C6AA0(void);

#define W(o)   (*(s32 *)(scr + (o)))
#define PTR(o) (*(u8 **)(scr + (o)))
#define SUB(o) (*(u32 *)(PTR(4) + (o)) & ~3u)
#define GS(o)  (*(s32 *)(D_003876A4 + (o)))

/* relocate the sub-block at offset k of the pack and leave its address in sp0 */
#define RELOC_BLOCK(k) \
    do { \
        sp0 = PTR(4) + SUB(k); \
        Res_RelocateOffsets((u8 *)&sp0, sp0, sp0); \
    } while (0)
#define BLOCK_OUT(o) (*(u8 **)(sp0 + 0x10) + (o))

s32 func_003C6CC0(s32 packIndex) {
    u8 *scr;
    u8 *sp0 = 0;
    u8 *sp4 = 0;
    u8 *base;
    u8 *ent;
    s32 i;
    s32 idx;

    scr = (u8 *)func_0028BAA8(0xBB18);
    D_00423114 = scr;
    memset(scr, 0, 0xBB18);

    base = D_00421390;
    PTR(0) = base + (*(u32 *)(base + packIndex * 4) & ~3u);
    PTR(4) = func_002B24C8(PTR(0), 0, 0);

    PTR(0xC0) = PTR(4) + SUB(8);
    Res_RelocateOffsets(scr + 0xC0, PTR(0xC0), PTR(0xC0));

    RELOC_BLOCK(0x54); PTR(0xC4) = *(u8 **)(sp0 + 0x10);
    RELOC_BLOCK(0x20); PTR(0xD8) = *(u8 **)(sp0 + 0x10);
    RELOC_BLOCK(0x0C); PTR(0xCC) = *(u8 **)(sp0 + 0x10);
    RELOC_BLOCK(0x18); PTR(0xD0) = *(u8 **)(sp0 + 0x10);
    RELOC_BLOCK(0x10); PTR(0xD4) = *(u8 **)(sp0 + 0x10);
    RELOC_BLOCK(0x14); PTR(0x108) = *(u8 **)(sp0 + 0x10);
    RELOC_BLOCK(0x3C); PTR(0xE8) = *(u8 **)(sp0 + 0x10);
    func_0026E7F0(scr + 0x48, PTR(4) + SUB(4), scr + 0xC4);
    func_0026EAE0(scr + 0x48, 60);

    RELOC_BLOCK(0x24);
    PTR(0x120) = *(u8 **)(sp0 + 0x10);
    PTR(0x124) = *(u8 **)(sp0 + 0x10) + 0x40;
    PTR(0x128) = *(u8 **)(sp0 + 0x10) + 0x80;
    RELOC_BLOCK(0x64); PTR(0x12C) = *(u8 **)(sp0 + 0x10);
    RELOC_BLOCK(0x60);
    PTR(0x130) = *(u8 **)(sp0 + 0x10);
    PTR(0x134) = *(u8 **)(sp0 + 0x10) + 0x40;
    func_0026E7F0(scr + 0x98, PTR(4) + SUB(0x30), scr + 0x120);
    func_0026EAE0(scr + 0x98, 60);

    RELOC_BLOCK(0x1C); PTR(0x13C) = *(u8 **)(sp0 + 0x10);
    RELOC_BLOCK(0x40);
    PTR(0x140) = *(u8 **)(sp0 + 0x10);
    PTR(0x138) = *(u8 **)(sp0 + 0x10) + 0x40;
    RELOC_BLOCK(0x44);
    PTR(0x164) = *(u8 **)(sp0 + 0x10);
    PTR(0x168) = *(u8 **)(sp0 + 0x10) + 0x40;
    PTR(0x160) = *(u8 **)(sp0 + 0x10) + 0x80;
    func_0026E7F0(scr + 0x70, PTR(4) + SUB(0x48), scr + 0x138);
    func_0026EAE0(scr + 0x70, 60);

    RELOC_BLOCK(0x4C);
    PTR(0x110) = *(u8 **)(sp0 + 0x10);
    PTR(0x118) = *(u8 **)(sp0 + 0x10) + 0x40;
    PTR(0x114) = *(u8 **)(sp0 + 0x10) + 0x80;
    PTR(0x11C) = *(u8 **)(sp0 + 0x10) + 0xC0;
    func_0026E7F0(scr + 0x20, PTR(4) + SUB(0x50), scr + 0x110);
    func_0026EAE0(scr + 0x20, 60);

    PTR(0x1C) = PTR(4) + SUB(0x5C);
    func_0029BB88(PTR(4) + SUB(0x58), PTR(0x1C));

    W(0x36E8) = -1;
    __builtin_memcpy(scr + 0x3A10, D_00423168, 0x2D);   /* text table (SJIS) */
    W(0x3B14) = 0x18;
    func_0028A0B8(scr + 0x36F8, D_00423198, -1, -1, 1);

    /* two copies of the 0x4000-byte save block */
    __builtin_memcpy(scr + 0x3B18, D_00387F2C, 0x4000);
    __builtin_memcpy(scr + 0x7B18, D_00387F2C, 0x4000);

    if (!(GS(0x18) & 0x1000)) {
        if (GS(0x18) & 0x2000) {
            __builtin_memcpy(scr + 0x8F20, *(u8 **)(D_003876A4 + 0x4D0), 0xB28);
            __builtin_memcpy(scr + 0x9A48, *(u8 **)(D_003876A4 + 0x4D4), 0x90C);
            GS(0x4C8) = (s32)(scr + 0x3B18);
            GS(0x4CC) = (s32)(scr + 0x7B18);
            W(0x18C) |= 0x20000000;
        } else {
            GS(0x4C8) = (s32)(scr + 0x3B18);
            GS(0x4CC) = (s32)(scr + 0x3B18);
        }
    } else {
        McCard_GetInfoSync(1);
        if (*(s32 *)(gMcCardPort + 0x30) == 2 &&
            (u32)(*(s32 *)(gMcCardPort + 0x2C) + 1) < 2) {
            W(0x36EC) = 1;
            func_0029C550(0);
            func_0029C820(1);
            func_0029C7E0(1);
            func_0029C810(1);
            func_00288348();
            W(0x36F0) = 0x78;
        } else {
            func_00288348();
            W(0x36EC) = 0;
            GS(0x4C8) = (s32)(scr + 0x3B18);
            GS(0x4CC) = (s32)(scr + 0x3B18);
        }
    }
    GS(0x18) &= ~0x1000;

    PTR(0x10) = func_002B24C8(PTR(4) + SUB(0x28), 0, 0);
    for (i = 0; i < 0x86; i++) {
        u8 *tbl = PTR(0x10);

        sp4 = tbl + (*(u32 *)(tbl + 4 + i * 4) & ~3u);
        Res_RelocateOffsets((u8 *)&sp4, sp4, sp4);
    }

    PTR(0x1CC) = PTR(4) + SUB(0x2C) + 4;
    W(0x1C8) = *(s32 *)(PTR(4) + SUB(0x2C));
    PTR(0x14) = PTR(4) + SUB(0x34);
    PTR(0x18) = PTR(4) + SUB(0x38);
    func_00248708(scr + 0x1D4, scr + 0x1D8, scr + 0x1C8, scr + 0x1CC);
    W(0x1C8) = W(0x1D4);
    PTR(0x1CC) = scr + 0x1D8;
    PTR(0x1D0) = scr + 0x19E8;
    W(0x3628) = W(0x1C8) / 7;
    PTR(8) = (u8 *)func_0028BAA8(0x17800);
    PTR(0xC) = (u8 *)func_0028BAA8(0x20560);
    W(0x362C) = 1;

    if (!func_0024ACB8(PTR(0x1CC), GS(0x390))) {
        GS(0x390) = 0;
        GS(0x3B8) = 0;
        GS(0x408) = 0;
        GS(0x430) = 0;
    }
    W(0x190) = GS(0x390) % 7;
    W(0x198) = GS(0x390) / 7;
    W(0x1A8) = GS(0x3B8);
    W(0x1A0) = GS(0x408);
    W(0x1B0) = GS(0x430);
    W(0x1B8) = GS(0x430);
    func_003C6408(0);

    idx = 7 * W(0x198) + W(0x190);
    ent = PTR(0x1CC) + 44 * idx;
    *(s32 *)ent = *(s32 *)(ent + 4 * W(0x1A0) + 8);
    func_003C6408(0);

    W(0x3638) = GS(0x8C);
    W(0x363C) = GS(0x90);
    W(0x3640) = GS(0x94);
    memset(D_003876A4 + 0xA0, 0, 0x200);
    return func_003C6AA0();
}
