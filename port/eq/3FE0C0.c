#include "common.h"

extern u8 *D_0042A58C __attribute__((section(".data")));
extern u8 *D_0042139C __attribute__((section(".data")));
extern u8 D_0042B860[] __attribute__((section(".data")));
extern u8 D_0042B890[] __attribute__((section(".data")));
extern u8 *D_387F2C __attribute__((section(".data")));

u8 *func_28BAA8(s32 a0);
u8 *func_2B24C8(u8 *a0, u8 *a1, s32 a2);
void Res_RelocateOffsets(u8 *a0, u8 *a1, u8 *a2);
void func_26E7F0(u8 *a0, u8 *a1, u8 *a2);
void func_26EAE0(u8 *a0, s32 a1);
void func_29BB88(u8 *a0, u8 *a1);
void func_28A0B8(u8 *a0, u8 *a1, s32 a2, s32 a3, s32 a4);
void McCard_Checksum(u8 *a0, s32 a1, s32 a2);

/* 0x003FE0C0: builds the 0x480-byte object O = D_0042A58C for table entry idx (table D_0042139C, words rebased by
 * the relocation of O->4 + (word & ~3)). Copies 0x2D bytes of D_0042B860 to O + 0x378, then a checksum on D_387F2C. */
void func_003FE0C0(s32 idx) {
    u8 *O;
    u8 *T;
    u8 *q;
    u8 *x;
    u8 frame[0x10];

    *(s32 *)frame = 0;
    T = D_0042139C;
    O = func_28BAA8(0x480);
    D_0042A58C = O;
    memset(O, 0, 0x480);

    *(u8 **)(O + 0x0) = T + (*(u32 *)(T + idx * 4) & ~3u);
    *(u8 **)(O + 0x4) = func_2B24C8(*(u8 **)(O + 0x0), 0, 0);

    x = *(u8 **)(O + 0x4);
    q = x + (*(u32 *)(x + 0x3C) & ~3u);
    *(u8 **)frame = q;
    Res_RelocateOffsets(frame, q, q);
    *(u8 **)(O + 0x34) = *(u8 **)frame;

    x = *(u8 **)(O + 0x4);
    q = x + (*(u32 *)(x + 0x44) & ~3u);
    *(u8 **)frame = q;
    Res_RelocateOffsets(frame, q, q);
    *(s32 *)(O + 0x3C) = *(s32 *)(*(u8 **)frame + 0x10);
    *(s32 *)(O + 0x38) = *(s32 *)(*(u8 **)frame + 0x10) + 0x40;

    x = *(u8 **)(O + 0x4);
    q = x + (*(u32 *)(x + 0x48) & ~3u);
    *(u8 **)frame = q;
    Res_RelocateOffsets(frame, q, q);
    *(s32 *)(O + 0x40) = *(s32 *)(*(u8 **)frame + 0x10);

    x = *(u8 **)(O + 0x4);
    func_26E7F0(O + 0xC, x + (*(u32 *)(x + 0x40) & ~3u), O + 0x38);
    func_26EAE0(O + 0xC, 0x3C);

    x = *(u8 **)(O + 0x4);
    *(u8 **)(O + 0x8) = x + (*(u32 *)(x + 0x78) & ~3u);
    x = *(u8 **)(O + 0x4);
    func_29BB88(x + (*(u32 *)(x + 0x58) & ~3u), *(u8 **)(O + 0x8));

    *(s32 *)(O + 0x50) = 8;
    *(s32 *)(O + 0x58) = -1;
    x = *(u8 **)(O + 0x4);
    *(u8 **)(O + 0x60) = x + (*(u32 *)(x + 0x7C) & ~3u);
    *(s32 *)(O + 0x6C) = 0xD74E;
    memcpy(O + 0x378, D_0042B860, 0x2D);
    *(s32 *)(O + 0x47C) = 0x18;
    func_28A0B8(O + 0x60, D_0042B890, -1, -1, 1); /* a5 (t1) = last copied word, not expressed */
    McCard_Checksum(D_387F2C, 0x4000, 1);
}
