#include "m2c_macros.h"

M2C_UNK func_0026F8B8(s32, M2C_UNK, M2C_UNK);       /* extern; asm 0x26C724 passes a1/a2 through */
M2C_UNK func_00270120(s32, M2C_UNK, M2C_UNK);       /* extern */

void func_0026C6F8(void *arg0, M2C_UNK arg1, M2C_UNK arg2) {
    s32 temp_a0;
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0);
    if (temp_v0 != 0) {
        func_0026F8B8(temp_v0, arg1, arg2);
    }
    temp_a0 = M2C_FIELD(arg0, s32 *, 8);
    if (temp_a0 != 0) {
        func_00270120(temp_a0, arg1, arg2);
    }
}
