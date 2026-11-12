#include "common.h"

void func_002AC9C0(s32 arg0, s32 arg1, s32 arg2);
extern s32 D_003B2654 __attribute__((section(".data")));

void func_002AC9E0(void) {
    D_003B2654 &= ~0x301;
    func_002AC9C0(-0x201, -0x101, -2);
}
