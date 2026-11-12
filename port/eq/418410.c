#include "common.h"

extern u8 *D_3876A4 __attribute__((section(".data")));
extern s32 D_00421394 __attribute__((section(".data")));

s32 func_100D58(s32 a0, s32 a1, s32 a2);
void func_101438(s32 a0);
void func_1012D0(void);
void func_298158(s32 a0);
void func_28BCB0(void);
void func_297A60(s32 a0, s32 a1);
void func_297EC8(void);
void func_28BCE8(void);
void func_28BB60(s32 a0);
s32 func_0041BCE8(s32 a0);
s32 func_0041A5D8(s32 a0);
s32 func_00409BB8(s32 a0);
s32 func_004115C0(s32 a0);
s32 func_004178F8(s32 a0);
void func_00405360(s32 a0);

/* 0x00418410: menu step on G = D_3876A4 (state at G->0x1C, 0x1E..0x23 via jtbl_0042ED50). sm is the message flag,
 * done ends the loop; returns ret (1 unless the 0x1E case finishes). */
s32 func_00418410(void) {
    u8 *G;
    s32 sm = 0;
    s32 done = 0;
    s32 ret = 1;

    if (D_00421394 == 0) {
        func_100D58(*(s32 *)(D_3876A4 + 0x4) + 2, 0, 1);
        do {
            D_00421394 = func_100D58(0, 0, 0);
        } while (D_00421394 == 0);
    }
    func_298158(0);
    func_28BCB0();
    func_297A60(0x33CF, 0);

    do {
        G = D_3876A4;
        switch ((u32)(*(s32 *)(G + 0x1C) - 0x1E)) {
        case 0:
            if (sm == 0) {
                func_101438(0x3E27);
                sm = 1;
            }
            if (func_0041BCE8(3) == 0) {
                func_1012D0();
                sm = 0;
                *(s32 *)(D_3876A4 + 0x1C) = 4;
                ret = 0;
                done = 1;
            }
            break;
        case 1:
            if (sm == 0) {
                func_101438(0x3E28);
                sm = 1;
            }
            if (func_00409BB8(1) == 0) {
                *(s32 *)(D_3876A4 + 0x1C) = 0x1E;
            } else {
                func_1012D0();
                sm = 0;
                *(s32 *)(D_3876A4 + 0x1C) = 0x22;
            }
            break;
        case 2:
            if (sm == 0) {
                func_101438(0x3E28);
                sm = 1;
            }
            if (func_004178F8(1) == 0) {
                *(s32 *)(D_3876A4 + 0x1C) = 0x1E;
            } else {
                func_1012D0();
                sm = 0;
                *(s32 *)(D_3876A4 + 0x1C) = 0x22;
            }
            break;
        case 3:
            if (sm == 0) {
                func_101438(0x3E28);
                sm = 1;
            }
            if (func_004115C0(1) == 0) {
                *(s32 *)(D_3876A4 + 0x1C) = 0x1E;
            } else {
                func_1012D0();
                sm = 0;
                *(s32 *)(D_3876A4 + 0x1C) = 0x22;
            }
            break;
        case 4:
            if (sm == 0) {
                func_101438(0x3E29);
            }
            if (func_0041A5D8(2) != 0) {
                func_1012D0();
                sm = 0;
                done = 1;
            } else {
                func_1012D0();
                sm = 0;
            }
            G = D_3876A4;
            if (*(s32 *)(G + 0x464) == 1) {
                *(s32 *)(G + 0x1C) = 0x20;
            } else if (*(s32 *)(G + 0x464) == 0) {
                *(s32 *)(G + 0x1C) = 0x1F;
            } else if (*(s32 *)(G + 0x464) == 2) {
                *(s32 *)(G + 0x1C) = 0x21;
            }
            break;
        case 5:
            func_00405360(3);
            *(s32 *)(D_3876A4 + 0x1C) = 0x1E;
            break;
        default:
            break;
        }
    } while (done == 0);

    func_297EC8();
    func_28BCE8();
    func_28BB60(D_00421394);
    D_00421394 = 0;
    return ret;
}
