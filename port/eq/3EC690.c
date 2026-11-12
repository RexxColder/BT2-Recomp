#include "common.h"

extern s32 D_004213A0 __attribute__((section(".data")));
extern u8 *D_3876A4 __attribute__((section(".data")));

s32 func_100D58(s32 a0, s32 a1, s32 a2);
void func_298158(s32 a0);
void func_28BCB0(void);
void func_297A60(s32 a0, s32 a1);
void func_101438(s32 a0);
void func_1012D0(void);
s32 func_003F0510(s32 a0);
s32 func_003EC558(s32 a0);
s32 func_00409BB8(s32 a0);
s32 func_0041A5D8(s32 a0);
void func_297EC8(void);
void func_28BCE8(void);
void func_28BB60(s32 a0);

/* 0x003EC690: sibling of 0x003CB1D0 (same boot and state machine shape) on D_3876A4->0x1C with states 0x3D..0x40.
 * Returns s7 (1, cleared to 0 by the 0x3D path when func_003F0510 fails). */
s32 func_003EC690(void) {
    u8 *G;
    s32 s1 = 0;
    s32 s3 = 0;
    s32 s7 = 1;
    s32 state;

    if (D_004213A0 == 0) {
        func_100D58(*(s32 *)(D_3876A4 + 0x4) + 8, 0, 1);
        do {
            D_004213A0 = func_100D58(0, 0, 0);
        } while (D_004213A0 == 0);
    }
    func_298158(0);
    func_28BCB0();
    func_297A60(0x33E6, 0);

    do {
        G = D_3876A4;
        state = *(s32 *)(G + 0x1C);
        if (state == 0x3E) {
            if (s1 == 0) {
                func_101438(0x3E2A);
                s1 = 1;
            }
            if (func_003EC558(2) == 0) {
                *(s32 *)(D_3876A4 + 0x1C) = 0x3D;
            } else {
                func_1012D0();
                s3 = 1;
                s1 = 0;
            }
        } else if (state == 0x3D) {
            if (s1 == 0) {
                func_101438(0x3E2A);
                s1 = 1;
            }
            if (func_003F0510(1) == 0) {
                func_1012D0();
                s1 = 0;
                *(s32 *)(D_3876A4 + 0x1C) = 0x4;
                s7 = 0;
                s3 = 1;
            } else if (*(s32 *)(D_3876A4 + 0x1C) == 0x3F) {
                func_1012D0();
                s1 = 0;
            }
        } else if (state == 0x3F) {
            if (s1 == 0) {
                func_101438(0x3E28);
            }
            if (func_00409BB8(3) != 0) {
                func_1012D0();
                s1 = 0;
                *(s32 *)(D_3876A4 + 0x1C) = 0x40;
            } else {
                func_1012D0();
                s1 = 0;
                *(s32 *)(D_3876A4 + 0x1C) = 0x3D;
            }
        } else if (state == 0x40) {
            if (s1 == 0) {
                func_101438(0x3E29);
            }
            if (func_0041A5D8(4) != 0) {
                func_1012D0();
                s1 = 0;
                s3 = 1;
            } else {
                func_1012D0();
                s1 = 0;
            }
            *(s32 *)(D_3876A4 + 0x1C) = 0x3F;
        }
    } while (s3 == 0);

    func_297EC8();
    func_28BCE8();
    func_28BB60(D_004213A0);
    D_004213A0 = 0;
    return s7;
}
