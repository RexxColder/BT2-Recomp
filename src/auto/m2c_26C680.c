#include "m2c_macros.h"

M2C_UNK func_0026C380(s32, s32);                    /* extern */
M2C_UNK func_0026F888(s32);                         /* extern */
M2C_UNK func_00270198(s32);                         /* extern */

void func_0026C680(void *arg0, void *arg1) {
    s32 temp_a0;
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0);
    if (temp_v0 != 0) {
        func_0026F888(temp_v0);
        M2C_FIELD(arg0, s32 *, 0) = 0;
    }
    temp_v0_2 = M2C_FIELD(arg0, s32 *, 4);
    if (temp_v0_2 != 0) {
        func_0026C380(M2C_FIELD(arg1, s32 *, 0x24), temp_v0_2);
        M2C_FIELD(arg0, s32 *, 4) = 0;
    }
    temp_a0 = M2C_FIELD(arg0, s32 *, 8);
    if (temp_a0 != 0) {
        func_00270198(temp_a0);
        M2C_FIELD(arg0, s32 *, 8) = 0;
    }
}
