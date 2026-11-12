#include "m2c_macros.h"

extern s32 D_00387858;

// Clears 16 records of 12 bytes in D_00387858 (words +0xC, +0x10, +0x14 of each), then words +0xCC, +0x4, +0xC for two indices (guess: state reset).
void func_001AE8D0(void) {
    s32 temp_a0;
    s32 temp_v1;
    s32 var_a0;
    s32 var_a2;
    void *temp_v0;

    var_a0 = 0;
    var_a2 = 0xF;
    do {
        var_a2 -= 1;
        M2C_FIELD((D_00387858 + var_a0), s32 *, 0xC) = 0;
        M2C_FIELD((D_00387858 + var_a0), s32 *, 0x10) = 0;
        temp_v0 = (void *) (D_00387858 + var_a0);
        var_a0 += 0xC;
        M2C_FIELD(temp_v0, s32 *, 0x14) = 0;
    } while (var_a2 >= 0);
    var_a2 = 0;
    do {
        temp_v1 = var_a2 * 4;
        temp_a0 = temp_v1 + 0xD0;
        var_a2 += 1;
        M2C_FIELD((temp_v1 + D_00387858), s32 *, 0xCC) = 0;
        M2C_FIELD((D_00387858 + temp_a0), s32 *, 4) = 0;
        M2C_FIELD((D_00387858 + temp_a0), s32 *, 0xC) = 0;
    } while (var_a2 < 2);
}
