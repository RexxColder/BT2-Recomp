#include "common.h"

extern u8 *D_0042139C __attribute__((section(".data")));
extern u8 *D_003876A4 __attribute__((section(".data")));

u8 *func_100ED0(s32 arg0, u8 *arg1, s32 arg2);
void func_299608(void);
void func_298158(s32 arg0);
void func_28BCB0(void);
void func_297A60(s32 arg0, s32 arg1);
void func_297EC8(void);
void func_28BCE8(void);
void func_28BB60(u8 *arg0);
void func_101438(s32 arg0);
void func_1012D0(void);
s32 func_003FA4E8(s32 arg0);
s32 func_003FD990(s32 arg0);
void func_003F5610(s32 arg0);
s32 func_003F3A90(s32 arg0);
s32 func_003F7F98(s32 arg0);
void func_003FB470(s32 arg0);
s32 func_004027B0(s32 arg0);
s32 func_003F9170(s32 arg0);
void func_003FF038(s32 arg0);
void *memset(void *dst, s32 c, u32 n);

/* 0x003F9300: one-time init when D_0042139C is 0 (it takes the return of func_100ED0), then a loop that dispatches on
 * P->0x1C (P = D_003876A4) for states 10..21 (jtbl_0042B2B0) until a case sets done. A local flag "called" guards the
 * func_101438(0x3E21) call and is cleared by func_1012D0 calls. Return value is ret (1 until state 10's success path
 * sets it to 0). At exit D_0042139C is passed to func_28BB60 and cleared. */
s32 func_003F9300(void) {
    s32 called;
    s32 done;
    s32 ret;
    s32 st;

    called = 0;
    done = 0;
    ret = 1;

    if (D_0042139C == 0) {
        D_0042139C = func_100ED0(*(s32 *)(D_003876A4 + 0x4) + 0x15, 0, 1);
        func_299608();
    }
    func_298158(0);
    func_28BCB0();
    func_297A60(0x33E6, 0);

    for (;;) {
        st = *(s32 *)(D_003876A4 + 0x1C);
        switch (st) {
        case 10:
            if (!called) {
                func_101438(0x3E21);
                called = 1;
            }
            if (func_003FA4E8(2) == 0) {
                func_1012D0();
                called = 0;
                *(s32 *)(D_003876A4 + 0x1C) = 4;
                ret = 0;
                done = 1;
            }
            break;

        case 11:
            if (!called) {
                func_101438(0x3E28);
            }
            if (func_003F3A90(4) != 0) {
                func_1012D0();
                called = 0;
                *(s32 *)(D_003876A4 + 0x1C) = 0x10;
            } else {
                func_1012D0();
                called = 0;
                *(s32 *)(D_003876A4 + 0x1C) = 0xE;
            }
            break;

        case 12:
            if (!called) {
                func_101438(0x3E21);
                called = 1;
            }
            if (func_003FD990(6) != 0) {
                func_1012D0();
                called = 0;
                *(s32 *)(D_003876A4 + 0x1C) = 0xC;
                done = 1;
            }
            break;

        case 13:
            func_003F5610(7);
            break;

        case 14:
            if (!called) {
                func_101438(0x3E21);
                called = 1;
            }
            if (func_003F7F98(1) != 0) {
                func_1012D0();
                called = 0;
                *(s32 *)(D_003876A4 + 0x1C) = 0xB;
            } else {
                *(s32 *)(D_003876A4 + 0x1C) = 0xA;
            }
            break;

        case 15:
            func_003FB470(3);
            *(s32 *)(D_003876A4 + 0x1C) = 0xA;
            break;

        case 16:
            if (!called) {
                func_101438(0x3E21);
                called = 1;
            }
            if (func_004027B0(5) != 0) {
                func_1012D0();
                called = 0;
                *(s32 *)(D_003876A4 + 0x1C) = 0xC;
                done = 1;
            } else {
                *(s32 *)(D_003876A4 + 0x1C) = 0xD;
            }
            break;

        case 17:
            if (func_003F9170(6) != 0) {
                *(s32 *)(D_003876A4 + 0x1C) = 0xD;
            } else {
                *(s32 *)(D_003876A4 + 0x1C) = 0x10;
            }
            break;

        case 18:
            if (!called) {
                func_101438(0x3E21);
                called = 1;
            }
            func_003FF038(6);
            *(s32 *)(D_003876A4 + 0x1C) = 0xA;
            memset(D_003876A4 + 0x40, 0, 0x48);
            break;

        case 19:
            func_003F5610(7);
            *(s32 *)(D_003876A4 + 0x1C) = 0x12;
            break;

        case 20:
            func_003F5610(7);
            *(s32 *)(D_003876A4 + 0x1C) = 0xA;
            memset(D_003876A4 + 0x40, 0, 0x48);
            break;

        case 21:
            *(s32 *)(D_003876A4 + 0x1C) = 0x12;
            break;

        default:
            break;
        }

        if (done != 0) {
            break;
        }
    }

    func_297EC8();
    func_28BCE8();
    func_28BB60(D_0042139C);
    D_0042139C = 0;
    return ret;
}
