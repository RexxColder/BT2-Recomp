#include "m2c_macros.h"

M2C_UNK EftTexSet_Keep32(s32, M2C_UNK, M2C_UNK);    /* extern */
extern void *D_00387824;

void func_001A5318(void) {
    s32 temp_v1;

    temp_v1 = M2C_FIELD(D_00387824, s32 *, 8);
    if (temp_v1 != 0) {
        EftTexSet_Keep32(temp_v1, 1, 0);
    }
}
