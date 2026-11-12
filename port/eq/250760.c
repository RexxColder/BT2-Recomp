#include "common.h"

s32 func_0029C550(s32 arg0);
s32 func_0029C820(s32 arg0);
s32 func_0029C7C0(s32 arg0);
s32 func_0029C640(s32 arg0);
s32 func_0029C830(void);
s32 func_0029C7D0(s32 arg0);
s32 func_0029C800(s32 arg0);
s32 func_0029C1E8(s32 arg0);
void func_0024C528(void);
void func_0024F558(void);
void func_0024C7A8(void);
extern u8 *D_003879A0;
extern u8 *D_003876A4;

s32 func_00250760(void) {
    u8 *gs;
    u8 *ps;
    s32 st;
    s32 v;

    gs = D_003879A0;
    st = *(s32 *)(gs + 0x3304);
    if (st == 0) {
        return 0;
    }

    switch (st) {
    case 1:
        func_0029C550(0);
        func_0029C820(1);
        *(s32 *)(gs + 0x3304) = 2;
        /* fall through */
    case 2:
        func_0029C7C0(1);
        gs = D_003879A0;
        v = *(s32 *)(gs + 0x330C);
        if (v > 0) {
            *(s32 *)(gs + 0x3304) = 3;
            *(s32 *)(gs + 0x330C) = 0;
            func_0029C550(1);
        } else if (v == 0) {
            *(s32 *)(gs + 0x330C) = func_0029C640(0);
        } else {
            *(s32 *)(gs + 0x3304) = 4;
            *(s32 *)(gs + 0x330C) = 0;
            func_0029C550(1);
        }
        break;
    case 3:
        func_0029C640(0);
        if (func_0029C830() != 0) {
            func_0024C528();
            func_0024F558();
            *(s32 *)(D_003879A0 + 0x3304) = 0;
        }
        break;
    case 4:
        func_0029C640(0);
        if (func_0029C830() != 0) {
            *(s32 *)(D_003879A0 + 0x3304) = 0;
        }
        break;
    case 5:
        func_0029C550(0);
        func_0029C820(1);
        *(s32 *)(gs + 0x3304) = 6;
        /* fall through */
    case 6:
        func_0029C7C0(1);
        gs = D_003879A0;
        v = *(s32 *)(gs + 0x330C);
        if (v > 0) {
            *(s32 *)(gs + 0x3304) = 7;
            *(s32 *)(gs + 0x330C) = 0;
            func_0029C550(1);
        } else if (v == 0) {
            *(s32 *)(gs + 0x330C) = func_0029C640(0);
        } else {
            *(s32 *)(gs + 0x3304) = 8;
            *(s32 *)(gs + 0x330C) = 0;
            func_0029C550(1);
        }
        break;
    case 7:
        func_0029C640(0);
        if (func_0029C830() != 0) {
            func_0024C7A8();
            *(s32 *)(D_003879A0 + 0x3228) = 3;
            *(s32 *)(D_003879A0 + 0x3304) = 0;
        }
        break;
    case 8:
        func_0029C640(0);
        if (func_0029C830() != 0) {
            *(s32 *)(D_003879A0 + 0x1C4) |= 0x100;
            *(s32 *)(D_003879A0 + 0x1C4) |= 0x400;
            *(s32 *)(D_003879A0 + 0x3230) = 0xF;
            *(s32 *)(D_003876A4 + 0x48C) |= 0x10;
            *(s32 *)(D_003879A0 + 0x3304) = 0;
        }
        break;
    default:
        break;
    }
    ps = D_003876A4;
    func_0029C7D0(*(s32 *)(ps + 0x48C) & 1);
    gs = D_003879A0;
    func_0029C800(*(s32 *)(gs + 0x3310));
    return func_0029C1E8(1);
}
