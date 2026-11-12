#include "m2c_macros.h"

M2C_UNK func_00300598(s32);                         /* extern */

void func_002BB3B8(void *arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x48);
    if (temp_v0 != 0) {
        func_00300598(temp_v0);
    }
}
