#include "m2c_macros.h"

M2C_UNK func_0026DF68(void *, s32, s32);            /* extern */

// If the object's pointer at +8 is set, calls func_0026DF68 on it at +0xA8 with the caller's second argument and flag 1.
void func_0026C770(void *arg0, s32 arg1) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 8);
    if (temp_v0 != 0) {
        func_0026DF68((u8 *)temp_v0 + 0xA8, arg1, 1);
    }
}
