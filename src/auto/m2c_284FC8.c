#include "m2c_macros.h"

M2C_UNK func_00284F88();                            /* extern */
s32 func_0028BAA8(M2C_UNK);                         /* extern */
M2C_UNK memset(s32, M2C_UNK, M2C_UNK);              /* extern */
extern s32 D_00387B0C;

void func_00284FC8(void) {
    s32 temp_v0;

    temp_v0 = func_0028BAA8(0x28);
    D_00387B0C = temp_v0;
    memset(temp_v0, 0, 0x28);
    func_00284F88();
}
