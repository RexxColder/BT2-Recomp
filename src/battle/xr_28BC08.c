#include "m2c_macros.h"

M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);        /* extern */
extern s32 D_00387EB4;
extern M2C_UNK D_0038A638 __attribute__((section(".data")));

/* Clears the 0x60-byte table at 0x38A638 and writes a sentinel entry keyed by D_00387EB4 (guess: init of a fixed table) */
void func_0028BC08(void) {
    s32 temp_v1;

    D_00387EB4 = 0;
    memset(&D_0038A638, 0, 0x60);
    temp_v1 = D_00387EB4 * 2;
    *(temp_v1 + &D_0038A638) = 0x5010;
    M2C_FIELD((&D_0038A638 + temp_v1), s32 *, 4) = 0x1BAFEF;
}
