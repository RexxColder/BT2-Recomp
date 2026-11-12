#include "common.h"

extern s32 D_004213A8 __attribute__((section(".data")));
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
s32 func_003C2668(s32 arg0);
void func_003C6260(s32 arg0);
void func_003C0518(s32 arg0);

/* 0x003C0700: if D_004213A8 == 0: func_100D58(*(D_003876A4+4)+0xB, 0, 1), then D_004213A8 = func_100D58(0,0,0) until
 * nonzero. func_298158(0), func_101438(0x3E2D), func_28BCB0(), func_297A60(0x33E7, 0). Loop with G = D_003876A4:
 * state 0x27 -> func_003C6260(2), state 0x26; state 0x26 -> if func_003C2668(1) == 0: state 4, return 0 (after exit);
 * state 0x28 -> func_003C0518(3), state 0x26. Exit on the 0x26 success: func_1012D0(), func_297EC8(), func_28BCE8(),
 * func_28BB60(D_004213A8), D_004213A8 = 0, return the flag (1 unless exited through state 0x26). */
s32 func_003C0700(void) {
    s32 s2 = 0;
    s32 s4 = 1;
    s32 v1;

    if (D_004213A8 == 0) {
        func_100D58(*(u8 **)(D_003876A4 + 4) + 0xB, 0, 1);
        do {
            D_004213A8 = func_100D58(0, 0, 0);
        } while (D_004213A8 == 0);
    }
    func_298158(0);
    func_101438(0x3E2D);
    func_28BCB0();
    func_297A60(0x33E7, 0);

    do {
        v1 = *(s32 *)(D_003876A4 + 0x1C);
        if (v1 == 0x27) {
            func_003C6260(2);
            *(s32 *)(D_003876A4 + 0x1C) = 0x26;
        } else if (v1 == 0x26) {
            if (func_003C2668(1) == 0) {
                *(s32 *)(D_003876A4 + 0x1C) = 4;
                s4 = 0;
                s2 = 1;
            }
        } else if (v1 == 0x28) {
            func_003C0518(3);
            *(s32 *)(D_003876A4 + 0x1C) = 0x26;
        }
    } while (s2 == 0);

    func_1012D0();
    func_297EC8();
    func_28BCE8();
    func_28BB60((void *)(s32)D_004213A8);
    D_004213A8 = 0;
    return s4;
}
