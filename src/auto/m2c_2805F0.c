#include "m2c_macros.h"

extern void *D_003876A0;
extern s32 D_00387AF8;

void func_002805F0(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_a0;

    temp_a0 = arg0 * 0xBC0;
    if (M2C_FIELD(D_003876A0, s64 *, 0x4D8) & 3) {
        M2C_FIELD((temp_a0 + D_00387AF8), s32 *, 0x614) = arg1;
        M2C_FIELD((temp_a0 + D_00387AF8), s32 *, 0x618) = arg2;
    }
}
