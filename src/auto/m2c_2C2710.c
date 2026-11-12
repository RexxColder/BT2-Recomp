#include "m2c_macros.h"

M2C_UNK func_002C2778(s32, void *);                 /* extern */
s32 func_002D4440(s32, s32);                        /* extern */
M2C_UNK func_002D4508(s32);                         /* extern */

void func_002C2710(void *arg0) {
    s32 temp_v0;

    temp_v0 = func_002D4440(arg0 + 0x94, M2C_FIELD(arg0, s32 *, 0x90));
    if (temp_v0 != 0) {
        func_002C2778(temp_v0, arg0);
        func_002D4508(temp_v0);
    }
}
