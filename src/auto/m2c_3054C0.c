#include "m2c_macros.h"

M2C_UNK memset(M2C_UNK *, M2C_UNK, M2C_UNK);        /* extern */
extern s32 D_00364B00 __attribute__((section(".data")));
extern M2C_UNK D_00364B08 __attribute__((section(".data")));

void func_003054C0(void) {
    s32 temp_v0;

    temp_v0 = D_00364B00 - 1;
    D_00364B00 = temp_v0;
    if (temp_v0 == 0) {
        memset(&D_00364B08, 0, 0xC00);
    }
}
