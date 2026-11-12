#include "common.h"

extern u8 *D_003876A0;

void func_00277E28(void *arg0);
s32 func_00211288(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_002621B8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 t0);
s32 func_00100ED0(s32 arg0, s32 arg1, s32 arg2);
void *func_00103168(s32 arg0);
s32 func_00100FC8(s32 arg0);
void func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_00262280(void);
void func_00262330(s32 arg0, s32 arg1, s32 arg2);
void func_001F65E8(s32 arg0);
void func_0011E828(s32 arg0);
void func_00148888(s32 arg0);
void func_00298240(s32 arg0, void *arg1);
void func_002980A8(s32 arg0, s32 arg1);
void Res_RelocateOffsets(void *arg0, s32 arg1, s32 arg2);
void func_00277E50(void *arg0);

s32 func_00103650(u8 *arg0) {
    u8 *p;
    u8 *s0;
    s32 st;
    s32 r;
    s32 v;
    s32 sp0;

    p = arg0;
    st = *(s32 *)p;
    if (st == 1) {
        goto L760;
    }
    if (st == 0) {
        goto L6A0;
    }
    if (st == 2) {
        goto L798;
    }
    return 1;

L6A0:
    func_00277E28(p);
    r = func_00211288(*(s32 *)(p + 0x18));
    if (func_00211310(r, 0xC, 0x100) == 0) {
        return 0;
    }
    s0 = D_003876A0;
    func_002621B8(1, *(u16 *)(p + 0x18), *(s32 *)(p + 4), *(s32 *)(p + 8), *(s32 *)(p + 0xC));
    *(s32 *)(s0 + 0xC) = func_00100ED0(*(s32 *)(p + 0x10), *(s32 *)(s0 + 0xC), 0);
    v = *(s32 *)(p + 0x14);
    if (v >= 0) {
        s0 = func_00103168(*(s32 *)(p + 0x18));
        if (s0 == NULL) {
            *(s32 *)(p + 0x14) = -1;
        } else {
            *(s32 *)(s0 + 0x54) = func_00100ED0(*(s32 *)(p + 0x14), *(s32 *)(s0 + 0x54), 0);
        }
    }
    func_00100FC8(1);
    *(u64 *)(D_003876A0 + 0x4D8) = *(u64 *)(D_003876A0 + 0x4D8) | 0x800;
    *(s32 *)p = *(s32 *)p + 1;
    return 0;

L760:
    if (func_00100FC8(0) == 0) {
        return 0;
    }
    r = func_00211288(*(s32 *)(p + 0x18));
    func_002113C0(r, 0xC, 0x200, 1);
    *(s32 *)p = *(s32 *)p + 1;

L798:
    if ((*(u64 *)(D_003876A0 + 0x4D8) & 0x100) != 0) {
        return 0;
    }
    r = func_00211288(*(s32 *)(p + 0x18));
    if (func_00211310(r, 0xC, 0x400) == 0) {
        return 0;
    }
    func_00262280();
    s0 = D_003876A0;
    func_00262330(0, *(u16 *)(p + 0x18), *(u16 *)(p + 0x18));
    func_001F65E8(*(s32 *)(p + 0x18));
    func_0011E828(*(s32 *)(p + 0x18));
    func_00148888(*(s32 *)(p + 0x18));
    if (*(s32 *)(p + 0x18) != 0) {
        *(u64 *)(D_003876A0 + 0xA8) = 0;
        func_00298240(*(s32 *)(s0 + 0xC), D_003876A0 + 0xA8);
    } else {
        *(u64 *)(D_003876A0 + 0xA0) = 0;
        func_00298240(*(s32 *)(s0 + 0xC), D_003876A0 + 0xA0);
    }
    func_002980A8(*(s32 *)(p + 0x18) + 3, *(s32 *)(s0 + 0xC));

    v = *(s32 *)(p + 0x14);
    if (v >= 0) {
        s0 = func_00103168(*(s32 *)(p + 0x18));
        if (s0 != NULL) {
            v = *(s32 *)(s0 + 0x54);
            sp0 = v;
            Res_RelocateOffsets(&sp0, v, v);
            *(s32 *)(s0 + 0x4C) = *(s32 *)(s0 + 0x54);
        }
    }

    *(u64 *)(D_003876A0 + 0x4D8) = *(u64 *)(D_003876A0 + 0x4D8) & (s64)-0x801;
    func_00277E50(D_003876A0);
    if (*(s32 *)(p + 0x18) != 0) {
        if (*(s32 *)(p + 0x18) == 1) {
            *(s32 *)(D_003876A0 + 0x4E0) = *(s32 *)(D_003876A0 + 0x4E0) & -3;
        }
    } else {
        *(s32 *)(D_003876A0 + 0x4E0) = *(s32 *)(D_003876A0 + 0x4E0) & -2;
    }
    return 1;
}
