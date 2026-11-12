#include "common.h"

void func_003126C8(s32 a0, s32 a1);
extern u8 *D_00387A30;

/* 0x0025AD78: copy from D_00387A30+0x2C0 and +0x2D0 into a0 and a1. */
void func_0025AD78(s32 a0, s32 a1) {
    func_003126C8(a0, (s32)(D_00387A30 + 0x2C0));
    func_003126C8(a1, (s32)(D_00387A30 + 0x2D0));
}
