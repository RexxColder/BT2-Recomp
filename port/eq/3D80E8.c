#include "common.h"

extern u8 *D_3876A4 __attribute__((section(".data")));

void *memset(void *s, s32 c, u32 n);
void func_100ED0();
s32 func_100FC8(s32 a0);
void func_2B24C8(u8 *a0, u8 *a1, s32 a2);
void Res_RelocateOffsets(u8 **a0, u8 *a1, u8 *a2);

/* 0x003D80E8: state machine on S->0x3314 (S = arg0). 1: idx = S->0x3324, two u16 table lookups in S+0xE+16*idx
 * (+0x3530 / +0x3532) index S+0x333E words; func_100ED0(X+0x56B, S->8, 1, X), func_100ED0(Y+0x56B, S->0xC, 0),
 * func_100FC8(1), state 2. 2: func_100FC8(0) != 0 -> state 3. 3: func_2B24C8 on (S->8, S->0x10) and (S->0xC, S->0x14),
 * the slot indices s2 / s3 from P->0x8C (0 -> 7/8, 0..2 -> 4/5, else 0/0), Res_RelocateOffsets on S->0x10 and S->0x14
 * with the pointer words stored at S+4+0x240+4*s2 and S+4+0x240+4*s3, state 0, S->0x2BC |= 0x200. */
void func_003D80E8(u8 *arg0) {
    u8 sp[0x20];
    u8 *slot;
    u8 *base;
    s32 st;
    s32 s2;
    s32 s3;
    s32 v;
    s32 idx;
    u8 *a3;
    u16 ua;
    u16 ub;
    s32 x;
    s32 y;

    memset(sp, 0, 8);
    st = *(s32 *)(arg0 + 0x3314);
    if (st == 2) {
        if (func_100FC8(0) != 0) {
            *(s32 *)(arg0 + 0x3314) = 3;
        }
    } else if (st == 1) {
        idx = *(s32 *)(arg0 + 0x3324);
        a3 = arg0 + 0xE + (idx << 4);
        ua = *(u16 *)(a3 + 0x3530);
        ub = *(u16 *)(a3 + 0x3532);
        x = *(u16 *)(arg0 + (ua << 5) + 0x333E);
        y = *(u16 *)(arg0 + (ub << 5) + 0x333E);
        func_100ED0(x + 0x56B, *(s32 *)(arg0 + 0x8), 1, x);
        func_100ED0(y + 0x56B, *(s32 *)(arg0 + 0xC), 0);
        func_100FC8(1);
        *(s32 *)(arg0 + 0x3314) = 2;
    } else if (st == 3) {
        s2 = 0;
        s3 = 0;
        func_2B24C8(*(u8 **)(arg0 + 0x8), *(u8 **)(arg0 + 0x10), 0);
        func_2B24C8(*(u8 **)(arg0 + 0xC), *(u8 **)(arg0 + 0x14), 0);
        v = *(s32 *)(D_3876A4 + 0x8C);
        if (v == 0) {
            s2 = 7;
            s3 = 8;
        } else if (v >= 0 && v < 3) {
            s2 = 4;
            s3 = 5;
        }
        base = arg0 + 0x4;
        slot = *(u8 **)(arg0 + 0x10);
        Res_RelocateOffsets(&slot, *(u8 **)(arg0 + 0x10), *(u8 **)(arg0 + 0x10));
        *(s32 *)(base + s2 * 4 + 0x240) = *(s32 *)(slot + 0x10);
        slot = *(u8 **)(arg0 + 0x14);
        Res_RelocateOffsets(&slot, *(u8 **)(arg0 + 0x14), *(u8 **)(arg0 + 0x14));
        *(s32 *)(base + s3 * 4 + 0x240) = *(s32 *)(slot + 0x10);
        *(s32 *)(arg0 + 0x3314) = 0;
        *(s32 *)(arg0 + 0x2BC) = *(s32 *)(arg0 + 0x2BC) | 0x200;
    }
}
