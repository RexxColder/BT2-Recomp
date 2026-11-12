#include "common.h"

extern u8 *D_0042A590 __attribute__((section(".data")));
extern u8 *D_0042139C __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));

void *func_28BAA8(s32 a0);
void *memset(void *arg0, s32 arg1, u32 arg2);
u8 *func_2B24C8(u8 *a0, u8 *a1, s32 a2);
void Res_RelocateOffsets(u8 *a0, u8 *a1, u8 *a2);
void func_26E7F0(u8 *a0, u8 *a1, u8 *a2);
void func_26EAE0(u8 *a0, s32 a1);
void func_003FF150(void);
void func_003FF340(void);
s32 func_00100ED0(s32 a0, u8 *a1, s32 a2);
s32 func_00100FC8(s32 a0);

#define RELOC_BLOCK(sp0, P, k) \
    do { \
        (sp0) = (P) + (*(u32 *)((P) + (k)) & ~3u); \
        Res_RelocateOffsets((u8 *)&(sp0), (sp0), (sp0)); \
    } while (0)

#define OBJ(o) (*(u8 **)(D_0042A590 + (o)))
#define W(o) (*(s32 *)(D_0042A590 + (o)))
#define SUB(o) (*(u32 *)(OBJ(4) + (o)) & ~3u)

void func_003FFD60(s32 a0) {
    u8 *sp0 = 0;
    u8 *obj;
    u8 *P;
    s32 i = 0;
    u8 *arr;
    u32 w;
    u8 *e;

    obj = (u8 *)func_28BAA8(0x288);
    D_0042A590 = obj;
    memset(obj, 0, 0x288);

    w = *(u32 *)(D_0042139C + a0 * 4);
    *(u8 **)(obj + 0) = D_0042139C + (w & ~3u);
    *(u8 **)(obj + 4) = func_2B24C8(*(u8 **)(obj + 0), 0, 0);
    P = *(u8 **)(obj + 4);

    RELOC_BLOCK(sp0, P, 0x58);
    W(0x11C) = (s32)sp0;
    P = OBJ(4);
    W(0x274) = (s32)(P + SUB(0x54) + 4);
    P = OBJ(4);
    W(0x278) = (s32)(P + SUB(0x78) + 4);
    P = OBJ(4);
    W(0x27C) = (s32)(P + SUB(0x8C) + 4);
    P = OBJ(4);
    W(0x280) = (s32)(P + SUB(0x90) + 4);

    P = OBJ(4); RELOC_BLOCK(sp0, P, 0x14);
    W(0x130) = *(s32 *)(sp0 + 0x10);
    P = OBJ(4); RELOC_BLOCK(sp0, P, 0x3C);
    W(0x16C) = *(s32 *)(sp0 + 0x10);
    P = OBJ(4); RELOC_BLOCK(sp0, P, 0x38);
    W(0x160) = *(s32 *)(sp0 + 0x10);
    W(0x164) = *(s32 *)(sp0 + 0x10) + 0x40;
    W(0x168) = *(s32 *)(sp0 + 0x10) + 0x80;
    P = OBJ(4); RELOC_BLOCK(sp0, P, 0x0C);
    W(0x15C) = *(s32 *)(sp0 + 0x10);
    P = OBJ(4); RELOC_BLOCK(sp0, P, 0x10);
    W(0x124) = *(s32 *)(sp0 + 0x10);
    P = OBJ(4); RELOC_BLOCK(sp0, P, 0x08);
    W(0x134) = *(s32 *)(sp0 + 0x10);
    P = OBJ(4); RELOC_BLOCK(sp0, P, 0x2C);
    W(0x13C) = *(s32 *)(sp0 + 0x10);
    P = OBJ(4); RELOC_BLOCK(sp0, P, 0x44);
    W(0x154) = *(s32 *)(sp0 + 0x10);
    W(0x158) = *(s32 *)(sp0 + 0x10) + 0x40;
    P = OBJ(4); RELOC_BLOCK(sp0, P, 0x68);
    W(0x138) = *(s32 *)(sp0 + 0x10);
    P = OBJ(4); RELOC_BLOCK(sp0, P, 0x6C);
    W(0x12C) = *(s32 *)(sp0 + 0x10);
    P = OBJ(4); RELOC_BLOCK(sp0, P, 0x40);
    W(0x128) = *(s32 *)(sp0 + 0x10);
    P = OBJ(4); RELOC_BLOCK(sp0, P, 0x70);
    W(0x140) = *(s32 *)(sp0 + 0x10);

    obj = D_0042A590;
    func_26E7F0(obj + 0xCC, OBJ(4) + SUB(4), obj + 0x124);
    func_26EAE0(obj + 0xCC, 0x3C);

    P = OBJ(4); RELOC_BLOCK(sp0, P, 0x24);
    W(0x1D8) = *(s32 *)(sp0 + 0x10);
    P = OBJ(4); RELOC_BLOCK(sp0, P, 0x30);
    W(0x1C8) = *(s32 *)(sp0 + 0x10);
    W(0x1CC) = *(s32 *)(sp0 + 0x10) + 0x40;
    P = OBJ(4); RELOC_BLOCK(sp0, P, 0x28);
    W(0x1B4) = *(s32 *)(sp0 + 0x10);
    W(0x1D0) = *(s32 *)(sp0 + 0x10) + 0x40;
    P = OBJ(4); RELOC_BLOCK(sp0, P, 0x20);
    W(0x1C4) = *(s32 *)(sp0 + 0x10);
    P = OBJ(4); RELOC_BLOCK(sp0, P, 0x1C);
    W(0x1B8) = *(s32 *)(sp0 + 0x10);
    W(0x1BC) = *(s32 *)(sp0 + 0x10) + 0x40;
    W(0x1C0) = *(s32 *)(sp0 + 0x10) + 0x80;

    obj = D_0042A590;
    func_26E7F0(obj + 0xF4, OBJ(4) + SUB(0x18), obj + 0x1B4);

    P = OBJ(4); RELOC_BLOCK(sp0, P, 0x5C);
    W(0x170) = *(s32 *)(sp0 + 0x10);

    obj = D_0042A590;
    func_26E7F0(obj + 0xA4, OBJ(4) + SUB(0x64), obj + 0x170);
    func_26EAE0(obj + 0xA4, 0x3C);
    obj = D_0042A590;
    func_26E7F0(obj + 0x2C, OBJ(4) + SUB(0x60), obj + 0x170);
    func_26EAE0(obj + 0x2C, 0x3C);

    P = OBJ(4); RELOC_BLOCK(sp0, P, 0x88);
    W(0x174) = *(s32 *)(sp0 + 0x10);
    P = OBJ(4); RELOC_BLOCK(sp0, P, 0x84);
    W(0x178) = *(s32 *)(sp0 + 0x10);
    W(0x120) = (s32)sp0;
    W(0x1E0) = *(s32 *)(sp0 + 0x10);
    W(0x1F4) = *(s32 *)(sp0 + 0x10) + 0x40;
    W(0x1F8) = *(s32 *)(sp0 + 0x10) + 0x80;
    W(0x1FC) = *(s32 *)(sp0 + 0x10) + 0xC0;
    W(0x200) = *(s32 *)(sp0 + 0x10) + 0x100;
    W(0x204) = *(s32 *)(sp0 + 0x10) + 0x140;
    P = OBJ(4); RELOC_BLOCK(sp0, P, 0x7C);
    W(0x1AC) = *(s32 *)(sp0 + 0x10);
    W(0x1F0) = *(s32 *)(sp0 + 0x10);

    obj = D_0042A590;
    func_26E7F0(obj + 0x54, OBJ(4) + SUB(0x80), obj + 0x174);
    func_26EAE0(obj + 0x54, 0x3C);
    obj = D_0042A590;
    func_26E7F0(obj + 0x7C, OBJ(4) + SUB(0x34), obj + 0x1E0);

    OBJ(0x18) = func_2B24C8(OBJ(4) + SUB(0x50), 0, 0);
    do {
        arr = OBJ(0x18);
        i++;
        w = *(u32 *)(arr + (i - 1) * 4 + 4) & ~3u;
        sp0 = arr + w;
        Res_RelocateOffsets((u8 *)&sp0, sp0, sp0);
    } while (i < 0x86);

    obj = D_0042A590;
    P = *(u8 **)(obj + 4);
    *(u8 **)(obj + 0x24) = P + (*(u32 *)(P + 0x48) & ~3u);
    obj = D_0042A590; P = *(u8 **)(obj + 4);
    *(u8 **)(obj + 0x28) = P + (*(u32 *)(P + 0x4C) & ~3u);
    obj = D_0042A590; P = *(u8 **)(obj + 4);
    *(u8 **)(obj + 0x284) = P + (*(u32 *)(P + 0x74) & ~3u);
    obj = D_0042A590; P = *(u8 **)(obj + 4);
    *(u8 **)(obj + 0x26C) = P + (*(u32 *)(P + 0x98) & ~3u) + 4;
    obj = D_0042A590; P = *(u8 **)(obj + 4);
    *(u8 **)(obj + 0x270) = P + (*(u32 *)(P + 0x94) & ~3u) + 4;

    OBJ(8) = (u8 *)func_28BAA8(0xB000);
    OBJ(0xC) = (u8 *)func_28BAA8(0xB000);
    OBJ(0x10) = (u8 *)func_28BAA8(0x10560);
    OBJ(0x14) = (u8 *)func_28BAA8(0x10560);
    OBJ(0x1C) = (u8 *)func_28BAA8(0xB800);
    OBJ(0x20) = (u8 *)func_28BAA8(0x10560);
    W(0x228) = 1;

#define ENT(idx) (*(u8 **)(D_0042A590 + 0x274) + 56 * (idx))
    if (*(s32 *)(D_3876A4 + 0x5C) != 0) {
        W(0x23C) = *(s32 *)(D_3876A4 + 0x5C);
        W(0x240) = W(0x23C) - 1;
        W(0x244) = W(0x23C) + 2;
        W(0x248) = W(0x23C) + 3;
    } else {
        W(0x23C) = *(s32 *)(ENT(*(s32 *)(D_3876A4 + 0x64)) + 8) - 1;
        W(0x240) = W(0x23C) - 1;
        W(0x244) = *(s32 *)(ENT(*(s32 *)(D_3876A4 + 0x64)) + 8) + 1;
        W(0x248) = *(s32 *)(ENT(*(s32 *)(D_3876A4 + 0x64)) + 8) + 2;
    }

    if (*(u32 *)(D_3876A4 + 0x40) & 0x10) {
        W(0x220) = 0x33;
        if ((*(u32 *)(D_3876A4 + 0x40) & 4) == 0) {
            W(0x208) |= 0x100;
        }
        W(0x23C) = *(s32 *)(D_3876A4 + 0x5C);
        W(0x240) = W(0x23C) - 1;
        W(0x244) = W(0x23C) + 2;
        W(0x248) = W(0x23C) + 3;
        func_003FF150();
    } else {
        W(0x23C) = *(s32 *)(ENT(*(s32 *)(D_3876A4 + 0x64)) + 8) - 1;
        W(0x240) = W(0x23C) - 1;
        W(0x244) = *(s32 *)(ENT(*(s32 *)(D_3876A4 + 0x64)) + 8) + 1;
        W(0x248) = *(s32 *)(ENT(*(s32 *)(D_3876A4 + 0x64)) + 8) + 2;
    }
    func_003FF340();

    if (W(0x208) & 0x200) {
        e = ENT(*(s32 *)(D_3876A4 + 0x64));
        func_00100ED0(*(s32 *)(e + 0x1C) + 0x6A3, OBJ(0x1C), 1);
        func_00100FC8(1);
        while (func_00100FC8(0) == 0) {
        }
        func_2B24C8(OBJ(0x1C), OBJ(0x20), 0);
        sp0 = OBJ(0x20);
        Res_RelocateOffsets((u8 *)&sp0, sp0, sp0);
        W(0x1D4) = *(s32 *)(sp0 + 0x10);
    }
    *(u32 *)(D_3876A4 + 0x40) &= ~0x10u;
    *(u32 *)(D_3876A4 + 0x40) &= ~4u;
}
