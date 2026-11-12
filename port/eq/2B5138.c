#include "common.h"

extern u8 D_00378440[] __attribute__((section(".data")));
void Rand_Range(u8 *a0, s32 a1);

void func_002B5138(u8 *arg0, s32 arg1) {
    s32 v = *(s32 *)(arg0 + 0x2D4);

    if (v == 0) {
        *(s32 *)(arg0 + 0x2D4) = arg1;
        return;
    }
    if (v != arg1) {
        Rand_Range(D_00378440, arg1);
    }
}
