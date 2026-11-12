#include "common.h"

#define LD32(p, off) (*(s32 *)((u8 *)(p) + (off)))
#define ST32(p, off, v) (*(s32 *)((u8 *)(p) + (off)) = (s32)(v))

void *memset(void *dst, s32 c, u32 n);
void *memcpy(void *dst, const void *src, u32 n);
s32 func_0028BAA8(s32 arg0);
s32 func_002B24C8(s32 arg0, s32 arg1, s32 arg2);
void Res_RelocateOffsets(s32 arg0, s32 arg1, s32 arg2);
void func_0026E7F0(s32 arg0, s32 arg1, s32 arg2);
void func_0026EAE0(s32 arg0, s32 arg1);

extern u8 *D_00387988;
extern s32 D_00374A58[] __attribute__((section(".data")));

/* 0x0024BED8: allocates and clears the 0x54-byte block D_00387988, sets its first word from func_002B24C8 and
 * relocates three offset tables from the block at that word (entries of the copied D_00374A58 index), then
 * fills the pointers at +0x38..+0x44, stores arg1 at +0x48 and relocates the table at +4 with func_0026E7F0
 * and func_0026EAE0. */
void func_0024BED8(s32 arg0, s32 arg1) {
    s32 tbl[3];
    s32 s;
    s32 base;
    s32 off;
    s32 r;
    s32 g;

    g = func_0028BAA8(0x54);
    D_00387988 = (u8 *)(s32)g;
    memset((void *)(s32)g, 0, 0x54);

    ST32(g, 0, func_002B24C8(arg0, 0, 0));

    memcpy(tbl, D_00374A58, 12);
    for (s = 0; s < 3; s++) {
        base = LD32(g, 0);
        off = LD32(base, tbl[s] * 4) & ~3;
        Res_RelocateOffsets(g + 0x2C + s * 4, base + off, base + off);
    }

    ST32(g, 0x38, LD32(LD32(g, 0x2C), 0x10));
    ST32(g, 0x3C, LD32(LD32(g, 0x30), 0x10));
    ST32(g, 0x40, LD32(LD32(g, 0x30), 0x10) + 0x40);
    ST32(g, 0x44, LD32(LD32(g, 0x34), 0x10));
    ST32(g, 0x48, arg1);

    r = LD32(g, 0);
    off = LD32(r, 4) & ~3;
    func_0026E7F0(g + 4, r + off, g + 0x38);
    func_0026EAE0(g + 4, 0x3C);
}
