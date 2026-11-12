#include "common.h"

s32 func_0026EB70(s32 arg0);
void func_0026E9E8(s32 arg0);
void func_002510E0(s32 arg0);
void func_00297FE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern u8 *D_003876A4;
extern s32 D_00387958;

void func_00244600(void) {
    s32 s0;
    s32 s1;

    if (func_0026EB70(D_00387958 + 0x28) & 0x10) {
        if (*(s32 *)(D_003876A4 + 0x1C) == 5) {
            func_00297FE0(2, 2, 0x40, 0x40, 1);
        } else {
            func_00297FE0(4, 2, 0x40, 0x40, 1);
        }
    }
    if (func_0026EB70(D_00387958 + 0x28) & 0x20) {
        if (*(s32 *)(D_003876A4 + 0x1C) == 5) {
            func_00297FE0(2, 3, 0x40, 0x40, 1);
        } else {
            func_00297FE0(4, 3, 0x40, 0x40, 1);
        }
    }
    s1 = 0;
    s0 = 3;
    do {
        s0 -= 1;
        func_0026E9E8(D_00387958 + s1);
        s1 += 0x28;
    } while (s0 >= 0);
    func_002510E0(D_00387958);
}
