#include "m2c_macros.h"

M2C_UNK func_0026C018(s32);                         /* extern */
M2C_UNK func_0026DEB8(s32);                         /* extern */
M2C_UNK func_0026F738(s32);                         /* extern */
M2C_UNK func_0026FDD8(s32);                         /* extern */
M2C_UNK func_0028BB60(s32);                         /* extern */
M2C_UNK memset(void *, M2C_UNK, M2C_UNK);           /* extern */

void func_0026E908(void *arg0) {
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_a0_4;
    s32 temp_a0_5;
    s32 temp_a0_6;
    s32 temp_a0_7;
    s32 temp_a0_8;

    temp_a0 = M2C_FIELD(arg0, s32 *, 0x24);
    if (temp_a0 != 0) {
        func_0026C018(temp_a0);
        temp_a0_2 = M2C_FIELD(arg0, s32 *, 0x24);
        if (temp_a0_2 != 0) {
            func_0028BB60(temp_a0_2);
            M2C_FIELD(arg0, s32 *, 0x24) = 0;
        }
    }
    temp_a0_3 = M2C_FIELD(arg0, s32 *, 0x20);
    if (temp_a0_3 != 0) {
        func_0026F738(temp_a0_3);
        temp_a0_4 = M2C_FIELD(arg0, s32 *, 0x20);
        if (temp_a0_4 != 0) {
            func_0028BB60(temp_a0_4);
            M2C_FIELD(arg0, s32 *, 0x20) = 0;
        }
    }
    temp_a0_5 = M2C_FIELD(arg0, s32 *, 0x1C);
    if (temp_a0_5 != 0) {
        func_0026FDD8(temp_a0_5);
        temp_a0_6 = M2C_FIELD(arg0, s32 *, 0x1C);
        if (temp_a0_6 != 0) {
            func_0028BB60(temp_a0_6);
            M2C_FIELD(arg0, s32 *, 0x1C) = 0;
        }
    }
    temp_a0_7 = M2C_FIELD(arg0, s32 *, 0x18);
    if (temp_a0_7 != 0) {
        func_0026DEB8(temp_a0_7);
        temp_a0_8 = M2C_FIELD(arg0, s32 *, 0x18);
        if (temp_a0_8 != 0) {
            func_0028BB60(temp_a0_8);
            M2C_FIELD(arg0, s32 *, 0x18) = 0;
        }
    }
    memset(arg0, 0, 0x28);
}
