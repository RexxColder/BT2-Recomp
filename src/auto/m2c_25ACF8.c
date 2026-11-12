#include "m2c_macros.h"

M2C_UNK func_003126C8(void *, s32);                 /* extern */
extern void *D_00387A30;

void func_0025ACF8(s32 arg0, s32 arg1) {
    if (M2C_FIELD(D_00387A30, s32 *, 0x2B0) != 0) {
        M2C_FIELD(D_00387A30, s32 *, 0x2F8) = (s32) (M2C_FIELD(D_00387A30, s32 *, 0x2F8) | 2);
    }
    M2C_FIELD(D_00387A30, s8 *, 0x31C) = 1;
    func_003126C8(D_00387A30 + 0x2C0, arg0);
    func_003126C8(D_00387A30 + 0x2D0, arg1);
    M2C_FIELD(D_00387A30, f32 *, 0x2CC) = 1.0f;
    M2C_FIELD(D_00387A30, f32 *, 0x2DC) = 1.0f;
}
