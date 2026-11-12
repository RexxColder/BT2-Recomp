#include "common.h"

s32 func_00100ED0(s32 a0, s32 a1, s32 a2);
extern u8 D_003876A8;
extern s32 D_003B0F6C;

/* 0x002A3CE0 (approx): D_003B0F6C = func_00100ED0(a0, 0, D_003876A8 != 0); clear D_003876A8. */
void func_002A3CE0(s32 a0) {
    D_003B0F6C = func_00100ED0(a0, 0, D_003876A8 != 0);
    if (D_003876A8 != 0) {
        D_003876A8 = 0;
    }
}
