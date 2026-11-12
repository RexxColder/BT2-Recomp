#include "m2c_macros.h"

M2C_UNK StgSlot_Call20(s32);                        /* extern */
s32 func_002E0F68();                                /* extern */

void func_002E0A38(void *arg0) {
    s32 temp_v0;

    if (func_002E0F68() != 0) {
        temp_v0 = M2C_FIELD(arg0, s32 *, 0x3B4);
        if (temp_v0 != 0) {
            StgSlot_Call20(temp_v0);
        }
    }
}
