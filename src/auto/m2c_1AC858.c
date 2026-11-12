#include "m2c_macros.h"

M2C_UNK EftTexSet_Keep4(s32, M2C_UNK, M2C_UNK);     /* extern */
extern s32 D_0038784C;

void func_001AC858(void *arg0) {
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x24), s32 *, 4) != 0) {
        EftTexSet_Keep4(D_0038784C + 8, 1, 0);
    }
}
