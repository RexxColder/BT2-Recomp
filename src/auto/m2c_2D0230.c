#include "m2c_macros.h"

M2C_UNK func_002C2FF0(M2C_UNK, M2C_UNK);            /* extern */
s32 func_002C3210();                                /* extern */

void func_002D0230(void *arg0, s32 arg1) {
    void *temp_a0;

    if (func_002C3210(arg0) != 0) {
        func_002C2FF0(0, 0xFF00015C);
        return;
    }
    temp_a0 = M2C_FIELD(arg0, void **, 0x36B0);
    if (temp_a0 != NULL) {
        M2C_FIELD(temp_a0, s32 *, 0xDD4) = arg1;
    }
}
