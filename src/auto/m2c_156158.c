#include "m2c_macros.h"

M2C_UNK EftTexSet_Keep32(s32, M2C_UNK, M2C_UNK);    /* extern */
M2C_UNK func_0014E970(void *);                      /* extern */

void func_00156158(void *arg0) {
    void *temp_s1;

    temp_s1 = M2C_FIELD(arg0, void **, 0x38);
    func_0014E970(temp_s1);
    if (M2C_FIELD(M2C_FIELD(arg0, void **, 0x24), s32 *, 4) != 0) {
        EftTexSet_Keep32(M2C_FIELD(temp_s1, s32 *, 0x1E84), 1, 0);
    }
}
