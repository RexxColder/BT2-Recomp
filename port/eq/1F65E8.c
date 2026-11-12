#include "common.h"

extern u8 *D_003876A0;

void *func_00211288(s32 arg0);
void func_003126C8(void *a0, void *a1);
void func_001F5958(void *a0);
void *func_00202DD8(void *a0, s32 a1);
s32 func_00202FC8(void *a0, s32 a1, s32 a2, s32 a3);
void *func_00202DA0(void *a0, s32 a1);
void func_00203040(void *a0, s32 a1);
void *func_00202DC0(void *a0);
s32 func_0023F960(void *a0);
s32 func_0023F9B0(void *a0);
s32 func_0023F520(void *a0);
void func_002113C0(void *a0, s32 a1, s32 a2, s32 a3);

void func_001F65E8(s32 arg0) {
    u8 *s6;
    u8 *s0;
    u8 *s5;
    u8 *v0r;
    u8 *p;
    s32 a2;
    s32 s4;
    s32 s7;
    s32 fp;
    s32 s2;
    s32 sp0;
    s32 sp4;
    s32 sp8;
    s32 spC;
    s32 sp18;
    s32 sp1C;
    s64 sp10;
    s32 r;
    s32 t;

    s6 = (u8 *)func_00211288(arg0);
    s0 = s6 + 0x510;
    func_003126C8((u8 *)*(s32 *)(s6 + 0x1530) + 0x9A0, s0);
    func_003126C8((u8 *)*(s32 *)(s6 + 0x1530) + 0x9C0, s0);
    func_003126C8((u8 *)*(s32 *)(s6 + 0x1530) + 0x9B0, s6 + 0x520);
    func_001F5958(s6);
    s5 = (u8 *)func_00202DD8(s6, *(s32 *)(s6 + 0x990));
    v0r = (u8 *)func_00202DD8(s6, *(s32 *)(s6 + 0x994));

    a2 = (D_003876A0[*(s32 *)(s6 + 0x1534) * 0x1D0 + 0x2A4] == 0) ? 0x14 : 0x28;

    s4 = *(s32 *)(s5 + 0x1C) + *(s32 *)(v0r + 0x1C);
    s4 = (a2 < s4) ? a2 : s4;
    s7 = *(s32 *)(s5 + 0x24) + *(s32 *)(v0r + 0x24);
    fp = *(s32 *)(s5 + 0x20) + *(s32 *)(v0r + 0x20);
    sp0 = *(s32 *)(s5 + 0xC) + *(s32 *)(v0r + 0xC);
    sp4 = *(s32 *)(s5 + 0x10) + *(s32 *)(v0r + 0x10);
    sp8 = *(s32 *)(s5 + 0x14) + *(s32 *)(v0r + 0x14);
    spC = *(s32 *)(s5 + 0x18) + *(s32 *)(v0r + 0x18);
    sp10 = *(s64 *)(s5 + 0x28) | *(s64 *)(v0r + 0x28);
    s2 = *(s32 *)(s5 + 0x44) + *(s32 *)(v0r + 0x44);
    sp18 = *(s32 *)(s5 + 0x38) + *(s32 *)(v0r + 0x38);
    sp1C = *(s32 *)(s5 + 0x3C) + *(s32 *)(v0r + 0x3C);

    /* min(a2, x) on the sums stored in the frame and on s7/fp */
    sp0 = (a2 < sp0) ? a2 : sp0;
    sp4 = (a2 < sp4) ? a2 : sp4;
    sp8 = (a2 < sp8) ? a2 : sp8;
    spC = (a2 < spC) ? a2 : spC;
    fp = (a2 < fp) ? a2 : fp;
    s7 = (a2 < s7) ? a2 : s7;

    r = func_00202FC8(s6, *(s32 *)(s6 + 0x990), a2, sp1C);
    if (r >= 0) {
        p = (u8 *)func_00202DA0(s6, r);
        *(s32 *)p = *(s32 *)((u8 *)*(s32 *)(s6 + 0x1530) + 4);
        /* second call passes a2 = obj+0x1530 as a third argument */
        p = (u8 *)((void *(*)(void *, s32, s32))func_00202DA0)(s6, r, *(s32 *)(s6 + 0x1530));
        *(s32 *)(p + 4) = *(s32 *)((u8 *)*(s32 *)(s6 + 0x1530) + 8);
    }

    func_00203040(s6, *(s32 *)(s6 + 0x994));
    s5 = (u8 *)func_00202DC0(s6);

    *(s32 *)(s5 + 0xC) = sp0;
    *(s32 *)(s5 + 0x10) = sp4;
    *(s32 *)(s5 + 0x14) = sp8;
    *(s32 *)(s5 + 0x18) = spC;
    *(s32 *)(s5 + 0x1C) = s4;
    *(s32 *)(s5 + 0x20) = fp;
    *(s32 *)(s5 + 0x24) = s7;
    *(s64 *)(s5 + 0x28) = sp10;
    *(s32 *)(s5 + 0x38) = sp18;
    *(s32 *)(s5 + 0x3C) = sp1C;
    t = func_0023F960(s6);
    *(s32 *)(s5 + 0x44) = s2;
    *(s32 *)(s5 + 0x40) = t;
    *(s32 *)(s5 + 0x48) = 0x186A0;
    t = func_0023F9B0(s6);
    *(s32 *)(s5 + 0x50) = (s32)((u32)t * 0x186A0u);

    if (func_0023F520(s6) & 0x2) {
        *(s32 *)(s5 + 0x38) = *(s32 *)(s5 + 0x38) + 0x2710;
    }
    if (func_0023F520(s6) & 0x4) {
        *(s32 *)(s5 + 0x38) = *(s32 *)(s5 + 0x38) + 0x4E20;
    }
    if (func_0023F520(s6) & 0x8) {
        *(s32 *)(s5 + 0x44) = *(s32 *)(s5 + 0x48);
    }
    if (func_0023F520(s6) & 0x10) {
        s5[0x60] = 0;
    }
    if (func_0023F520(s6) & 0x20) {
        *(s32 *)(s5 + 0x54) = 0x7530;
        *(s32 *)(s5 + 0x44) = *(s32 *)(s5 + 0x48);
        func_002113C0(s6, 0, 0x800, 1);
    }

    if (*(s32 *)(s5 + 0x3C) < *(s32 *)(s5 + 0x38)) {
        *(s32 *)(s5 + 0x38) = *(s32 *)(s5 + 0x3C);
    }
    if (*(s32 *)(s5 + 0x48) < *(s32 *)(s5 + 0x44)) {
        *(s32 *)(s5 + 0x44) = *(s32 *)(s5 + 0x48);
    }
    if (*(s32 *)(s5 + 0x50) < *(s32 *)(s5 + 0x4C)) {
        *(s32 *)(s5 + 0x4C) = *(s32 *)(s5 + 0x50);
    }
}
