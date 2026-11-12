#include "common.h"

extern u8 *D_003876A0;

u8 *func_00105A88(void);
s32 func_00105A78(u8 *a0);
s32 func_00105F78(s32 a0);
void func_00105AC8(u8 *a0);
void func_001F8760(u8 *a0);
s32 func_0020A758(s32 a0);
s32 func_0020AE88(s32 a0);
s32 func_0020B218(s32 a0);

/* 0x00105BA8: state update for the record returned by func_00105A88 (fields +0 and +4); returns 1 when
 * the record was set, 0 when a check failed. Branches follow the original's order exactly. */
s32 func_00105BA8(void) {
    u8 *p;
    s32 a0;

    p = func_00105A88();
    if ((*(s32 *)p & 0xF) != 0) {
        return 1;
    }
    if ((*(s64 *)(D_003876A0 + 0x4D8) & 0x100) != 0) {
        return 0;
    }
    if (func_00105F78(func_00105A78(D_003876A0)) != 0) {
        func_001F8760(p);
        a0 = *(s32 *)(D_003876A0 + 0xC8);
        if (a0 == 1) {
            *(s32 *)p = a0;
        } else {
            func_00105AC8(p);
        }
        *(s32 *)(p + 4) = 4;
        return 1;
    }
    if (func_0020A758(0) != 0) {
        return 0;
    }
    if (func_0020A758(1) != 0) {
        return 0;
    }
    if (func_0020B218(0) != 0 && func_0020AE88(1) != 0) {
        func_001F8760(p);
        func_00105AC8(p);
        *(s32 *)(p + 4) = 8;
        return 1;
    }
    if (func_0020B218(1) != 0) {
        func_001F8760(p);
        *(s32 *)p = 1;
        *(s32 *)(p + 4) = 8;
        return 1;
    }
    if (func_0020B218(0) != 0) {
        func_001F8760(p);
        *(s32 *)p = 2;
        *(s32 *)(p + 4) = 8;
        return 1;
    }
    if (func_0020AE88(0) != 0 && func_0020AE88(1) != 0) {
        func_001F8760(p);
        func_00105AC8(p);
        *(s32 *)(p + 4) = 1;
        return 1;
    }
    if (func_0020AE88(1) != 0) {
        func_001F8760(p);
        *(s32 *)(p + 4) = 1;
        *(s32 *)p = 1;
        return 1;
    }
    if (func_0020AE88(0) == 0) {
        return 0;
    }
    func_001F8760(p);
    *(s32 *)p = 2;
    *(s32 *)(p + 4) = 1;
    return 1;
}
