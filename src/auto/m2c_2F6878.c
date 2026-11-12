#include "m2c_macros.h"

M2C_UNK func_002F1360(s32, s32);                         /* extern */

void func_002F6878(void *arg0, s8 arg1) {
    s32 temp_v0;

    M2C_FIELD(arg0, s8 *, 0x98) = arg1;
    temp_v0 = M2C_FIELD(arg0, s32 *, 4);
    if (temp_v0 != 0) {
        func_002F1360(temp_v0, arg1);
    }
}
