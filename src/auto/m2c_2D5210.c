#include "m2c_macros.h"

s32 func_002D45E8();                                /* extern */
M2C_UNK func_002D4888(s32, M2C_UNK);                /* extern */

void func_002D5210(void *arg0, M2C_UNK arg1) {
    s32 temp_s1;

    temp_s1 = M2C_FIELD(arg0, s32 *, 4);
    if (func_002D45E8(arg0) != 0) {
        func_002D4888(temp_s1, arg1);
    }
}
