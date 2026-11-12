#include "m2c_macros.h"

M2C_UNK FlashShapePool_Term(s32);                   /* extern */
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);              /* extern */

void func_001AEA90(void *arg0) {
    s32 temp_s0;

    temp_s0 = M2C_FIELD(arg0, s32 *, 0x38);
    FlashShapePool_Term(temp_s0 + 0x170);
    memset(temp_s0, 0, 0x1D0);
}
