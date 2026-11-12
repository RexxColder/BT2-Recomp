#include "common.h"

void func_0026E908(s32 arg0);
void func_0028BB60(s32 arg0);
extern s32 D_00387A10;

void func_002596F0(void) {
    s32 s0 = 2;
    s32 s1 = 0;

    do {
        s0 -= 1;
        func_0026E908(D_00387A10 + s1 + 0x4);
        s1 += 0x28;
    } while (s0 >= 0);
    func_0028BB60(D_00387A10);
}
