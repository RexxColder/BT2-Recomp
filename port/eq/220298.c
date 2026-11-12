#include "common.h"

void func_002113C0(u8 *a0, s32 a1, s32 a2, s32 a3);

/* 0x00220298: func_002113C0(a0, 2, 0x100, 1); *(a0 + 0xB84) = 0x1E. */
void func_00220298(u8 *a0) {
    func_002113C0(a0, 2, 0x100, 1);
    *(s32 *)(a0 + 0xB84) = 0x1E;
}
