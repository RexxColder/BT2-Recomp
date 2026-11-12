#include "m2c_macros.h"

s32 func_002BD798(s32);                             /* extern */
M2C_UNK func_002CED10(s32);                         /* extern */

void func_002B74A0(void *arg0) {
    s32 temp_s0;
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x40);
    temp_s0 = M2C_FIELD(arg0, s32 *, 0x3C);
    if ((temp_v0 != 0) && (func_002BD798(temp_v0) == 3)) {
        func_002CED10(temp_s0);
    }
}
