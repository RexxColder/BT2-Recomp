#include "common.h"

s32 func_00100ED0(s32 arg0, s32 arg1, s32 arg2);
s32 func_00100FC8(s32 arg0);
void func_00148888(s32 arg0);
void func_0011E828(s32 arg0);
void func_001F63D8(s32 arg0);
s32 func_00211288(s32 arg0);
s32 func_00211310(s32 arg0, s32 arg1, s32 arg2);
s32 func_002113C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void func_002621B8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
void func_00262280(void);
void func_00262330(s32 arg0, s32 arg1, s32 arg2);
void func_002980A8(s32 arg0, s32 arg1);
s32 func_00298240(s32 arg0, s32 arg1);
extern u8 *D_003876A0;

s32 func_00103A90(s32 arg0) {
    u8 *self;
    u8 *d;
    u8 *s1;
    s32 st;
    s32 v;
    s32 idx;
    u16 a1;

    self = (u8 *)arg0;
    st = *(s32 *)self;

    if (st == 0) {
        func_002621B8(1, *(u16 *)(self + 0x18), *(s32 *)(self + 4), *(s32 *)(self + 8), *(s32 *)(self + 0xC));
        s1 = D_003876A0;
        if (*(s32 *)(self + 0x10) >= 0) {
            *(s32 *)(s1 + 0xC) = func_00100ED0(*(s32 *)(self + 0x10), *(s32 *)(s1 + 0xC), 0);
        }
        func_00100FC8(1);
        *(s64 *)(D_003876A0 + 0x4D8) = *(s64 *)(D_003876A0 + 0x4D8) | 0x800;
        *(s32 *)self = *(s32 *)self + 1;
        return 0;
    }
    if (st == 1) {
        if (func_00100FC8(0) == 0) {
            return 0;
        }
        func_002113C0(func_00211288(*(s32 *)(self + 0x18)), 0xC, 0x10000, 1);
        *(s32 *)self = *(s32 *)self + 1;
    } else if (st != 2) {
        return 1;
    }

    /* L3B80 */
    d = D_003876A0;
    if ((*(s64 *)(d + 0x4D8) & 0x100) != 0) {
        return 0;
    }
    v = func_00211310(func_00211288(*(s32 *)(self + 0x18)), 0xC, 0x20000);
    if (v == 0) {
        return 0;
    }
    s1 = D_003876A0;
    func_00262280();
    a1 = *(u16 *)(self + 0x18);
    func_00262330(0, a1, a1);
    func_001F63D8(*(s32 *)(self + 0x18));
    func_0011E828(*(s32 *)(self + 0x18));
    if (*(s32 *)(self + 0xC) >= 0) {
        func_00148888(*(s32 *)(self + 0x18));
    }
    if (*(s32 *)(self + 0x10) >= 0) {
        if (*(s32 *)(self + 0x18) == 0) {
            *(s64 *)(D_003876A0 + 0xA0) = 0;
            func_00298240(*(s32 *)(s1 + 0xC), (s32)(D_003876A0 + 0xA0));
        } else {
            *(s64 *)(D_003876A0 + 0xA8) = 0;
            func_00298240(*(s32 *)(s1 + 0xC), (s32)(D_003876A0 + 0xA8));
        }
        func_002980A8(*(s32 *)(self + 0x18) + 3, *(s32 *)(s1 + 0xC));
    }
    *(s64 *)(D_003876A0 + 0x4D8) = *(s64 *)(D_003876A0 + 0x4D8) & ~(s64)0x800;
    idx = *(s32 *)(self + 0x18);
    if (idx == 0) {
        *(s32 *)(D_003876A0 + 0x4E0) = *(s32 *)(D_003876A0 + 0x4E0) & -2;
    } else if (idx == 1) {
        *(s32 *)(D_003876A0 + 0x4E0) = *(s32 *)(D_003876A0 + 0x4E0) & -3;
    }
    return 1;
}
