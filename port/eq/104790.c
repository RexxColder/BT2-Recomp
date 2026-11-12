#include "common.h"

s32 func_00100ED0(s32 arg0, s32 arg1, s32 arg2);
s32 func_00100FC8(s32 arg0);
void func_00261F38(s32 arg0, s32 arg1, u16 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_00262330(s32 arg0, u16 arg1, u16 arg2);
void func_002980A8(s32 arg0, s32 arg1);
s32 func_002980C0(void);
void func_00298240(s32 arg0, s32 arg1);
extern u8 *D_003876A0;

s32 func_00104790(void *arg0) {
    u8 *p;
    u8 *d;
    s32 st;

    p = (u8 *)arg0;
    st = *(s32 *)p;
    if (st == 1) {
        if (func_00100FC8(0) == 0) {
            return 0;
        }
        *(s32 *)p = *(s32 *)p + 1;
        goto case2;
    }
    if (st < 2) {
        if (st != 0) {
            return 1;
        }
        d = D_003876A0;
        func_00261F38(1, 1, *(u16 *)(p + 0x18), *(s32 *)(p + 4), *(s32 *)(p + 8), *(s32 *)(p + 0xC));
        *(s32 *)(d + 0xC) = func_00100ED0(*(s32 *)(p + 0x10), *(s32 *)(d + 0xC), 0);
        func_00100FC8(1);
        *(s32 *)p = *(s32 *)p + 1;
        return 0;
    }
    if (st == 2) {
        goto case2;
    }
    if (st == 3) {
        if (func_002980C0() != 0) {
            return 1;
        }
        return 0;
    }
    return 1;

case2:
    d = D_003876A0;
    func_00262330(0, *(u16 *)(p + 0x18), *(u16 *)(p + 0x18));
    if (*(s32 *)(p + 0x18) == 0) {
        *(s64 *)(d + 0xA0) = 0;
        func_00298240(*(s32 *)(d + 0xC), (s32)(d + 0xA0));
    } else {
        *(s64 *)(d + 0xA8) = 0;
        func_00298240(*(s32 *)(d + 0xC), (s32)(d + 0xA8));
    }
    func_002980A8(*(s32 *)(p + 0x18) + 3, *(s32 *)(d + 0xC));
    *(s32 *)p = *(s32 *)p + 1;
    return 0;
}
