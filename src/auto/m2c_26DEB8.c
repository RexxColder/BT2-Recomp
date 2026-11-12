#include "m2c_macros.h"

M2C_UNK func_0028BB60(s32);                         /* extern */

void func_0026DEB8(void *arg0) {
    s32 temp_v0;

    temp_v0 = M2C_FIELD(arg0, s32 *, 0x14);
    if (temp_v0 != 0) {
        func_0028BB60(temp_v0);
        M2C_FIELD(arg0, s32 *, 0x14) = 0;
    }
}
