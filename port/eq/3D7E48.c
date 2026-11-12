#include "common.h"

extern u8 *D_3876A4 __attribute__((section(".data")));
extern u8 D_004262A8[] __attribute__((section(".data")));
extern u8 D_004262C0[] __attribute__((section(".data")));
extern u8 D_004262D8[] __attribute__((section(".data")));
extern u8 D_004262F0[] __attribute__((section(".data")));
extern u8 D_00426308[] __attribute__((section(".data")));
extern u8 D_00426320[] __attribute__((section(".data")));
extern u8 D_00426338[] __attribute__((section(".data")));
extern u8 D_00426350[] __attribute__((section(".data")));
extern u8 D_00426368[] __attribute__((section(".data")));
extern u8 D_00426380[] __attribute__((section(".data")));
extern u8 D_00426398[] __attribute__((section(".data")));
extern u8 D_004263B0[] __attribute__((section(".data")));

s32 func_003D66F8(s32 a0);
void func_26EB20(u8 *a0, s32 a1, s32 a2);
void func_26EAE0(u8 *a0, s32 a1, u8 *a2);
void func_26EB78(u8 *a0, u8 *a1);
void func_297FE0(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0);

/* word lookup: *(s32 *)(Q + (w & ~3) + 0x10) with w = *(u32 *)(Q + idx * 4 + 4) */
#define LOOKUP(q, idx) (*(s32 *)((q) + (*(u32 *)((q) + (idx) * 4 + 4) & ~3u) + 0x10))

/* 0x003D7E48: sibling of 0x003D7BE8 on P (a0): k = P->0x3324, P->0x22C / 0x238 from the u16 indices, the optional
 * func_003D66F8 offset, two u16 bit sets, func_26EAE0, then a 6-way switch on P->0x354A[k] calling func_26EB78
 * with one of the D_004262xx blocks (P->0x2C8 selects the first or second), then func_297FE0(2, 3, 0x40, 0x40, 1). */
void func_003D7E48(u8 *P) {
    u8 *Q;
    u8 *s1;
    s32 k;
    s32 idx;
    s32 r;
    f32 nf;
    u16 st;
    u8 *G;
    u8 *a;

    *(s32 *)(P + 0x2BC) = *(s32 *)(P + 0x2BC) | 0x20;
    k = *(s32 *)(P + 0x3324);
    Q = *(u8 **)(P + 0x18);
    idx = *(u16 *)(P + 0xE + k * 16 + 0x3530);
    *(s32 *)(P + 0x22C) = LOOKUP(Q, *(u16 *)(P + idx * 32 + 0x333E));
    idx = *(u16 *)(P + 0xE + k * 16 + 0x3532);
    *(s32 *)(P + 0x238) = LOOKUP(Q, *(u16 *)(P + idx * 32 + 0x333E));

    G = D_3876A4;
    if (*(s32 *)(G + 0x90) != 0) {
        r = func_003D66F8(*(u16 *)(P + k * 16 + 0x3548));
        nf = -(f32)r;
        *(f32 *)(P + 0x3330) = nf;
        func_26EB20(P + 0x30, (s32)nf, 0);
        k = *(s32 *)(P + 0x3324);
    }

    s1 = P + 0x80;
    idx = *(u16 *)(P + k * 16 + 0xE + 0x3530);
    *(u16 *)(P + idx * 32 + 0x3330 + 0xC) = *(u16 *)(P + idx * 32 + 0x3330 + 0xC) | 0x8;
    idx = *(u16 *)(P + k * 16 + 0xE + 0x3532);
    *(u16 *)(P + idx * 32 + 0x3330 + 0xC) = *(u16 *)(P + idx * 32 + 0x3330 + 0xC) | 0x8;
    func_26EAE0(s1, 0x3C, P + 0xE + k * 16);

    st = *(u16 *)(P + k * 16 + 0x354A);
    if (st < 6) {
        a = NULL;
        switch (st) {
        case 0:
            a = (*(s32 *)(P + 0x2C8) != 0) ? D_004262A8 : D_004262C0;
            break;
        case 1:
            a = (*(s32 *)(P + 0x2C8) != 0) ? D_004262D8 : D_004262F0;
            break;
        case 2:
            a = (*(s32 *)(P + 0x2C8) != 0) ? D_00426308 : D_00426320;
            break;
        case 3:
            a = (*(s32 *)(P + 0x2C8) != 0) ? D_00426338 : D_00426350;
            break;
        case 4:
            a = (*(s32 *)(P + 0x2C8) != 0) ? D_00426368 : D_00426380;
            break;
        case 5:
            a = (*(s32 *)(P + 0x2C8) != 0) ? D_00426398 : D_004263B0;
            break;
        }
        func_26EB78(s1, a);
    }
    func_297FE0(2, 3, 0x40, 0x40, 1);
}
