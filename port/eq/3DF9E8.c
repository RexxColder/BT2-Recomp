#include "common.h"

extern s32 D_004213A4 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));

s32 func_100D58(s32 a0, s32 a1, s32 a2);
void func_1012D0(void);
void func_101438(s32 a0);
void func_298158(s32 a0);
void func_28BB60(s32 a0);
void func_28BCB0(void);
void func_28BCE8(void);
void func_297A60(s32 a0, s32 a1);
void func_297EC8(void);
s32 func_003DE7C0(s32 a0);
s32 func_003DF8C8(s32 a0);
s32 func_003E09A0(s32 a0);
s32 func_003E1988(s32 a0);

/* 0x003DF9E8: menu state machine on P = D_3876A4 (state word P->0x1C, dispatched on P->0x1C - 0x2B through
 * jtbl_004275D0, cases 0..4). The first call of the frame seeds D_004213A4 with func_100D58 until it is non-zero.
 * Case 0 runs func_003E09A0(1) and on 0 sets s4 = 0, done = 1, P->0x1C = 4; case 1 func_003DE7C0(2) -> 0x2B; case 2
 * func_003DF8C8(3) -> 0x2B; case 3 func_1012D0 + func_003E1988(4) -> 0x2B and func_101438(0x3E2F); case 4 -> 0x2C.
 * Cases 1..3 test the result s0 of the call they made, case 4 the stale s0. Loop until done, then cleanup and return s4. */
s32 func_003DF9E8(void) {
    s32 s0;
    s32 done;
    s32 s4;
    s32 v;

    s0 = 0;
    done = 0;
    s4 = 1;
    if (D_004213A4 == 0) {
        func_100D58(*(s32 *)(D_3876A4 + 0x4) + 0xA, 0, 1);
        do {
            v = func_100D58(0, 0, 0);
            D_004213A4 = v;
        } while (v == 0);
    }
    func_298158(0);
    func_101438(0x3E2F);
    func_28BCB0();
    func_297A60(0x33CD, 0);
    do {
        v = *(s32 *)(D_3876A4 + 0x1C) - 0x2B;
        if ((u32)v < 5) {
            switch (v) {
            case 0:
                s0 = func_003E09A0(1);
                if (s0 == 0) {
                    s4 = 0;
                    done = 1;
                    *(s32 *)(D_3876A4 + 0x1C) = 4;
                }
                break;
            case 1:
                s0 = func_003DE7C0(2);
                if (s0 == 0) {
                    *(s32 *)(D_3876A4 + 0x1C) = 0x2B;
                }
                break;
            case 2:
                s0 = func_003DF8C8(3);
                if (s0 == 0) {
                    *(s32 *)(D_3876A4 + 0x1C) = 0x2B;
                }
                break;
            case 3:
                func_1012D0();
                s0 = func_003E1988(4);
                if (s0 == 0) {
                    *(s32 *)(D_3876A4 + 0x1C) = 0x2B;
                    func_101438(0x3E2F);
                }
                break;
            case 4:
                if (s0 == 0) {
                    *(s32 *)(D_3876A4 + 0x1C) = 0x2C;
                }
                break;
            }
        }
    } while (done == 0);

    func_1012D0();
    func_297EC8();
    func_28BCE8();
    func_28BB60(D_004213A4);
    D_004213A4 = 0;
    return s4;
}
