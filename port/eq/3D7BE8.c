#include "common.h"

extern u8 *D_3876A4 __attribute__((section(".data")));
extern u8 D_00426230[] __attribute__((section(".data")));
extern u8 D_00426240[] __attribute__((section(".data")));
extern u8 D_00426250[] __attribute__((section(".data")));
extern u8 D_00426260[] __attribute__((section(".data")));
extern u8 D_00426270[] __attribute__((section(".data")));
extern u8 D_00426280[] __attribute__((section(".data")));

s32 func_003D66F8(s32 a0);
void func_26EB20(u8 *a0, s32 a1, s32 a2);
void func_26EAE0(u8 *a0, s32 a1, u8 *a2);
void func_26EB78(u8 *a0, u8 *a1);
void func_297FE0(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0);

/* word lookup: *(s32 *)(Q + (w & ~3) + 0x10) with w = *(u32 *)(Q + idx * 4 + 4) */
#define LOOKUP(q, idx) (*(s32 *)((q) + (*(u32 *)((q) + (idx) * 4 + 4) & ~3u) + 0x10))

/* 0x003D7BE8: per-slot update of the object P (a0). k = P->0x3324 selects a 16-byte record at P + 0xE + 16k with
 * u16 indices into the P->0x18 table (results to P->0x214, P->0x220); a 6-way switch on P->0x3546[k] calls
 * func_26EB78 with one of six D_004262xx blocks, then func_297FE0(2, 3, 0x40, 0x40, 1). */
void func_003D7BE8(u8 *P) {
    u8 *Q;
    u8 *s1;
    s32 k;
    s32 idx;
    s32 r;
    f32 nf;
    u16 st;
    u8 *G;

    *(s32 *)(P + 0x3314) = 1;
    *(s32 *)(P + 0x2BC) = *(s32 *)(P + 0x2BC) | 0x40;
    k = *(s32 *)(P + 0x3324);
    Q = *(u8 **)(P + 0x18);
    idx = *(u16 *)(P + 0xE + k * 16 + 0x3530);
    *(s32 *)(P + 0x214) = LOOKUP(Q, *(u16 *)(P + idx * 32 + 0x333E));
    idx = *(u16 *)(P + 0xE + k * 16 + 0x3532);
    *(s32 *)(P + 0x220) = LOOKUP(Q, *(u16 *)(P + idx * 32 + 0x333E));

    G = D_3876A4;
    if (*(s32 *)(G + 0x90) != 0) {
        r = func_003D66F8(*(u16 *)(P + k * 16 + 0x3548));
        nf = -(f32)r;
        *(f32 *)(P + 0x3330) = nf;
        func_26EB20(P + 0x30, (s32)nf, 0);
        k = *(s32 *)(P + 0x3324);
    }

    s1 = P + 0x58;
    idx = *(u16 *)(P + k * 16 + 0xE + 0x3530);
    *(u16 *)(P + idx * 32 + 0x3330 + 0xC) = *(u16 *)(P + idx * 32 + 0x3330 + 0xC) | 0x8;
    idx = *(u16 *)(P + k * 16 + 0xE + 0x3532);
    *(u16 *)(P + idx * 32 + 0x3330 + 0xC) = *(u16 *)(P + idx * 32 + 0x3330 + 0xC) | 0x8;
    func_26EAE0(s1, 0x3C, P + 0xE + k * 16);

    st = *(u16 *)(P + k * 16 + 0x3546);
    if (st < 6) {
        switch (st) {
        case 0:
            func_26EB78(s1, D_00426230);
            break;
        case 1:
            func_26EB78(s1, D_00426240);
            break;
        case 2:
            func_26EB78(s1, D_00426250);
            break;
        case 3:
            func_26EB78(s1, D_00426260);
            break;
        case 4:
            func_26EB78(s1, D_00426270);
            break;
        case 5:
            func_26EB78(s1, D_00426280);
            break;
        }
    }
    func_297FE0(2, 3, 0x40, 0x40, 1);

    if (*(s32 *)(G + 0x8C) == 0) {
        *(s32 *)(P + 0x19C) = 0;
    } else if (*(s32 *)(G + 0x8C) >= 0 && *(s32 *)(G + 0x8C) < 3) {
        *(s32 *)(P + 0x190) = 0;
    }
}
