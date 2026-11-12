#include "m2c_macros.h"

M2C_UNK EftTexSet_Keep32(s32, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_001E8B08();                            /* extern */
extern s32 D_003878F4;

void func_001E7718(void *arg0) {
    func_001E8B08();
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x24), s32 *, 4) != 0) {
        EftTexSet_Keep32(D_003878F4 + 8, 1, 0);
    }
}
