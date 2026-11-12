#include "common.h"

extern s32 D_00421398 __attribute__((section(".data")));
extern u8 *D_003876A4 __attribute__((section(".data")));

s32 func_100D58(u8 *arg0, s32 arg1, s32 arg2);
void func_1012D0(void);
void func_101438(s32 arg0);
void func_28BB60(void *arg0);
void func_28BCB0(void);
void func_28BCE8(void);
void func_297A60(s32 arg0, s32 arg1);
void func_297EC8(void);
void func_298158(s32 arg0);
s32 func_003E3A48(s32 arg0);
s32 func_003E6658(s32 arg0);
s32 func_003E8270(s32 arg0);
s32 func_003EA078(s32 arg0);

/* 0x003E3B98: if D_00421398 == 0: func_100D58(*(D_003876A4+4)+0xC, 0, 1), then D_00421398 = func_100D58(0,0,0) until
 * nonzero. func_298158(0), func_101438(0x3E2E), func_28BCB0(), func_297A60(0x33D2, 0). Loop on G->0x1C (G = D_003876A4):
 * 0x31 -> func_003E3A48(2), state 0x30; 0x30 -> if func_003E6658(1) == 0: state 4 and exit; 0x32 -> func_003E8270(3),
 * state 0x30; 0x33 -> func_003EA078(4), state 0x30. Exit: func_1012D0(), func_297EC8(), func_28BCE8(),
 * func_28BB60(D_00421398), D_00421398 = 0, return 1. */
s32 func_003E3B98(void) {
    s32 s2 = 0;
    s32 v1;

    if (D_00421398 == 0) {
        func_100D58(*(u8 **)(D_003876A4 + 4) + 0xC, 0, 1);
        do {
            D_00421398 = func_100D58(0, 0, 0);
        } while (D_00421398 == 0);
    }
    func_298158(0);
    func_101438(0x3E2E);
    func_28BCB0();
    func_297A60(0x33D2, 0);

    do {
        v1 = *(s32 *)(D_003876A4 + 0x1C);
        if (v1 == 0x31) {
            func_003E3A48(2);
            *(s32 *)(D_003876A4 + 0x1C) = 0x30;
        } else if (v1 == 0x30) {
            if (func_003E6658(1) == 0) {
                *(s32 *)(D_003876A4 + 0x1C) = 4;
                s2 = 1;
            }
        } else if (v1 == 0x32) {
            func_003E8270(3);
            *(s32 *)(D_003876A4 + 0x1C) = 0x30;
        } else if (v1 == 0x33) {
            func_003EA078(4);
            *(s32 *)(D_003876A4 + 0x1C) = 0x30;
        }
    } while (s2 == 0);

    func_1012D0();
    func_297EC8();
    func_28BCE8();
    func_28BB60((void *)(s32)D_00421398);
    D_00421398 = 0;
    return 1;
}
