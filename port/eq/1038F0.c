#include "common.h"

s32 func_00100FC8(s32 arg0);
s32 func_00211288(s32 arg0);
s32 func_00211310(s32 a0, s32 a1, s32 a2);
void func_002113C0(s32 a0, s32 a1, s32 a2, s32 a3);
s32 func_0025E068(void);
void func_00261F38(s32 a0, s32 a1, s32 a2, s32 a3, s32 t0, s32 t1);
s32 func_002622F0(void);
void func_00262330(s32 a0, s32 a1, s32 a2);
void func_00206E60(s32 a0, s32 a1, s32 a2);
extern u8 *D_003876A0;

s32 func_001038F0(u8 *arg0) {
    s32 st;
    s32 v0;
    s32 t;

    st = *(s32 *)arg0;
    if (st == 1) {
        v0 = func_00100FC8(0);
        if (v0 == 0) {
            return 0;
        }
        func_002113C0(func_00211288(0), 0xC, 0x2000, 1);
        func_002113C0(func_00211288(1), 0xC, 0x2000, 1);
        *(s32 *)arg0 += 1;
        goto block11;
    }
    if (st < 2) {
        if (st != 0) {
            return 1;
        }
        t = func_002622F0();
        *(s32 *)(arg0 + 4) = t;
        if (t == -1) {
            return 1;
        }
        func_00261F38(1, 0, (u16)*(s32 *)(arg0 + 4), *(s32 *)(arg0 + 0xC), -1, -1);
        func_00100FC8(1);
        *(s64 *)(D_003876A0 + 0x4D8) = *(s64 *)(D_003876A0 + 0x4D8) | (s64)0x1000;
        *(s32 *)arg0 += 1;
        return 0;
    }
    if (st != 2) {
        return 1;
    }
block11:
    v0 = 0;
    if (!(*(s64 *)(D_003876A0 + 0x4D8) & (s64)0x100)) {
        v0 = func_00211310(func_00211288(*(s32 *)(arg0 + 0x18)), 0xC, 0x4000);
        if (v0 != 0) {
            t = func_0025E068();
            func_00262330(1, t & 0xFFFF, (u16)*(s32 *)(arg0 + 4));
            func_00206E60(func_00211288(*(s32 *)(arg0 + 0x18)), t, *(s32 *)(arg0 + 4));
            v0 = 1;
            *(s64 *)(D_003876A0 + 0x4D8) = *(s64 *)(D_003876A0 + 0x4D8) & (s64)-0x1001;
        }
    }
    return v0;
}
