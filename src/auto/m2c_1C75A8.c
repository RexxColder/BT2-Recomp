#include "m2c_macros.h"

M2C_UNK EftTexSet_Keep32(s32, M2C_UNK, M2C_UNK);    /* extern */
extern s32 D_003878A4;

void func_001C75A8(void *arg0) {
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x24), s32 *, 4) != 0) {
        EftTexSet_Keep32(D_003878A4 + 8, 1, 0);
    }
}
