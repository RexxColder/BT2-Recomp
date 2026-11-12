#include "m2c_macros.h"

M2C_UNK func_28BB60(s32);                           /* extern */

void func_003B4B20(void *arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0xA8);
    if (temp_v0 != 0) {
        func_28BB60(temp_v0);
        M2C_FIELD(arg0, s32 *, 0xA8) = 0;
    }
}
