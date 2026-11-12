#include "common.h"

extern u8 *D_0042FD70 __attribute__((section(".data")));
extern u8 *D_004213AC __attribute__((section(".data")));

u8 *func_28BAA8(s32 a0);
u8 *func_2B24C8(u8 *a0, u8 *a1, s32 a2);
void Res_RelocateOffsets(u8 *a0, u8 *a1, u8 *a2);
void func_26E7F0(u8 *a0, u8 *a1, u8 *a2);
void func_26EAE0(u8 *a0, s32 a1);

/* table rebase: o4 + (*(u32 *)(o4 + off) & ~3) */
#define RELOC_SRC(o4, off) ((o4) + (*(u32 *)((o4) + (off)) & ~3u))

/* 0x0041C1B8: builds the 0x8C-byte object O = D_0042FD70 for table entry idx (table D_004213AC). Same pattern as
 * 0x003FE0C0: O->4 from func_2B24C8, five Res_RelocateOffsets of O->4 + (word & ~3) (each out word is the
 * pointer to a 0x10-stride table of values), func_26E7F0 / func_26EAE0 and O->0x88 = 1. */
void func_0041C1B8(s32 idx) {
    u8 *O;
    u8 *T;
    u8 *q;
    u8 frame[0x10];

    *(s32 *)frame = 0;
    T = D_004213AC;
    O = func_28BAA8(0x8C);
    D_0042FD70 = O;
    memset(O, 0, 0x8C);

    *(u8 **)(O + 0x0) = T + (*(u32 *)(T + idx * 4) & ~3u);
    *(u8 **)(O + 0x4) = func_2B24C8(*(u8 **)(O + 0x0), 0, 0);

    q = RELOC_SRC(*(u8 **)(O + 0x4), 0x8);
    *(u8 **)frame = q;
    Res_RelocateOffsets(frame, q, q);
    *(u8 **)(O + 0x34) = *(u8 **)frame;

    q = RELOC_SRC(*(u8 **)(O + 0x4), 0xC);
    *(u8 **)frame = q;
    Res_RelocateOffsets(frame, q, q);
    *(s32 *)(O + 0x40) = *(s32 *)(*(u8 **)frame + 0x10);
    *(s32 *)(O + 0x3C) = *(s32 *)(*(u8 **)frame + 0x10) + 0x40;
    *(s32 *)(O + 0x48) = *(s32 *)(*(u8 **)frame + 0x10) + 0x80;
    *(s32 *)(O + 0x44) = *(s32 *)(*(u8 **)frame + 0x10) + 0xC0;

    q = RELOC_SRC(*(u8 **)(O + 0x4), 0x10);
    *(u8 **)frame = q;
    Res_RelocateOffsets(frame, q, q);
    *(s32 *)(O + 0x4C) = *(s32 *)(*(u8 **)frame + 0x10);
    *(s32 *)(O + 0x50) = *(s32 *)(*(u8 **)frame + 0x10) + 0x40;
    *(s32 *)(O + 0x54) = *(s32 *)(*(u8 **)frame + 0x10) + 0x80;
    *(s32 *)(O + 0x58) = *(s32 *)(*(u8 **)frame + 0x10) + 0xC0;
    *(s32 *)(O + 0x5C) = *(s32 *)(*(u8 **)frame + 0x10) + 0x100;
    *(s32 *)(O + 0x60) = *(s32 *)(*(u8 **)frame + 0x10) + 0x140;
    *(s32 *)(O + 0x64) = *(s32 *)(*(u8 **)frame + 0x10) + 0x180;
    *(s32 *)(O + 0x68) = *(s32 *)(*(u8 **)frame + 0x10) + 0x1C0;
    *(s32 *)(O + 0x6C) = *(s32 *)(*(u8 **)frame + 0x10) + 0x200;

    q = RELOC_SRC(*(u8 **)(O + 0x4), 0x14);
    *(u8 **)frame = q;
    Res_RelocateOffsets(frame, q, q);
    *(s32 *)(O + 0x70) = *(s32 *)(*(u8 **)frame + 0x10);

    func_26E7F0(O + 0xC, RELOC_SRC(*(u8 **)(O + 0x4), 0x4), O + 0x38);
    func_26EAE0(O + 0xC, 0x3C);

    *(u8 **)(O + 0x8) = RELOC_SRC(*(u8 **)(O + 0x4), 0x18);
    *(s32 *)(O + 0x88) = 1;
}
