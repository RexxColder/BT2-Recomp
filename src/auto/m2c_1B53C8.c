#include "m2c_macros.h"

M2C_UNK GfxLens_Stop(s32, M2C_UNK);                 /* extern */

void func_001B53C8(void *arg0) {
    s32 temp_v1;

    temp_v1 = M2C_FIELD(M2C_FIELD(arg0, void **, 0x38), s32 *, 0x50);
    if (temp_v1 != -1) {
        GfxLens_Stop(temp_v1, -1);
    }
}
