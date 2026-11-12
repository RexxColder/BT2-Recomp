#include "m2c_macros.h"

s32 func_0028BAA8(M2C_UNK);                         /* extern */
M2C_UNK func_002982E8(s32);                         /* extern */
extern s32 D_00387F2C;

void func_00298438(void) {
    s32 temp_v0;

    temp_v0 = func_0028BAA8(0x4000);
    D_00387F2C = temp_v0;
    func_002982E8(temp_v0);
}
