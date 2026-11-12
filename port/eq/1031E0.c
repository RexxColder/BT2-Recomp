#include "common.h"

extern u8 *D_003876A0;

void func_00277E28(void);
void func_00277E50(void);
void func_002621B8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_00100ED0(s32 arg0, s32 arg1, s32 arg2);
s32 func_00100FC8(s32 arg0);
u8 *func_00103168(s32 arg0);
s32 func_00211288(s32 arg0);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
void func_00262280(void);
void func_00262330(s32 arg0, s32 arg1, s32 arg2);
void func_001F5FD8(s32 arg0);
void func_0011E828(s32 arg0);
void func_00148888(s32 arg0);
s32 func_00298240(s32 arg0, s32 arg1);
void func_002980A8(s32 arg0, s32 arg1);
void Res_RelocateOffsets(s32 arg0, s32 arg1, s32 arg2);

s32 func_001031E0(u8 *arg0) {
    s32 sp[4];
    s32 st;
    s32 a0;
    s32 v;
    u8 *s0;
    u8 *r;

    st = *(s32 *)arg0;
    if (st == 0) {
        func_00277E28();
        s0 = D_003876A0;
        func_002621B8(1, *(u16 *)(arg0 + 0x18), *(s32 *)(arg0 + 4), *(s32 *)(arg0 + 8), *(s32 *)(arg0 + 0xC));
        a0 = *(s32 *)(arg0 + 0x10);
        if (a0 >= 0) {
            *(s32 *)(s0 + 0xC) = func_00100ED0(a0, *(s32 *)(s0 + 0xC), 0);
        }
        if (*(s32 *)(arg0 + 0x14) >= 0) {
            r = func_00103168(*(s32 *)(arg0 + 0x18));
            if (r != NULL) {
                *(s32 *)(r + 0x54) = func_00100ED0(*(s32 *)(arg0 + 0x14), *(s32 *)(r + 0x54), 0);
            } else {
                *(s32 *)(arg0 + 0x14) = -1;
            }
        }
        func_00100FC8(1);
        *(s64 *)(D_003876A0 + 0x4D8) = *(s64 *)(D_003876A0 + 0x4D8) | 0x800;
        *(s32 *)arg0 = *(s32 *)arg0 + 1;
        return 0;
    }

    if (st == 1) {
        if (func_00100FC8(0) == 0) {
            return 0;
        }
        func_002113C0(func_00211288(*(s32 *)(arg0 + 0x18)), 0xC, 4, 1);
        *(s32 *)arg0 = *(s32 *)arg0 + 1;
    } else if (st != 2) {
        return 1;
    }

    /* state 2: */
    if ((*(s64 *)(D_003876A0 + 0x4D8) & 0x100) != 0) {
        return 0;
    }
    if (func_00211310(func_00211288(*(s32 *)(arg0 + 0x18)), 0xC, 8) == 0) {
        return 0;
    }
    s0 = D_003876A0;
    func_00262280();
    func_00262330(0, *(u16 *)(arg0 + 0x18), *(u16 *)(arg0 + 0x18));
    func_001F5FD8(*(s32 *)(arg0 + 0x18));
    func_0011E828(*(s32 *)(arg0 + 0x18));
    if (*(s32 *)(arg0 + 0xC) >= 0) {
        func_00148888(*(s32 *)(arg0 + 0x18));
    }
    if (*(s32 *)(arg0 + 0x10) >= 0) {
        if (*(s32 *)(arg0 + 0x18) == 0) {
            *(s64 *)(D_003876A0 + 0xA0) = 0;
            func_00298240(*(s32 *)(s0 + 0xC), (s32)(D_003876A0 + 0xA0));
        } else {
            *(s64 *)(D_003876A0 + 0xA8) = 0;
            func_00298240(*(s32 *)(s0 + 0xC), (s32)(D_003876A0 + 0xA8));
        }
        func_002980A8(*(s32 *)(arg0 + 0x18) + 3, *(s32 *)(s0 + 0xC));
    }
    if (*(s32 *)(arg0 + 0x14) >= 0) {
        r = func_00103168(*(s32 *)(arg0 + 0x18));
        if (r != NULL) {
            v = *(s32 *)(r + 0x54);
            sp[0] = v;
            Res_RelocateOffsets((s32)sp, v, v);
            *(s32 *)(r + 0x4C) = *(s32 *)(r + 0x54);
        }
    }
    *(s64 *)(D_003876A0 + 0x4D8) = *(s64 *)(D_003876A0 + 0x4D8) & -0x801;
    func_00277E50();
    if (*(s32 *)(arg0 + 0x18) == 0) {
        *(s32 *)(D_003876A0 + 0x4E0) = *(s32 *)(D_003876A0 + 0x4E0) & -2;
    } else if (*(s32 *)(arg0 + 0x18) == 1) {
        *(s32 *)(D_003876A0 + 0x4E0) = *(s32 *)(D_003876A0 + 0x4E0) & -3;
    }
    return 1;
}
