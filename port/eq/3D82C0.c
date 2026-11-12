#include "common.h"

void *memset(void *, int, unsigned int);
void func_100ED0();
s32 func_100FC8(s32 arg0);
u8 *func_2B24C8(s32 arg0, s32 arg1, s32 arg2);
void Res_RelocateOffsets(void *arg0, u8 *arg1, u8 *arg2);

/* 0x003D82C0: P = arg0. sp[0..1] = 0 (memset 8), k = P->0x3324, q = P + 0xE + 16k, A = u16 at q+0x3530, B = u16 at
 * q+0x3532; flagA = u16 at P+32A+0x333E, vB = u16 at P+32B+0x333E. sp[0] = flagA, sp[1] = vB;
 * func_100ED0(flagA+0x56B, P->8, 1, flagA); func_100ED0(vB+0x56B, P->0xC, 0); func_100FC8(1);
 * do {} while (func_100FC8(0) == 0); func_2B24C8(P->8, P->0x10, 0); func_2B24C8(P->0xC, P->0x14, 0);
 * t = P->0x10; sp10 = t; Res_RelocateOffsets(&sp10, t, t); P->0x288 = *(sp10 + 0x10) (before the next step);
 * sp10 = P->0x14; Res_RelocateOffsets(&sp10, P->0x14, P->0x14); P->0x28C = *(sp10 + 0x10). */
void func_003D82C0(u8 *arg0) {
    s32 sp[2];
    u8 *sp10;
    u8 *q;
    s32 ia;
    s32 ib;
    s32 flagA;
    s32 vB;
    s32 k;
    u8 *a3p;
    s32 v1;

    memset(sp, 0, 8);

    k = *(s32 *)(arg0 + 0x3324);
    q = arg0 + 0xE + k * 16;
    ia = *(u16 *)(q + 0x3530);
    ib = *(u16 *)(q + 0x3532);
    flagA = *(u16 *)(arg0 + (ia << 5) + 0x333E);
    vB = *(u16 *)(arg0 + (ib << 5) + 0x333E);

    sp[0] = flagA;
    sp[1] = vB;
    func_100ED0(flagA + 0x56B, *(s32 *)(arg0 + 8), 1, flagA);
    func_100ED0(sp[1] + 0x56B, *(s32 *)(arg0 + 0xC), 0);
    func_100FC8(1);
    while (func_100FC8(0) == 0) {
    }
    func_2B24C8(*(s32 *)(arg0 + 8), *(s32 *)(arg0 + 0x10), 0);
    func_2B24C8(*(s32 *)(arg0 + 0xC), *(s32 *)(arg0 + 0x14), 0);

    sp10 = *(u8 **)(arg0 + 0x10);
    Res_RelocateOffsets(&sp10, sp10, sp10);

    a3p = *(u8 **)(arg0 + 0x14);
    v1 = *(s32 *)(sp10 + 0x10);
    sp10 = a3p;
    *(s32 *)(arg0 + 0x288) = v1;
    Res_RelocateOffsets(&sp10, a3p, a3p);

    *(s32 *)(arg0 + 0x28C) = *(s32 *)(sp10 + 0x10);
}
