#include "m2c_macros.h"

M2C_UNK func_002824C8();                            /* extern */
s32 func_0028BAA8(M2C_UNK);                         /* extern */
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);              /* extern */
extern s32 D_00387B04;

void func_002825E0(void) {
    s32 temp_v0;

    temp_v0 = func_0028BAA8(0x60);
    D_00387B04 = temp_v0;
    memset(temp_v0, 0, 0x60);
    func_002824C8();
}
