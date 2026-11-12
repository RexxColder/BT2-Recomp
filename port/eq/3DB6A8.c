#include "common.h"

extern u8 *D_003876A4 __attribute__((section(".data")));
extern s32 D_003876AC __attribute__((section(".data")));

s32 func_100D58(u8 *arg0, s32 arg1, s32 arg2);
void func_1012D0(void);
void func_101438(s32 arg0);
s32 func_250978(s32 arg0);
void func_2539C8(s32 arg0);
void func_28BB60(void *arg0);
void func_28BCB0(void);
void func_28BCE8(void);
void func_297A60(s32 arg0, s32 arg1);
void func_297EC8(void);
void func_298158(s32 arg0);
s32 func_003DC5E0(s32 arg0);
void func_003DB4E0(s32 arg0);

/* 0x003DB6A8: if D_003876AC == 0: func_100D58(*(D_003876A4+4) + 9, 0, 1), then D_003876AC = func_100D58(0,0,0) until
 * nonzero. func_298158(0), func_101438(0x3E2B), func_28BCB0(), func_297A60(0x33D0, 0). Loop (at least once): switch on
 * G->0x1C - 0x35 (G = D_003876A4): 0 -> if func_003DC5E0(1) == 0, G->0x1C = 4, return value 0 and exit; 1 -> G->0x1C =
 * func_250978(2) ? 0x38 : 0x35; 2 -> nothing; 3 -> func_2539C8(3), 0x36; 4 -> func_2539C8(3), 0x35; 5 -> func_003DB4E0(4),
 * 0x35. Exit: func_1012D0(), func_297EC8(), func_28BCE8(), func_28BB60(D_003876AC), D_003876AC = 0, return s3. */
s32 func_003DB6A8(void) {
    s32 s1 = 0;
    s32 s3 = 1;
    s32 idx;

    if (D_003876AC == 0) {
        func_100D58(*(u8 **)(D_003876A4 + 4) + 9, 0, 1);
        do {
            D_003876AC = func_100D58(0, 0, 0);
        } while (D_003876AC == 0);
    }
    func_298158(0);
    func_101438(0x3E2B);
    func_28BCB0();
    func_297A60(0x33D0, 0);

    do {
        idx = *(s32 *)(D_003876A4 + 0x1C) - 0x35;
        if ((u32)idx < 6) {
            switch (idx) {
            case 0:
                if (func_003DC5E0(1) == 0) {
                    *(s32 *)(D_003876A4 + 0x1C) = 4;
                    s3 = 0;
                    s1 = 1;
                }
                break;
            case 1:
                if (func_250978(2) != 0) {
                    *(s32 *)(D_003876A4 + 0x1C) = 0x38;
                } else {
                    *(s32 *)(D_003876A4 + 0x1C) = 0x35;
                }
                break;
            case 2:
                break;
            case 3:
                func_2539C8(3);
                *(s32 *)(D_003876A4 + 0x1C) = 0x36;
                break;
            case 4:
                func_2539C8(3);
                *(s32 *)(D_003876A4 + 0x1C) = 0x35;
                break;
            case 5:
                func_003DB4E0(4);
                *(s32 *)(D_003876A4 + 0x1C) = 0x35;
                break;
            }
        }
    } while (s1 == 0);

    func_1012D0();
    func_297EC8();
    func_28BCE8();
    func_28BB60((void *)(s32)D_003876AC);
    D_003876AC = 0;
    return s3;
}
