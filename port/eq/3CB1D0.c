#include "common.h"

extern s32 D_00421390 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));

s32 func_100D58(s32 a0, s32 a1, s32 a2);
void func_1012D0(void);
void func_101438(s32 a0);
s32 func_003CABA8(s32 a0);
s32 func_003CD778(s32 a0);
void func_003CFAF8(s32 a0);
s32 func_003D09C0(s32 a0);
void func_28BB60(s32 a0);
void func_28BCB0(void);
void func_28BCE8(void);
void func_297A60(s32 a0, s32 a1);
void func_297EC8(void);
void func_298158(s32 a0);

/* 0x003CB1D0: boot/state step of the menu. Once D_00421390 (flag) is set, it runs a state machine on
 * D_3876A4->0x1C (states 0x18, 0x19, 0x1A, 0x1B) until s2 is set. Returns s6 (1 unless the 0x18 case finished). */
s32 func_003CB1D0(void) {
    u8 *G;
    s32 s2 = 0;
    s32 s6 = 1;
    s32 s7 = 0;
    s32 state;

    if (D_00421390 == 0) {
        func_100D58(*(s32 *)(D_3876A4 + 0x4) + 3, 0, 1);
        do {
            D_00421390 = func_100D58(0, 0, 0);
        } while (D_00421390 == 0);
    }
    func_298158(0);
    func_28BCB0();
    func_297A60(0x33CE, 0);

    do {
        G = D_3876A4;
        state = *(s32 *)(G + 0x1C);
        if (state == 0x19) {
            if (s7 == 0) {
                func_101438(0x3E28);
            }
            if (func_003CABA8(1) != 0) {
                func_1012D0();
                s7 = 0;
                *(s32 *)(D_3876A4 + 0x1C) = 0x1A;
            } else {
                func_1012D0();
                s7 = 0;
                *(s32 *)(D_3876A4 + 0x1C) = 0x18;
            }
        } else if (state < 0x1A) {
            if (state == 0x18) {
                if (s7 == 0) {
                    func_101438(0x3E23);
                }
                if (func_003CD778(2) != 0) {
                    func_1012D0();
                    s7 = 0;
                    *(s32 *)(D_3876A4 + 0x1C) = 0x19;
                } else {
                    func_1012D0();
                    s7 = 0;
                    *(s32 *)(D_3876A4 + 0x1C) = 0x4;
                    s6 = 0;
                    s2 = 1;
                }
            }
        } else if (state == 0x1A) {
            if (s7 == 0) {
                func_101438(*(s32 *)(G + 0x8C) + 0x3E24);
            }
            if (func_003D09C0(0) != 0) {
                func_1012D0();
                s7 = 0;
                s2 = 1;
            } else {
                func_1012D0();
                s7 = 0;
            }
        } else if (state == 0x1B) {
            if (s7 == 0) {
                s7 = 1;
                func_101438(0x3E23);
            }
            func_003CFAF8(2);
            *(s32 *)(D_3876A4 + 0x1C) = 0x18;
        }
    } while (s2 == 0);

    func_297EC8();
    func_28BCE8();
    func_28BB60(D_00421390);
    D_00421390 = 0;
    return s6;
}
